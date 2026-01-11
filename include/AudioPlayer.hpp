#ifndef BAD_APPLE_ASCII_AUDIOPLAYER_HPP
#define BAD_APPLE_ASCII_AUDIOPLAYER_HPP

#include "Common.hpp"
#include "IAudioPlayer.hpp"

#include <string>
#include <iostream>

#include <miniaudio.h>

NAMESPACE_BAD_APPLE_BEGIN

namespace IO
{
    class AudioPlayer : public IAudioPlayer
    {
    public:
        AudioPlayer();
        ~AudioPlayer() override;
        bool load(const std::string& path) override;
        void play() override;
        void stop() override;
        [[nodiscard]] bool is_playing() const override;
        [[nodiscard]] std::int64_t get_time_ms() const override; // 获取播放进度时间戳

    private:
        ma_engine m_engine; // 音频引擎
        ma_sound m_sound;   // 声音对象
        bool m_initialized = false;
        bool m_loaded = false;
    };
}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_AUDIOPLAYER_HPP