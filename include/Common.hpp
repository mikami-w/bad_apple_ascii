#ifndef BAD_APPLE_ASCII_COMMON_HPP
#define BAD_APPLE_ASCII_COMMON_HPP

#include <string>

namespace BadApple {
    struct Config {
        std::string video_path;
        std::string audio_path;
        int console_width = 120;
        int console_height = 40;
    };
}

#define NAMESPACE_BAD_APPLE_BEGIN namespace BadApple {
#define NAMESPACE_BAD_APPLE_END }

#endif //BAD_APPLE_ASCII_COMMON_HPP