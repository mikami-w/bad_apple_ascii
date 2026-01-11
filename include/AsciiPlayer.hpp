#ifndef BAD_APPLE_ASCII_ASCIIPLAYER_HPP
#define BAD_APPLE_ASCII_ASCIIPLAYER_HPP

#include "Common.hpp"
#include "AsciiConverter.hpp"
#include "AudioPlayer.hpp"
#include "OpenCVVideoSource.hpp"
#include "Renderer.hpp"

#include <string>
#include <memory>
NAMESPACE_BAD_APPLE_BEGIN

namespace App
{
    class AsciiPlayer
    {
    public:
        AsciiPlayer(std::string video_path, std::string audio_path, int video_width = 160)
            : m_video_width(video_width), m_video_path(std::move(video_path)), m_audio_path(std::move(audio_path)) {}
        ~AsciiPlayer() = default;

        void run();

    private:
        void init_modules();

    private:
        int m_video_width;

        std::string m_video_path;
        std::string m_audio_path;

        std::unique_ptr<IO::IVideoSource> m_video;
        std::unique_ptr<View::IRenderer> m_renderer;
        Graphics::AsciiConverter m_converter;

        IO::AudioPlayer m_audio_player;
    };
}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_ASCIIPLAYER_HPP