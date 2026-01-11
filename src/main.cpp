#include "AsciiPlayer.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>

class BadAppleApp
{
public:
    BadAppleApp()
        : BadAppleApp("../resources/ba_video.mp4", "../resources/ba_audio.webm") {}
    BadAppleApp(std::string video_path, std::string audio_path)
        : m_video_path(std::move(video_path)), m_audio_path(std::move(audio_path)) {}
    ~BadAppleApp() = default;

    void run()
    {
        BadApple::App::AsciiPlayer app(m_video_path, m_audio_path);
        app.run();
    }
private:
    std::string m_video_path;
    std::string m_audio_path;
};

int main(int argc, char* argv[])
{
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

    BadAppleApp app;
    app.run();

    return 0;
}