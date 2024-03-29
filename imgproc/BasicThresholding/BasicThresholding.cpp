/**
 * 基本阈值操作：分离对应于我们想要分析的对象的图像的区域。该分离基于对象像素和背景像素之间的强度变化。
 * 1. 阈值二进制
 * 2. 阈值二进制，倒数
 * 3. 截短
 * 4. 阈值为零
 * 5. 阈值为零，倒数
 */

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using std::cout;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

Mat src, src_gray, dst;
const char *window_name = "Threshold Demo";

const char *trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char *trackbar_value = "Value";

//![Threshold_Demo]
static void Threshold_Demo(int, void *) {
    /*
     0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */
    threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
    imshow(window_name, dst);
}
//![Threshold_Demo]

int main(int argc, char *argv[]) {
    //! [load]
    String imageName("chicky_512.png"); // by default
    if (argc > 1) {
        imageName = argv[1];
    }
    src = imread(samples::findFile(imageName), IMREAD_COLOR); // Load an image

    if (src.empty()) {
        cout << "Cannot read the image: " << imageName << std::endl;
        return -1;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
    //! [load]

    //! [window]
    namedWindow(window_name, WINDOW_AUTOSIZE); // Create a window to display results
    //! [window]

    //! [trackbar]
    createTrackbar(trackbar_type,
                   window_name, &threshold_type,
                   max_type, Threshold_Demo); // Create a Trackbar to choose type of Threshold

    createTrackbar(trackbar_value,
                   window_name, &threshold_value,
                   max_value, Threshold_Demo); // Create a Trackbar to choose Threshold value
    //! [trackbar]

    Threshold_Demo(0, 0); // Call the function to initialize

    /// Wait until the user finishes the program
    waitKey();
    return 0;
}
