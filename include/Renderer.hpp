#ifndef BAD_APPLE_ASCII_RENDERER_HPP
#define BAD_APPLE_ASCII_RENDERER_HPP

#include "Common.hpp"

#include <memory>
#include <string>

NAMESPACE_BAD_APPLE_BEGIN

namespace View
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual void initialize() = 0; // 初始化窗口大小, 隐藏光标等
        virtual void render(std::string const& data) = 0; // 渲染一帧数据
    };

    std::unique_ptr<IRenderer> create_renderer();
}

NAMESPACE_BAD_APPLE_END

#endif //BAD_APPLE_ASCII_RENDERER_HPP