/*
 *  resourceGenerator.c
 *  Resource generator
 *
 *  Created by Damien Bendejacq on 21/05/2016.
 *  Copyright © 2016 Damien Bendejacq. All rights reserved.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MINIMUM_ARG_COUNT           3
#define OUTPUT_FILE_ARG_INDEX       1
#define FIRST_RESOURCE_ARG_INDEX    2

#define READ_FILE_BUFFER_LENGTH     256
#define OUTPUT_FILE_COLUMN_SIZE     10

#define NON_ALPHANUM_REPLACEMENT    '_'

#define RESOURCE_TYPE_BINARY_PREFIX "-b"
#define RESOURCE_TYPE_TEXT_PREFIX   "-t"

#define RESOURCE_TYPE_UNKNOWN       0
#define RESOURCE_TYPE_BINARY        1
#define RESOURCE_TYPE_TEXT          2

void usage()
{
    fprintf(stderr, "Usage: resourceGenerator outputFile -type<resource> [-type<resource>...]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Available types:\n");
    fprintf(stderr, "  -b<resource>   A binary file.\n");
    fprintf(stderr, "  -t<resource>   A text file.\n");
}

FILE* openFile(const char *name, const char *mode)
{
    FILE *file = fopen(name, mode);
    if (NULL == file)
    {
        perror(name);
    }
    return file;
}

FILE* prepareOutputFile(const char *resourceName)
{
    return openFile(resourceName, "wb");
}

FILE* prepareResourceFile(const char *resourceName)
{
    return openFile(resourceName, "rb");
}

int isResourceOfType(const char *resourceName, const char *resourceTypePrefix)
{
    return strstr(resourceName, resourceTypePrefix) == resourceName;
}

int getResourceNameFromArgument(char **resourceName)
{
    if (isResourceOfType(*resourceName, RESOURCE_TYPE_BINARY_PREFIX))
    {
        *resourceName += strlen(RESOURCE_TYPE_BINARY_PREFIX);
        return RESOURCE_TYPE_BINARY;
    }

    if (isResourceOfType(*resourceName, RESOURCE_TYPE_TEXT_PREFIX))
    {
        *resourceName += strlen(RESOURCE_TYPE_TEXT_PREFIX);
        return RESOURCE_TYPE_TEXT;
    }

    return RESOURCE_TYPE_UNKNOWN;
}

int appendResource(FILE *outputFile, char *resourceName)
{
    int resourceType = getResourceNameFromArgument(&resourceName);
    if (RESOURCE_TYPE_UNKNOWN == resourceType)
    {
        fprintf(stderr, "Invalid resource type prefix provided: %s", resourceName);
        return -1;
    }

    FILE *resourceFile = prepareResourceFile(resourceName);
    if (NULL == resourceFile)
    {
        return -1;
    }

    int resourceNameLength = (int)strlen(resourceName);
    int resourceNameIndex = resourceNameLength - 1;
    while (resourceNameIndex > -1)
    {
        if (resourceName[resourceNameIndex] == '/' ||
            resourceName[resourceNameIndex] == '\\')
        {
            break;
        }

        if (!isalnum(resourceName[resourceNameIndex]))
        {
            resourceName[resourceNameIndex] = NON_ALPHANUM_REPLACEMENT;
        }

        --resourceNameIndex;
    }
    ++resourceNameIndex;

    char resourceVariableName[FILENAME_MAX];
    memset(resourceVariableName, 0, FILENAME_MAX);
    memcpy(
        resourceVariableName,
        resourceName + resourceNameIndex,
        resourceNameLength - resourceNameIndex
    );

    fprintf(outputFile, "\n");
    fprintf(
        outputFile,
        "extern \"C\" const unsigned char %s[] =\n{\n",
        resourceVariableName
    );

    unsigned char buf[READ_FILE_BUFFER_LENGTH];
    size_t nRead = 0;
    size_t lineCount = 0;
    do
    {
        nRead = fread(buf, 1, sizeof(buf), resourceFile);
        size_t i;
        for (i = 0; i < nRead; ++i)
        {
            if (0 == lineCount)
            {
                fprintf(outputFile, "    ");
            }

            fprintf(outputFile, "0x%02x, ", buf[i]);
            if (++lineCount == OUTPUT_FILE_COLUMN_SIZE)
            {
                fprintf(outputFile, "\n");
                lineCount = 0;
            }
        }
    }
    while (nRead > 0);

    if (RESOURCE_TYPE_TEXT == resourceType)
    {
        /* A text resource must always be terminated by the NULL character. */
        if (0 == lineCount)
        {
            fprintf(outputFile, "    0x00");
        }
        else
        {
            fprintf(outputFile, "0x00");
        }
    }

    fprintf(outputFile, "\n};\n");

    if (RESOURCE_TYPE_TEXT != resourceType)
    {
        fprintf(
            outputFile,
            "extern \"C\" const size_t %s_size = sizeof(%s);\n",
            resourceVariableName,
            resourceVariableName
        );
    }

    fclose(resourceFile);

    return 0;
}

int main(int argc, char ** argv)
{
    if (argc < MINIMUM_ARG_COUNT)
    {
        usage();
        return EXIT_FAILURE;
    }

    FILE *outputFile = prepareOutputFile(argv[OUTPUT_FILE_ARG_INDEX]);
    if (NULL == outputFile)
    {
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "#include <stdlib.h>\n");
    for (int resourceIndex = FIRST_RESOURCE_ARG_INDEX; resourceIndex < argc; ++resourceIndex)
    {
        if (-1 == appendResource(outputFile, argv[resourceIndex]))
        {
            break;
        }
    }

    fclose(outputFile);

    return EXIT_SUCCESS;
}
