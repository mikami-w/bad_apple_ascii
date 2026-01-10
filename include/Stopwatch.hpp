#ifndef BAD_APPLE_ASCII_STOPWATCH_HPP
#define BAD_APPLE_ASCII_STOPWATCH_HPP

#include "Common.hpp"

#include <chrono>

NAMESPACE_BAD_APPLE_BEGIN

namespace Core
{
    class Stopwatch
    {
    public:
        using Clock = std::chrono::steady_clock; // 使用稳态时钟，不受系统时间修改影响
        using TimePoint = std::chrono::time_point<Clock>;

        Stopwatch(): m_start(Clock::now()), m_end(m_start), m_running(false) {}

        void start()
        {
            m_start = Clock::now();
            m_running = true;
        }
        void stop()
        {
            m_end = Clock::now();
            m_running = false;
        }
        void reset()
        {
            m_start = Clock::now();
            m_end = m_start;
            m_running = false;
        }

        template <typename T = std::chrono::milliseconds>
        [[nodiscard]] std::int64_t elapsed() const
        {
            return std::chrono::duration_cast<T>(m_running ? Clock::now() - m_start : m_end - m_start).count();
        }

    private:
        TimePoint m_start;
        TimePoint m_end;
        bool m_running;
    };
}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_STOPWATCH_HPP