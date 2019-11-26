/**
 * 更多形态转化
 * 1. Opening
 *  - 侵蚀后扩张
 *  - 作用：去除小物体（白色）
 * 2. Closing
 *  - 扩张后侵蚀
 *  - 作用：去除小孔（黑色）
 * 3. Morphological Gradient
 *  - 扩张减侵蚀
 *  - 作用：物体轮廓检测
 * 4. Top Hat
 *  - 源减 Opening
 *  - 作用：顶帽运算往往用来分离比邻近点亮一些的斑块，在一幅图像具有大幅的背景，而微小物品比较有规律的情况下，可以使用顶帽运算进行背景提取
 * 5. Black Hat
 *  - 源减 Closing
 *  - 作用：黑帽运算后的效果图突出了比原图轮廓周围的区域更暗的区域，黑帽运算用来分离比临近点暗一点的斑块，效果图有着非常完美的轮廓
 */

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

/// Global variables
Mat src, dst;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

const char *window_name = "Morphology Transformations Demo";


void Morphology_Operations(int, void *);

int main(int argc, char *argv[]) {
    //![load]
    CommandLineParser parser(argc, argv, "{@input | baboon.jpg | input image}");
    src = imread(samples::findFile(parser.get<String>("@input")), IMREAD_COLOR);
    if (src.empty()) {
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return EXIT_FAILURE;
    }
    //![load]

    //![window]
    namedWindow(window_name, WINDOW_AUTOSIZE); // Create window
    //![window]

    //![create_trackbar1]
    /// Create Trackbar to select Morphology operation
    createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name,
                   &morph_operator, max_operator, Morphology_Operations);
    //![create_trackbar1]

    //![create_trackbar2]
    /// Create Trackbar to select kernel type
    createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
                   &morph_elem, max_elem,
                   Morphology_Operations);
    //![create_trackbar2]

    //![create_trackbar3]
    /// Create Trackbar to choose kernel size
    createTrackbar("Kernel size:\n 2n +1", window_name,
                   &morph_size, max_kernel_size,
                   Morphology_Operations);
    //![create_trackbar3]

    /// Default start
    Morphology_Operations(0, 0);

    waitKey(0);
    return 0;
}

//![morphology_operations]
/**
 * @function Morphology_Operations
 */
void Morphology_Operations(int, void *) {
    // Since MORPH_X : 2,3,4,5 and 6
    //![operation]
    int operation = morph_operator + 2;
    //![operation]

    Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1),
                                        Point(morph_size, morph_size));

    /// Apply the specified morphology operation
    morphologyEx(src, dst, operation, element);
    imshow(window_name, dst);
}
//![morphology_operations]
