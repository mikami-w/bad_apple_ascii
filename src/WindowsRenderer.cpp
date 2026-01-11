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
    void reset_cursor()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos{0, 0};
        SetConsoleCursorPosition(hOut, pos);
    }

    class WindowsConsoleRenderer : public IRenderer
    {
    public:
        WindowsConsoleRenderer()
        {
            // 获取标准输出句柄
            m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        void initialize() override
        {
            if (m_hConsole == INVALID_HANDLE_VALUE) return;

            // 隐藏光标
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(m_hConsole, &cursorInfo);
            cursorInfo.bVisible = FALSE; // 设置为不可见
            SetConsoleCursorInfo(m_hConsole, &cursorInfo);

            // 设置控制台编码为 UTF-8
            SetConsoleOutputCP(CP_UTF8);
        }

        void render(std::string const& data) override
        {
            if (m_hConsole == INVALID_HANDLE_VALUE) return;

            // 光标复位到 (0,0)
            COORD pos = {0, 0};
            SetConsoleCursorPosition(m_hConsole, pos);

            // 直接写入控制台缓冲区
            DWORD bytesWritten = 0;
            WriteConsoleA(
                m_hConsole,             // 句柄
                data.c_str(),           // 数据指针
                static_cast<DWORD>(data.length()), // 长度
                &bytesWritten,          // 实际写入了多少
                nullptr                 // 保留
            );
        }
    private:
        HANDLE m_hConsole;
    };

    std::unique_ptr<IRenderer> create_renderer()
    {
        return std::make_unique<WindowsConsoleRenderer>();
    }
}

NAMESPACE_BAD_APPLE_END

#endif

