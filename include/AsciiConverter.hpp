#ifndef BAD_APPLE_ASCII_ASCIICONVERTER_HPP
#define BAD_APPLE_ASCII_ASCIICONVERTER_HPP

#include "Common.hpp"

#include <opencv2/opencv.hpp>
#include <string>

NAMESPACE_BAD_APPLE_BEGIN

namespace Graphics
{
    class AsciiConverter
    {
    public:
        AsciiConverter(): AsciiConverter(120, 90) {};
        AsciiConverter(int width, int height):m_width(width), m_height(height) {}

        void set_scale(int width, int height)
        {
            m_width = width;
            m_height = height;
        }

        std::string convert(cv::Mat const& frame) const;

    private:
        // 字符集：从暗(0)到亮(255)
        static constexpr std::array<char, 256> m_lut = []() -> std::array<char, 256>
        {
            constexpr char ASCII_PALETTE[] = " .:-=+*#%@" ;
            constexpr int PALETTE_SIZE = std::size(ASCII_PALETTE) - 1; // 不包括终止符
            std::array<char, 256> lut{}; // constexpr 函数不允许未初始化的变量, 故必须进行初始化，否则无法在编译期计算

            for (int i = 0; i < 256; ++i)
            {
                // 根据灰度值映射到字符集索引
                int index = (i * (PALETTE_SIZE - 1)) / 255;
                lut[i] = ASCII_PALETTE[index];
            }

            return lut;
        }();
        int m_width;
        int m_height;
    };

}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_ASCIICONVERTER_HPP