#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <stdexcept>

// Callback function for trackbar
void updateThreshold(int val, cv::Mat& image) {
    cv::Mat threshImage;
    cv::threshold(image, threshImage, val, 255, cv::THRESH_BINARY);
    cv::imshow("Thresholded Image", threshImage);
}

int main() {
    try {
        std::filesystem::path image_path = "data/raw/Mona Lisa.jpg";

        // Check if the file exists
        if (!std::filesystem::exists(image_path)) {
            throw std::runtime_error("The file '" + image_path.string() + "' does not exist.");
        }

        // Read the image
        cv::Mat image = cv::imread(image_path.string(), cv::IMREAD_GRAYSCALE);
        if (image.empty()) {
            throw std::runtime_error("Unable to read the image file '" + image_path.string() + "'.");
        }

        // Create a window
        cv::namedWindow("Thresholded Image", cv::WINDOW_NORMAL);

        // Initialize trackbar
        int initialThreshold = 127;
        cv::createTrackbar("Threshold", "Thresholded Image", &initialThreshold, 255, [](int val, void* userdata) {
            cv::Mat* img = static_cast<cv::Mat*>(userdata);
            updateThreshold(val, *img);
        }, &image);

        // Display the initial thresholded image
        updateThreshold(initialThreshold, image);

        // Wait until the user presses a key
        cv::waitKey(0);
        cv::destroyAllWindows();

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

    return 0;
}
