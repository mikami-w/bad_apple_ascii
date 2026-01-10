#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[])
{
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

    // 读取图片（请确保路径下有这张图，或者换成存在的图片）
    cv::Mat image = cv::imread("../img/hina.jpg");

    if (image.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::imshow("Display window", image);
    cv::waitKey(0);
    return 0;
}