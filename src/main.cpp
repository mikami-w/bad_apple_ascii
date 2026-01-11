#include "AsciiConverter.hpp"
#include "OpenCVVideoSource.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>

#include "Renderer.hpp"

#ifdef _WIN32
#include <windows.h>
void reset_cursor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos{0, 0};
    SetConsoleCursorPosition(hOut, pos);
}
#else
void reset_cursor()
{
    std::cout << "\033[H";
}
#endif


int main(int argc, char* argv[])
{
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

    using namespace BadApple;

    auto video = std::make_unique<IO::OpenCVVideoSource>();
    auto renderer = View::create_renderer();
    Graphics::AsciiConverter converter;

    if (!video->open("../resources/ba_video.mp4"))
    {
        std::cerr << "Failed to open video stream." << std::endl;
        return 1;
    }

    if (renderer) renderer->initialize();

    if (video->get_width() == 0)
    {
        std::cerr << "Video Stream Width Error: width = 0." << std::endl;
        return 2;
    }

    int width = 160;
    int height = (width * video->get_height() / video->get_width()) >> 1;
    converter.set_scale(width, height);

    for (;;)
    {
        auto frame = video->next_frame();
        if (!frame.has_value())
        {
            break;
        }

        std::string ascii_art = converter.convert(frame.value());
        reset_cursor();

        if (renderer)
            renderer->render(ascii_art);

        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    return 0;
}