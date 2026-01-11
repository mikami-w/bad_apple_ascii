#ifndef BAD_APPLE_ASCII_IAUDIOPLAYER_HPP
#define BAD_APPLE_ASCII_IAUDIOPLAYER_HPP

#include <cstdint>

#include "Common.hpp"

NAMESPACE_BAD_APPLE_BEGIN

namespace IO
{
    class IAudioPlayer
    {
    public:
        virtual ~IAudioPlayer() = default;

        virtual bool load(std::string const& path) = 0;
        virtual void play() = 0; // 异步播放 (非阻塞)
        virtual void stop() = 0;

        [[nodiscard]] virtual bool is_playing() const = 0;
        [[nodiscard]] virtual std::int64_t get_time_ms() const = 0;

    };
}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_IAUDIOPLAYER_HPP