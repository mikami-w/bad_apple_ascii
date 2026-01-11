#include "AsciiPlayer.hpp"

#include <thread>

#include "Common.hpp"

NAMESPACE_BAD_APPLE_BEGIN
namespace App
{
    void AsciiPlayer::run()
    {
        try
        {
            init_modules();
        } catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return;
        }

        double fps = m_video->get_fps();

        // start
        play_audio_async();
        m_stopwatch.start();

        for (;;)
        {
            auto elapsed_ms = m_stopwatch.elapsed();

            // 计算目标帧
            int target_frame = static_cast<int>(fps * elapsed_ms / 1000.0);
            // 获取当前帧
            int current_frame = m_video->get_current_frame_index();

            if (current_frame < target_frame)
            {
                // 落后, 丢帧追赶
                auto frame = m_video->next_frame();
                if (!frame.has_value()) break;
                continue;
            }
            else if (current_frame > target_frame)
            {
                // 超前, 等待
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            else
            {
                // 恰好, 渲染
                auto frame = m_video->next_frame();
                if (!frame.has_value()) break;

                std::string ascii = m_converter.convert(frame.value());
                if (m_renderer)
                    m_renderer->render(ascii);
            }
        }
    }

    void AsciiPlayer::init_modules()
    {
        // 视频源
        m_video = std::make_unique<IO::OpenCVVideoSource>();
        if (!m_video->open(m_video_path))
        {
            throw std::runtime_error("Failed to open video: " + m_video_path);
        }
        if (m_video->get_height() == 0)
        {
            throw std::runtime_error("Video has incorrect property: height=0");
        }

        // 渲染器
        m_renderer = View::create_renderer();
        if (!m_renderer)
        {
            throw std::runtime_error("Failed to create renderer");
        }
        m_renderer->initialize();

        // ascii转换器
        int console_width = 120;
        int console_height = (console_width * m_video->get_height() / m_video->get_width()) >> 1;
        m_converter.set_scale(console_width, console_height);
    }

    void AsciiPlayer::play_audio_async()
    {
#ifdef __linux__
        std::string cmd = "./ffplay -nodisp -autoexit -loglevel quiet \"" + m_audio_path + "\" > /dev/null 2>&1 &";
#endif
#ifdef _WIN32
        std::string cmd = "start /B .\\ffplay.exe -nodisp -autoexit -loglevel quiet \"" + m_audio_path + "\"";
#endif

        (void)std::system(cmd.c_str());
    }
}
NAMESPACE_BAD_APPLE_END
