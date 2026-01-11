#ifndef BAD_APPLE_ASCII_OPENCVVIDEOSOURCE_HPP
#define BAD_APPLE_ASCII_OPENCVVIDEOSOURCE_HPP

#include "Common.hpp"
#include "Stopwatch.hpp"
#include "IVideoSource.hpp"

#include <opencv2/opencv.hpp>

NAMESPACE_BAD_APPLE_BEGIN

namespace IO
{
    class OpenCVVideoSource : public IVideoSource
    {
    public:
        OpenCVVideoSource() = default;
        ~OpenCVVideoSource() override = default;

        bool open(const std::string& source) override;
        void close() override;

        [[nodiscard]] std::optional<cv::Mat> next_frame() override;
        [[nodiscard]] int get_width() const override { return m_width; }
        [[nodiscard]] int get_height() const override { return m_height; }
        [[nodiscard]] double get_fps() const override { return m_fps;}
        [[nodiscard]] int get_frame_count() const override { return m_frame_count;}

    private:
        cv::VideoCapture m_capture;
        int m_width = 0;
        int m_height = 0;
        double m_fps = 0.0;
        int m_frame_count = 0;
    };

}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_OPENCVVIDEOSOURCE_HPP