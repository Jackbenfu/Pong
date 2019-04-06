//
// window.impl.cpp
// jackbengine
//
// Created by Damien Bendejacq on 11/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "window.impl.hpp"

using namespace Jackbengine;

Window::Impl::Impl(const std::string &title, int width, int height, bool fullscreen)
{
    SDL_WindowFlags flags;
    int x;
    int y;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
        x = 0;
        y = 0;
    }
    else
    {
        flags = SDL_WINDOW_HIDDEN;
        x = SDL_WINDOWPOS_CENTERED;
        y = SDL_WINDOWPOS_CENTERED;
    }

    m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    if (nullptr == m_window)
    {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_GetWindowSize(m_window, &m_width, &m_height);

    setWindowIcon();
    SDL_ShowWindow(m_window);
}

Window::Impl::~Impl()
{
    SDL_DestroyWindow(m_window);
}

int Window::Impl::width() const
{
    return m_width;
}

int Window::Impl::height() const
{
    return m_height;
}

SDL_Window* Window::Impl::internalObject() const
{
    return m_window;
}

void Window::Impl::setWindowIcon()
{
#ifdef _WIN32

    // Thanks to this Gist: https://gist.github.com/noct/9884320

    auto handle = GetModuleHandle(nullptr);
    if (!handle)
    {
        throw std::runtime_error(std::to_string(GetLastError()));
    }

    const uint maskR = 0x00ff0000;
    const uint maskG = 0x0000ff00;
    const uint maskB = 0x000000ff;
    const uint maskA = 0xff000000;
    const int size = 32;
    const int bpp = 32;

    auto icon = (HICON)LoadImage(handle, "icon", IMAGE_ICON, size, size, LR_SHARED);
    if (nullptr == icon)
    {
        throw std::runtime_error(std::to_string(GetLastError()));
    }

    ICONINFO iconInfo; // NOLINT
    if (FALSE == GetIconInfo(icon, &iconInfo))
    {
        throw std::runtime_error(std::to_string(GetLastError()));
    }

    auto deviceContext = CreateCompatibleDC(nullptr);
    if (nullptr == deviceContext)
    {
        throw std::runtime_error(std::to_string(GetLastError()));
    }

    auto surface = SDL_CreateRGBSurface(0, size, size, bpp, maskR, maskG, maskB, maskA);
    if (nullptr == surface)
    {
        throw std::runtime_error(IMG_GetError());
    }

    BITMAPINFO bmi; // NOLINT
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = size;
    bmi.bmiHeader.biHeight = -size;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = bpp;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;

    SelectObject(deviceContext, iconInfo.hbmColor);
    GetDIBits(deviceContext, iconInfo.hbmColor, 0, size, surface->pixels, &bmi, DIB_RGB_COLORS);
    SDL_SetWindowIcon(m_window, surface);

    SDL_FreeSurface(surface);
    DeleteDC(deviceContext);
    DeleteObject(iconInfo.hbmColor);
    DeleteObject(iconInfo.hbmMask);
    DestroyIcon(icon);

#endif
}
