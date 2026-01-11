#ifndef BAD_APPLE_ASCII_IVIDEOSOURCE_HPP
#define BAD_APPLE_ASCII_IVIDEOSOURCE_HPP

#include "Common.hpp"

#include <opencv2/opencv.hpp>
#include <string>
#include <optional>

NAMESPACE_BAD_APPLE_BEGIN

namespace IO
{
    // 定义视频读取标准
    class IVideoSource
    {
    public:
        virtual ~IVideoSource() = default;

        virtual bool open(std::string const& source) = 0;
        virtual void close() = 0;

        [[nodiscard]] virtual std::optional<cv::Mat> next_frame() = 0;

        [[nodiscard]] virtual int get_width() const = 0;
        [[nodiscard]] virtual int get_height() const = 0;
        [[nodiscard]] virtual double get_fps() const = 0;
        [[nodiscard]] virtual int get_frame_count() const = 0;
        [[nodiscard]] virtual int get_current_frame_index() const = 0;
    };
}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_IVIDEOSOURCE_HPP
