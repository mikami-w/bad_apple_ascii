#ifdef _WIN32
#include <memory>

#include "Renderer.hpp"
#include "Common.hpp"
#include "Common.hpp"
#include "Renderer.hpp"

#include <windows.h>
#include <iostream>

NAMESPACE_BAD_APPLE_BEGIN
namespace View
{
    class WindowsConsoleRenderer : public IRenderer
    {

    };

    std::unique_ptr<IRenderer> create_renderer()
    {
        return std::make_unique<WindowsConsoleRenderer>();
    }
}

NAMESPACE_BAD_APPLE_END

#endif

