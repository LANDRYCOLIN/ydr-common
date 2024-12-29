#include <opencv2/opencv.hpp>
#include <string>

int main() {
    std::string path = "Resources/test.png";
    cv::Mat img = cv::imread(path);

    if (img.empty()) {
        std::cerr << "Image not found!" << std::endl;
        return -1;
    }

    // 转换为灰度图像
    cv::Mat grayImage;
    cv::cvtColor(img, grayImage, cv::COLOR_BGR2GRAY);

    // 二值化处理
    cv::Mat binaryImage;
    cv::threshold(grayImage, binaryImage, 128, 255, cv::THRESH_BINARY);

    // 高斯模糊处理
    cv::Mat blurredImage;
    cv::GaussianBlur(binaryImage, blurredImage, cv::Size(5, 5), 0);

    // 膨胀操作
    cv::Mat dilatedImage;
    cv::Mat kernel = cv::Mat::ones(5, 5, CV_8U);
    cv::dilate(blurredImage, dilatedImage, kernel);

    cv::imshow("Original Image", img);
    cv::imshow("Gray Image", grayImage);
    cv::imshow("Binary Image", binaryImage);
    cv::imshow("Blurred Image", blurredImage);
    cv::imshow("Dilated Image", dilatedImage);

    cv::waitKey(0);
    return 0;
}
