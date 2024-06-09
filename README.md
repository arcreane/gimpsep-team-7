# fadobe

Overview
This application provides a suite of image processing operations utilizing OpenCV. The functionalities include image dilation, erosion, resizing, lightening, darkening, edge detection, panorama creation, rotation, Gaussian blur application, grayscale conversion, auto contrast, video processing, and face detection. Each operation can be performed through command-line arguments.

Prerequisites
Ensure you have the following installed on your system:

C++ compiler (e.g., g++, clang++)
OpenCV library
Visual Studio 2022


Then you need to build and run the application

Here are examples of all the command for the operations :

-canny test.jpg 100 200
-dilate test.jpg 5
-erode test.jpg 3
-resize test.jpg 0.5
-lighten test.jpg 50
-darken test.jpg -50

-rotate test.jpg 45
-blur test.jpg 15
-grayscale test.jpg
-autocontrast test.jpg

-video Video.mp4 grayscale
-recognize FaceGIMP.jpg

-panorama goldengate.png goldengate2.png goldengate3.png goldengate4.png

If you want to save the image, add output.jpg to the command, for example:

dilate test.jpg 5 output.jpg

