#include "image_processing.h"
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

// Function to save an image to a file
void saveImage(const std::string& filename, const cv::Mat& image) {
    if (!cv::imwrite(filename, image)) {
        std::cerr << "Error: Could not save image to " << filename << std::endl;
    }
    else {
        std::cout << "Image saved to " << filename << std::endl;
    }
}

// Function to apply dilation or erosion to an image
void applyDilationErosion(cv::Mat& inputImage, int size, bool isDilation, const std::string& outputPath = "") {
    cv::Mat outputImage;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * size + 1, 2 * size + 1), cv::Point(size, size));

    if (isDilation) {
        cv::dilate(inputImage, outputImage, element);
    }
    else {
        cv::erode(inputImage, outputImage, element);
    }

    if (!outputPath.empty()) {
        saveImage(outputPath, outputImage);
    }

    cv::imshow("Output Image", outputImage);
    cv::waitKey(0);
}

// Function to resize an image
void resizeImage(cv::Mat& inputImage, double scaleFactor, const std::string& outputPath = "") {
    cv::Mat outputImage;
    cv::resize(inputImage, outputImage, cv::Size(), scaleFactor, scaleFactor);

    if (!outputPath.empty()) {
        saveImage(outputPath, outputImage);
    }

    cv::imshow("Resized Image", outputImage);
    cv::waitKey(0);
}

// Function to lighten or darken an image
void lightenDarkenImage(cv::Mat& inputImage, double factor, const std::string& outputPath = "") {
    cv::Mat outputImage = inputImage + cv::Scalar(factor, factor, factor);

    if (!outputPath.empty()) {
        saveImage(outputPath, outputImage);
    }

    cv::imshow("Modified Image", outputImage);
    cv::waitKey(0);
}

// Function to apply Canny edge detection to an image
void cannyEdgeDetection(cv::Mat& inputImage, double threshold1, double threshold2, const std::string& outputPath = "") {
    cv::Mat edges;
    cv::Canny(inputImage, edges, threshold1, threshold2);

    if (!outputPath.empty()) {
        saveImage(outputPath, edges);
    }

    cv::imshow("Canny Edges", edges);
    cv::waitKey(0);
}

// Function to create a panorama from multiple images
void createPanorama(std::vector<cv::Mat>& images, const std::string& outputPath = "") {
    if (images.size() < 2) {
        std::cout << "Error: Need at least two images to create a panorama." << std::endl;
        return;
    }

    cv::Mat panorama;
    cv::Stitcher::Mode mode = cv::Stitcher::SCANS;
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);

    // Debugging: Check if the images are correctly detected as stitchable
    for (size_t i = 0; i < images.size(); ++i) {
        std::vector<cv::KeyPoint> keypoints;
        cv::Mat descriptors;
        cv::Ptr<cv::ORB> orb = cv::ORB::create();
        orb->detectAndCompute(images[i], cv::noArray(), keypoints, descriptors);

        std::cout << "Image " << i << " has " << keypoints.size() << " keypoints." << std::endl;
    }

    cv::Stitcher::Status status = stitcher->stitch(images, panorama);

    if (status == cv::Stitcher::OK) {
        if (!outputPath.empty()) {
            saveImage(outputPath, panorama);
        }
        cv::imshow("Panorama Image", panorama);
        cv::waitKey(0);
        std::cout << "Panorama created successfully" << std::endl;
    }
    else {
        std::cout << "Error stitching images, error code = " << int(status) << std::endl;
        switch (status) {
        case cv::Stitcher::ERR_NEED_MORE_IMGS:
            std::cout << "Error: Need more images to create a panorama." << std::endl;
            break;
        case cv::Stitcher::ERR_HOMOGRAPHY_EST_FAIL:
            std::cout << "Error: Homography estimation failed." << std::endl;
            break;
        case cv::Stitcher::ERR_CAMERA_PARAMS_ADJUST_FAIL:
            std::cout << "Error: Camera parameters adjustment failed." << std::endl;
            break;
        default:
            std::cout << "Error: Unknown error." << std::endl;
            break;
        }
    }
}

// Function to rotate an image by a given angle
void rotateImage(cv::Mat& inputImage, double angle, const std::string& outputPath = "") {
    cv::Mat outputImage;
    cv::Point2f center(inputImage.cols / 2.0, inputImage.rows / 2.0);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::warpAffine(inputImage, outputImage, rotationMatrix, inputImage.size());

    if (!outputPath.empty()) {
        saveImage(outputPath, outputImage);
    }

    cv::imshow("Rotated Image", outputImage);
    cv::waitKey(0);
}

// Function to apply Gaussian blur to an image
void applyGaussianBlur(cv::Mat& inputImage, int kernelSize, const std::string& outputPath = "") {
    cv::Mat outputImage;
    cv::GaussianBlur(inputImage, outputImage, cv::Size(kernelSize, kernelSize), 0);

    if (!outputPath.empty()) {
        saveImage(outputPath, outputImage);
    }

    cv::imshow("Gaussian Blur", outputImage);
    cv::waitKey(0);
}

// Function to convert an image to grayscale
void convertToGrayscale(cv::Mat& inputImage, const std::string& outputPath = "") {
    cv::Mat outputImage;
    cv::cvtColor(inputImage, outputImage, cv::COLOR_BGR2GRAY);

    if (!outputPath.empty()) {
        saveImage(outputPath, outputImage);
    }

    cv::imshow("Grayscale Image", outputImage);
    cv::waitKey(0);
}

// Function to apply auto contrast to an image
void autoContrast(cv::Mat& inputImage, const std::string& outputPath = "") {
    cv::Mat outputImage;
    cv::normalize(inputImage, outputImage, 0, 255, cv::NORM_MINMAX);

    if (!outputPath.empty()) {
        saveImage(outputPath, outputImage);
    }

    cv::imshow("Auto Contrast", outputImage);
    cv::waitKey(0);
}

//Function for video processing
void processVideo(const std::string& videoPath, const std::string& operation, double param1 = 0, double param2 = 0) {
    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        if (operation == "grayscale") {
            convertToGrayscale(frame);
        }
        else if (operation == "resize") {
            resizeImage(frame, param1);
        }
        else if (operation == "blur") {
            applyGaussianBlur(frame, static_cast<int>(param1));
        } // Add more operations as needed

        cv::imshow("Video", frame);
        if (cv::waitKey(30) >= 0) break;
    }
    cap.release();
    cv::destroyAllWindows();
}

//Function for face detection and recognition
void detectAndRecognizeFaces(cv::Mat& inputImage) {
    cv::CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

    if (faceCascade.empty()) {
        std::cerr << "Error: Could not load face cascade." << std::endl;
        return;
    }

    std::vector<cv::Rect> faces;
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    faceCascade.detectMultiScale(grayImage, faces);

    for (const auto& face : faces) {
        cv::rectangle(inputImage, face, cv::Scalar(255, 0, 0), 2);
    }

    cv::imshow("Face Detection", inputImage);
    cv::waitKey(0);
}
