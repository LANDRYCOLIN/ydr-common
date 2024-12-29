#include <opencv2/opencv.hpp>

int main() {
    std::string path = "Resources/image.png";
    cv::Mat img = cv::imread(path);

    if (img.empty()) {
        std::cerr << "Image not found!" << std::endl;
        return -1;
    }

    cv::Mat hsvImage;
    cv::cvtColor(img, hsvImage, cv::COLOR_BGR2HSV);

    cv::Scalar blueLower(100, 150, 50); 
    cv::Scalar blueUpper(140, 255, 255);
    cv::Scalar yellowLower(20, 100, 100); 
    cv::Scalar yellowUpper(30, 255, 255);

    cv::Mat blueMask;
    cv::inRange(hsvImage, blueLower, blueUpper, blueMask);

    cv::Mat yellowMask;
    cv::inRange(hsvImage, yellowLower, yellowUpper, yellowMask);

    std::vector<std::vector<cv::Point>> blueContours;
    cv::findContours(blueMask, blueContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> yellowContours;
    cv::findContours(yellowMask, yellowContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < blueContours.size(); ++i) {
        cv::Rect boundingBox = cv::boundingRect(blueContours[i]);

        if (cv::contourArea(blueContours[i]) < 500) continue;

        cv::rectangle(img, boundingBox, cv::Scalar(255, 0, 0), 2);
        cv::putText(img, "blue", cv::Point(boundingBox.x, boundingBox.y - 10),
            cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 0), 2);
    }

    for (size_t i = 0; i < yellowContours.size(); ++i) {
        cv::Rect boundingBox = cv::boundingRect(yellowContours[i]);

        if (cv::contourArea(yellowContours[i]) < 500) continue;

        cv::rectangle(img, boundingBox, cv::Scalar(0, 255, 255), 2);
        cv::putText(img, "yellow", cv::Point(boundingBox.x, boundingBox.y - 10),
            cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 255), 2);
    }

    cv::imshow("Detected Colors", img);
    cv::waitKey(0);

    return 0;
}
