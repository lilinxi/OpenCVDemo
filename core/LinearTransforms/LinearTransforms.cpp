/**
 * 线性变换：
 * 1. 亮度（α)和对比度调整（β），g(x)=αf(x)+β，Using convertTo
 * 2. 伽马矫正，O = (I/255)^γ * 255，Using LUT
 * 3. saturate_cast：转化为uchar（0~255）
 */

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>

// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using namespace cv;

int main(int argc, char *argv[]) {
    /// Read image given by user
    //! [basic-linear-transform-load]
    // 第一部分是参数名称。第二部分是参数的默认值，可以为空。第三部分是描述该参数的帮助信息，可以为空。
    CommandLineParser parser(argc, argv, "{@input | ../lena.jpg | input image}");
    Mat image = imread(samples::findFile(parser.get<String>("@input")));
    if (image.empty()) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    //! [basic-linear-transform-load]

    //! [basic-linear-transform-output]
    Mat new_image = Mat::zeros(image.size(), image.type());
    //! [basic-linear-transform-output]

    //! [basic-linear-transform-parameters]
    double alpha = 1.0; /*< Simple contrast control */
    int beta = 0;       /*< Simple brightness control */

    /// Initialize values
    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: ";
    cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";
    cin >> beta;
    //! [basic-linear-transform-parameters]

    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    /// Instead of these 'for' loops we could have used simply:
    /// image.convertTo(new_image, -1, alpha, beta);
    /// but we wanted to show you how to access the pixels :)
    //! [basic-linear-transform-operation]
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int c = 0; c < image.channels(); c++) {
                new_image.at<Vec3b>(y, x)[c] =
                        saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
            }
        }
    }
    //! [basic-linear-transform-operation]

    imshow("Original Image", image);
    waitKey(1000);
    imshow("New Image", new_image);
    waitKey(1000);

    // Using convertTo
    Mat new_image_2 = Mat::zeros(image.size(), image.type());
    // if rtype is negative, the output matrix will have the same type as the input.
    image.convertTo(new_image_2, -1, alpha, beta);
    imshow("New Image(2)", new_image_2);
    waitKey(1000);

    Mat lookUpTable(1, 256, CV_8U);
    uchar *p = lookUpTable.ptr();
    float gamma_ = 2.2;
    for (int i = 0; i < 256; ++i) {
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);
    }
    Mat res = image.clone();
    LUT(image, lookUpTable, res);
    imshow("New Image(gamma)", res);
    waitKey(1000);

    return 0;
}
