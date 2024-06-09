#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "image_processing.h"

int main(int argc, char** argv) {
    // Check if the minimum number of arguments is provided
    if (argc < 3) {
        std::cout << "Usage: <operation> <image_path/video_path> [additional parameters] [output_path]" << std::endl;
        std::cin.get();
        return -1;
    }

    std::string operation = argv[1];
    std::string outputPath = (argc > 4) ? argv[argc - 1] : "";

    // Special case for creating a panorama
    if (operation == "panorama") {
        std::vector<cv::Mat> images;
        for (int i = 2; i < argc - 1; ++i) {
            cv::Mat img = cv::imread(argv[i], cv::IMREAD_COLOR);
            if (img.empty()) {
                std::cout << "Error: Could not load image " << argv[i] << std::endl;
                std::cin.get();
                return -1;
            }
            images.push_back(img);
        }
        createPanorama(images, outputPath);
        std::cout << "Panorama created successfully" << std::endl;
        std::cin.get();
        return 0;
    }

    // Special case for processing a video
    if (operation == "video") {
        if (argc < 4) {
            std::cout << "Usage: video <video_path> <operation> [param1] [param2]" << std::endl;
            std::cin.get();
            return -1;
        }
        std::string videoPath = argv[2];
        std::string videoOperation = argv[3];
        double param1 = (argc > 4) ? std::stod(argv[4]) : 0;
        double param2 = (argc > 5) ? std::stod(argv[5]) : 0;
        processVideo(videoPath, videoOperation, param1, param2);
        return 0;
    }

    // Load the input image for other operations
    cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_COLOR);
    if (inputImage.empty()) {
        std::cout << "Error: Could not load image " << argv[2] << std::endl;
        std::cin.get();
        return -1;
    }

    std::cout << "Image loaded successfully" << std::endl;

    // Apply the specified operation
    if (operation == "dilate" || operation == "erode") {
        int size = std::stoi(argv[3]);
        bool isDilation = (operation == "dilate");
        applyDilationErosion(inputImage, size, isDilation, outputPath);
    }
    else if (operation == "resize") {
        double factor = std::stod(argv[3]);
        resizeImage(inputImage, factor, outputPath);
    }
    else if (operation == "lighten" || operation == "darken") {
        double factor = std::stod(argv[3]);
        lightenDarkenImage(inputImage, (operation == "lighten") ? factor : -factor, outputPath);
    }
    else if (operation == "canny") {
        double threshold1 = std::stod(argv[3]);
        double threshold2 = std::stod(argv[4]);
        cannyEdgeDetection(inputImage, threshold1, threshold2, outputPath);
    }
    else if (operation == "rotate") {
        double angle = std::stod(argv[3]);
        rotateImage(inputImage, angle, outputPath);
    }
    else if (operation == "blur") {
        int kernelSize = std::stoi(argv[3]);
        applyGaussianBlur(inputImage, kernelSize, outputPath);
    }
    else if (operation == "grayscale") {
        convertToGrayscale(inputImage, outputPath);
    }
    else if (operation == "autocontrast") {
        autoContrast(inputImage, outputPath);
    }
    else if (operation == "recognize") {
        detectAndRecognizeFaces(inputImage);
    }
    else {
        std::cout << "Unknown operation: " << operation << std::endl;
    }

    std::cin.get();
    return 0;
}
