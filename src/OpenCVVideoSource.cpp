#include "OpenCVVideoSource.hpp"
#include "Common.hpp"

NAMESPACE_BAD_APPLE_BEGIN

namespace IO
{
    bool OpenCVVideoSource::open(const std::string& source)
    {
        m_capture.open(source);
        if (!m_capture.isOpened())
        {
            std::cerr << "OpenCVVideoSource could not open source: " << source << std::endl;
            return false;
        }

        m_width = m_capture.get(cv::CAP_PROP_FRAME_WIDTH);
        m_height = m_capture.get(cv::CAP_PROP_FRAME_HEIGHT);
        m_fps = m_capture.get(cv::CAP_PROP_FPS);
        m_frame_count = m_capture.get(cv::CAP_PROP_FRAME_COUNT);

        return true;
    }

    void OpenCVVideoSource::close()
    {
        m_capture.release();
    }

    std::optional<cv::Mat> OpenCVVideoSource::next_frame()
    {
        if (!m_capture.isOpened())
        {
            return std::nullopt;
        }

        cv::Mat frame;
        m_capture.read(frame);
        ++m_frame_cursor;

        if (frame.empty())
        {
            // 视频结束
            return std::nullopt;
        }

        return frame;
    }

}

NAMESPACE_BAD_APPLE_END