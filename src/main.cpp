#include "AsciiPlayer.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>

class BadAppleApp
{
public:
    explicit BadAppleApp(int video_width = 120)
        : BadAppleApp("./resources/ba_video.mp4", "./resources/ba_audio.wav", video_width) {}
    BadAppleApp(std::string video_path, std::string audio_path, int video_width = 120)
        : m_video_width(video_width), m_video_path(std::move(video_path)), m_audio_path(std::move(audio_path)) {}
    ~BadAppleApp() = default;

    void run()
    {
        BadApple::App::AsciiPlayer app(m_video_path, m_audio_path, m_video_width);
        app.run();
    }
private:
    int m_video_width;
    std::string m_video_path;
    std::string m_audio_path;
};

int main(int argc, char* argv[])
{
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

    // 在 if/else 内部初始化，在外部调用 run
    std::unique_ptr<BadAppleApp> app;

    try
    {
        if (argc == 1)
        {
            // 无参数 -> 使用默认构造
            app = std::make_unique<BadAppleApp>();
        }
        else if (argc == 2)
        {
            // 有一个参数 -> 尝试解析为整数
            std::string arg = argv[1];
            std::size_t pos = 0;

            // std::stoi 会抛出异常如果无法转换
            // pos 会存储处理了多少个字符
            int value = std::stoi(arg, &pos);

            // 严格检查：确保整个字符串都是数字 (防止 "123abc" 被解析为 123)
            if (pos != arg.length())
            {
                throw std::invalid_argument("Argument contains non-digit characters");
            }

            // 使用带参构造
            app = std::make_unique<BadAppleApp>(value);
        }
        else
        {
            // 参数过多 -> 报错
            std::cerr << "[Error] Too many arguments." << std::endl;
            std::cerr << "Usage: " << argv[0] << " [optional_integer]" << std::endl;
            return -1;
        }

        // 运行应用
        if (app)
        {
            app->run();
        }
    }
    catch (const std::invalid_argument&)
    {
        std::cerr << "[Error] Invalid argument: \"" << argv[1] << "\" is not a valid integer." << std::endl;
        return -1;
    }
    catch (const std::out_of_range&)
    {
        std::cerr << "[Error] Argument is out of integer range." << std::endl;
        return -1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[Error] An unexpected error occurred: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}