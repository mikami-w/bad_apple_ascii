#ifdef __linux__

#include "Common.hpp"
#include "Renderer.hpp"
#include <cstdio>
#include <iostream>

NAMESPACE_BAD_APPLE_BEGIN
namespace View
{
    class LinuxConsoleRenderer : public IRenderer
    {
    public:
        LinuxConsoleRenderer()
        {
            std::ios::sync_with_stdio(false);
        }

        ~LinuxConsoleRenderer() override
        {
            // Linux 终端状态是全局的, 所以在析构函数中确保程序退出时光标被重新显示
            // ANSI Code: Show Cursor (\033[?25h)
            std::printf("\033[?25h");
            std::fflush(stdout);
        }

        void initialize() override
        {
            std::printf("\033[?25l"); // 隐藏光标
            std::printf("\033[2J"); // 清屏 (?考虑是否保留)

            std::fflush(stdout);
        }

        void render(std::string const& data) override
        {
            std::printf("\033[H"); // 光标移动到左上角
            std::fwrite(data.c_str(), 1, data.size(), stdout);
            std::fflush(stdout); // 刷新缓冲区, 确保一帧立刻显示出来而不是等待缓冲区满
        }
    };

    std::unique_ptr<IRenderer> create_renderer()
    {
        return std::make_unique<LinuxConsoleRenderer>();
    }
}

NAMESPACE_BAD_APPLE_END

#endif
