#include "AsciiConverter.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

    // 读取图片（请确保路径下有这张图，或者换成存在的图片）
    cv::Mat img = cv::imread("../img/hina.jpg");

    if (img.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        // 容错：造一个渐变图测试
        img = cv::Mat(480, 640, CV_8UC1);
        for(int i=0; i<img.rows; ++i)
            for(int j=0; j<img.cols; ++j)
                img.at<uchar>(i,j) = (i+j) % 256;
    }

    std::thread t([&img]
    {
        cv::imshow("Hina", img);
        cv::waitKey(0);
    });


    BadApple::Graphics::AsciiConverter converter(132, 100);
    // 转换
    std::string art = converter.convert(img);

    // 打印
    std::cout << "========= BEGIN FRAME =========" << std::endl;
    std::cout << art << std::endl;
    std::cout << "========= END FRAME =========" << std::endl;

    t.join();
    return 0;
}