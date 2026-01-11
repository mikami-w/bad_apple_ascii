#ifndef BAD_APPLE_ASCII_ASCIIPLAYER_HPP
#define BAD_APPLE_ASCII_ASCIIPLAYER_HPP

#include "Common.hpp"
#include "AsciiConverter.hpp"
#include "OpenCVVideoSource.hpp"
#include "Renderer.hpp"
#include "Stopwatch.hpp"

#include <string>
#include <memory>
NAMESPACE_BAD_APPLE_BEGIN

namespace App
{
    class AsciiPlayer
    {
    public:
        AsciiPlayer(std::string video_path, std::string audio_path)
            : m_video_path(std::move(video_path)), m_audio_path(std::move(audio_path)) {}
        ~AsciiPlayer() = default;

        void run();

    private:
        void init_modules();
        void play_audio_async();

    private:
        std::string m_video_path;
        std::string m_audio_path;

        std::unique_ptr<IO::IVideoSource> m_video;
        std::unique_ptr<View::IRenderer> m_renderer;
        Graphics::AsciiConverter m_converter;
        Core::Stopwatch m_stopwatch;
    };
}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_ASCIIPLAYER_HPP