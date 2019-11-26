/**
 * 使用形态学操作来提取水平和垂直线
 * 1. 灰度
 * 2. 二值：adaptiveThreshold()
 * 3. 提取水平边缘（水平核）
 * 4. 提取垂直边缘（垂直核）
 * 5. 反相：bitwise_not()
 * // 1. extract edges
 * // 2. dilate(edges)
 * // 3. src.copyTo(smooth)
 * // 4. blur smooth img
 * // 5. smooth.copyTo(src, edges)
 */

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    //! [load_image]
    CommandLineParser parser(argc, argv, "{@input | notes.png | input image}");
    Mat src = imread(samples::findFile(parser.get<String>("@input")), IMREAD_COLOR);
    if (src.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    // Show source image
    imshow("src", src);
    //! [load_image]

    //! [gray]
    // Transform source image to gray if it is not already
    Mat gray;

    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    } else {
        gray = src;
    }

    // Show gray image
    imshow("gray", gray);
    //! [gray]

    //! [bin]
    // Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
    Mat bw;
    // 将灰度图像转换为二进制。注意〜符号，表示我们使用它的逆（即bitwise_not）
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);

    // Show binary image
    imshow("binary", bw);
    //! [bin]

    //! [init]
    // Create the images that will use to extract the horizontal and vertical lines
    Mat horizontal = bw.clone();
    Mat vertical = bw.clone();
    //! [init]

    //! [horiz]
    // Specify size on horizontal axis
    int horizontal_size = horizontal.cols / 30;

    // Create structure element for extracting horizontal lines through morphology operations
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));

    // Apply morphology operations
    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));

    // Show extracted horizontal lines
    imshow("horizontal", horizontal);
    //! [horiz]

    //! [vert]
    // Specify size on vertical axis
    int vertical_size = vertical.rows / 30;

    // Create structure element for extracting vertical lines through morphology operations
    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));

    // Apply morphology operations
    erode(vertical, vertical, verticalStructure, Point(-1, -1));
    dilate(vertical, vertical, verticalStructure, Point(-1, -1));

    // Show extracted vertical lines
    imshow("vertical", vertical);
    //! [vert]

    //! [smooth]
    // Inverse vertical image
    bitwise_not(vertical, vertical);
    imshow("vertical_bit", vertical);

    // Extract edges and smooth image according to the logic
    // 1. extract edges
    // 2. dilate(edges)
    // 3. src.copyTo(smooth)
    // 4. blur smooth img
    // 5. smooth.copyTo(src, edges)

    // Step 1
    Mat edges;
    adaptiveThreshold(vertical, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
    imshow("edges", edges);

    // Step 2
    Mat kernel = Mat::ones(2, 2, CV_8UC1);
    dilate(edges, edges, kernel);
    imshow("dilate", edges);

    // Step 3
    Mat smooth;
    vertical.copyTo(smooth);

    // Step 4
    blur(smooth, smooth, Size(2, 2));

    // Step 5
    smooth.copyTo(vertical, edges);

    // Show final result
    imshow("smooth - final", vertical);
    //! [smooth]

    waitKey(0);
    return 0;
}