#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <stdexcept>

int main() {

    std::filesystem::path image_path = "data/raw/Mona Lisa.jpg";
    
    try {
        // Check if the file exists
        if (!std::filesystem::exists(image_path)) {
            throw std::runtime_error("The file '" + image_path.string() + "' does not exist.");
        }
        
        // Read the image
        cv::Mat image = cv::imread(image_path.string(), cv::IMREAD_GRAYSCALE);  // Read the image in grayscale
        
        if (image.empty()) {
            throw std::runtime_error("Failed to load image.");
        }
        
        // Apply simple thresholding
        cv::Mat thresholded_image;
        cv::threshold(image, thresholded_image, 127, 255, cv::THRESH_BINARY);
        
        // Create a resizable window
        cv::namedWindow("Simple Thresholding", cv::WINDOW_NORMAL);
        
        // Display the result
        cv::imshow("Simple Thresholding", thresholded_image);
        
        // Wait for a key press and close the window
        cv::waitKey(0);
        cv::destroyAllWindows();
    } 
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } 
    catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

    return 0;
}
