#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

// Function to apply dilation or erosion to an image
// Parameters:
// - inputImage: the input image to be processed
// - size: the size of the structuring element used for dilation or erosion
// - isDilation: if true, applies dilation; if false, applies erosion
// - outputPath: optional path to save the output image
void applyDilationErosion(cv::Mat& inputImage, int size, bool isDilation, const std::string& outputPath);

// Function to resize an image
// Parameters:
// - inputImage: the input image to be resized
// - scaleFactor: the factor by which the image should be scaled
// - outputPath: optional path to save the output image
void resizeImage(cv::Mat& inputImage, double scaleFactor, const std::string& outputPath);

// Function to lighten or darken an image
// Parameters:
// - inputImage: the input image to be processed
// - factor: the factor by which to lighten (positive) or darken (negative) the image
// - outputPath: optional path to save the output image
void lightenDarkenImage(cv::Mat& inputImage, double factor, const std::string& outputPath);

// Function to apply Canny edge detection to an image
// Parameters:
// - inputImage: the input image to be processed
// - threshold1: the first threshold for the hysteresis procedure
// - threshold2: the second threshold for the hysteresis procedure
// - outputPath: optional path to save the output image
void cannyEdgeDetection(cv::Mat& inputImage, double threshold1, double threshold2, const std::string& outputPath);

// Function to create a panorama from multiple images
// Parameters:
// - images: a vector of images to be stitched together
// - outputPath: optional path to save the output panorama image
void createPanorama(std::vector<cv::Mat>& images, const std::string& outputPath);

/////////////////////// New functions///////////////////////////////////////////////////////

// Function to rotate an image by a given angle
// Parameters:
// - inputImage: the input image to be rotated
// - angle: the angle by which to rotate the image
// - outputPath: optional path to save the output image
void rotateImage(cv::Mat& inputImage, double angle, const std::string& outputPath);

// Function to apply Gaussian blur to an image
// Parameters:
// - inputImage: the input image to be blurred
// - kernelSize: the size of the Gaussian kernel
// - outputPath: optional path to save the output image
void applyGaussianBlur(cv::Mat& inputImage, int kernelSize, const std::string& outputPath);

// Function to convert an image to grayscale
// Parameters:
// - inputImage: the input image to be converted to grayscale
// - outputPath: optional path to save the output image
void convertToGrayscale(cv::Mat& inputImage, const std::string& outputPath);

// Function to apply auto contrast to an image
// Parameters:
// - inputImage: the input image to be processed
// - outputPath: optional path to save the output image
void autoContrast(cv::Mat& inputImage, const std::string& outputPath);

// Function to process a video file
// Parameters:
// - videoPath: the path to the video file to be processed
// - operation: the operation to be applied to each frame of the video (e.g., "grayscale", "resize", "blur")
// - param1: an optional parameter for the operation
// - param2: an optional parameter for the operation
void processVideo(const std::string& videoPath, const std::string& operation, double param1, double param2);

// Function to detect and recognize faces in an image
// Parameters:
// - inputImage: the input image in which to detect faces
void detectAndRecognizeFaces(cv::Mat& inputImage);

#endif // IMAGE_PROCESSING_H
