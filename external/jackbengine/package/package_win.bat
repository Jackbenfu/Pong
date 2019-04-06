@echo off

if [%1]==[] goto usage

set target=%1
set executable_name=%~nx1
set executable_dir=%~dp1

echo Creating final archive
set rar_tool_bin="C:\Program Files\WinRAR\Rar.exe"
set mingw_bin_dir="C:\MinGW\bin"
set archive_name="%executable_dir%%executable_name%.zip"

%rar_tool_bin% a -m5 -ep %archive_name% %1
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libFLAC-8.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libfreetype-6.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libjpeg-9.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libmodplug-1.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libogg-0.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libpng16-16.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libtiff-5.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libvorbis-0.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libvorbisfile-3.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libwebp-4.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\SDL2.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\SDL2_image.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\SDL2_mixer.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\SDL2_ttf.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\smpeg2.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\zlib1.dll
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\"libstdc++-6.dll"
%rar_tool_bin% a -m5 -ep %archive_name% %mingw_bin_dir%\libgcc_s_dw2-1.dll

goto :eof

:usage
echo Usage: package_win.bat target
echo   target    The target executable including its full path.
