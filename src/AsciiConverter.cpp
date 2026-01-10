#include "AsciiConverter.hpp"

#include <opencv2/imgproc.hpp>
#include <array>

NAMESPACE_BAD_APPLE_BEGIN

namespace Graphics
{
    std::string AsciiConverter::convert(cv::Mat const& frame) const
    {
        if (frame.empty())
            return "";

        // 缩放
        cv::Mat resized;
        cv::resize(frame, resized, cv::Size(m_width, m_height)); // AsciiConverter 不负责处理控制台字符的宽高不一致问题

        // 转灰度
        cv::Mat gray;
        if (resized.channels() == 1)
        {
            gray = resized;
        }
        else
        {
            cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
        }

        // 映射到 string
        std::string result;
        result.reserve((m_width + 1) * m_height);

        for (int row = 0; row < gray.rows; ++row)
        {
            uchar const* row_p = gray.ptr<uchar>(row); // 使用指针而不是有边界检查的 at 方法
            for (int col = 0; col < gray.cols; ++col)
            {
                // row_ptr[col] 拿到像素值 (0-255)
                // m_lut[row_ptr[col]] 查表拿到字符
                result.push_back(m_lut[row_p[col]]);
            }
            result.push_back('\n');
        }

        return result;
    }
}

NAMESPACE_BAD_APPLE_END