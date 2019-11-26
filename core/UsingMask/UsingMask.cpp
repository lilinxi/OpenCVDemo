/**
 * 根据掩码矩阵（也称为内核）重新计算图像中的每个像素值。
 */

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// OpenCV 's filter2D is slower
void Sharpen(const Mat &myImage, Mat &Result);

int main(int argc, char *argv[]) {
    const char *filename = argc >= 2 ? argv[1] : "./lena.jpg";

    Mat src, dst0, dst1;
    src = imread( samples::findFile( filename ), IMREAD_COLOR);

    if (src.empty()) {
        cerr << "Can't open image [" << filename << "]" << endl;
        return EXIT_FAILURE;
    }

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    imshow("Input", src);

    double t = (double) getTickCount();
    Sharpen(src, dst0);
    t = ((double) getTickCount() - t) / getTickFrequency();
    cout << "Hand written function time passed in seconds: " << t << endl;
    imshow("Output", dst0);
    waitKey(1000);

    //![kern]
    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
            -1, 5, -1,
            0, -1, 0);
    //![kern]
    t = (double) getTickCount();
    //![filter2D]
    filter2D(src, dst1, src.depth(), kernel);
    //![filter2D]
    t = ((double) getTickCount() - t) / getTickFrequency();
    cout << "Built-in filter2D time passed in seconds:     " << t << endl;
    imshow("Output", dst1);
    waitKey(1000);

    return EXIT_SUCCESS;
}

//! [basic_method]
void Sharpen(const Mat &myImage, Mat &Result) {
    //! [8_bit]
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
    //! [8_bit]

    //! [create_channels]
    const int nChannels = myImage.channels();
    Result.create(myImage.size(), myImage.type());
    //! [create_channels]

    //! [basic_method_loop]
    for (int j = 1; j < myImage.rows - 1; ++j) {
        const uchar *previous = myImage.ptr<uchar>(j - 1);
        const uchar *current = myImage.ptr<uchar>(j);
        const uchar *next = myImage.ptr<uchar>(j + 1);

        uchar *output = Result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i) {
            *output++ = saturate_cast<uchar>(5 * current[i]
                                             - current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
        }
    }
    //! [basic_method_loop]

    //! [borders]
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows - 1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));
    //! [borders]
}
//! [basic_method]
