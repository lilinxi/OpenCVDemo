/**
 * 减少色彩空间。这意味着我们将颜色空间当前值与新的输入值分开，以减少颜色。例如：0~9->0，10~19->10
 */

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

// 下标访问：最有效
Mat &ScanImageAndReduceC(Mat &I, const uchar *table);

// 迭代器访问：迭代程序方法被认为是更安全的方式
Mat &ScanImageAndReduceIterator(Mat &I, const uchar *table);

// 随机访问：指定要访问的项目的行号和列号
Mat &ScanImageAndReduceRandomAccess(Mat &I, const uchar *table);

// LUT：OpenCV 提供了修改图像值的功能，无需编写图像的扫描逻辑
Mat &ScanImageAndReduceUsingLUT(Mat &I, Mat &J, const uchar *const table);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    I = imread(argv[1], IMREAD_COLOR);

    if (I.empty()) {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    //! [dividewith]
    int divideWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> divideWith;
    if (!s || !divideWith) {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    // 计算查找表
    uchar table[256];
    for (int i = 0; i < 256; ++i) {
        table[i] = (uchar) (divideWith * (i / divideWith));
    }
    //! [dividewith]

    // 如何衡量时间？那么OpenCV提供了两个简单的函数来实现这个cv :: getTickCount（）和cv ::getTickFrequency（）。
    // 第一个从某个事件返回系统CPU的刻度数（就像您启动系统一样）。第二次返回您的CPU在一秒钟内发出多少次刻录。
    const int times = 100;
    double t;

    t = (double) getTickCount();
    for (int i = 0; i < times; ++i) {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i, table);
    }
    t = 1000 * ((double) getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with the C operator [] (averaged for "
         << times << " runs): " << t << " milliseconds." << endl;
    // create window
    // If a window with the same name already exists, the function does nothing.
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    // show image
    // If the window was not created before this function, it is assumed creating a window with cv::WINDOW_AUTOSIZE.
    imshow("Display Image(1)", J);
    waitKey(1000);

    t = (double) getTickCount();
    for (int i = 0; i < times; ++i) {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceIterator(clone_i, table);
    }
    t = 1000 * ((double) getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with the iterator (averaged for "
         << times << " runs): " << t << " milliseconds." << endl;
    imshow("Display Image(2)", J);
    waitKey(1000);

    t = (double) getTickCount();
    for (int i = 0; i < times; ++i) {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceRandomAccess(clone_i, table);
    }
    t = 1000 * ((double) getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
         << times << " runs): " << t << " milliseconds." << endl;
    imshow("Display Image(3)", J);
    waitKey(1000);

    //! [table-init]
    Mat lookUpTable(1, 256, CV_8U);
    uchar *p = lookUpTable.ptr();
    for (int i = 0; i < 256; ++i)
        p[i] = table[i];
    //! [table-init]
    t = (double) getTickCount();
    for (int i = 0; i < times; ++i) {
        //! [table-use]
        LUT(I, lookUpTable, J);
        //! [table-use]
    }
    t = 1000 * ((double) getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with the LUT function (averaged for "
         << times << " runs): " << t << " milliseconds." << endl;
    imshow("Display Image(4)", J);
    waitKey(1000);

    t = (double) getTickCount();
    for (int i = 0; i < times; ++i) {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceUsingLUT(clone_i, J, table);
    }
    t = 1000 * ((double) getTickCount() - t) / getTickFrequency();
    t /= times;
    cout << "Time of reducing with the LUT function (averaged for "
         << times << " runs): " << t << " milliseconds." << endl;
    imshow("Display Image(5)", J);
    waitKey(1000);

    destroyAllWindows();
    return 0;
}

//! [scan-c]
Mat &ScanImageAndReduceC(Mat &I, const uchar *const table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    int i, j;
    uchar *p;
    for (i = 0; i < nRows; ++i) {
        p = I.ptr<uchar>(i);
        for (j = 0; j < nCols; ++j) {
            p[j] = table[p[j]];
        }
    }
    return I;
}
//! [scan-c]

//! [scan-iterator]
Mat &ScanImageAndReduceIterator(Mat &I, const uchar *const table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch (channels) {
        case 1: {
            MatIterator_<uchar> it, end;
            for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it) {
                *it = table[*it];
            }
            break;
        }
        case 3: {
            MatIterator_<Vec3b> it, end;
            for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    return I;
}
//! [scan-iterator]

//! [scan-random]
Mat &ScanImageAndReduceRandomAccess(Mat &I, const uchar *const table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch (channels) {
        case 1: {
            for (int i = 0; i < I.rows; ++i) {
                for (int j = 0; j < I.cols; ++j) {
                    I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
                }
            }
            break;
        }
        case 3: {
            Mat_<Vec3b> _I = I;

            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j) {
                    _I(i, j)[0] = table[_I(i, j)[0]];
                    _I(i, j)[1] = table[_I(i, j)[1]];
                    _I(i, j)[2] = table[_I(i, j)[2]];
                }
            I = _I;
            break;
        }
    }

    return I;
}
//! [scan-random]

//! [scan-LUT]
Mat &ScanImageAndReduceUsingLUT(Mat &I, Mat &J, const uchar *const table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    //! [table-init]
    Mat lookUpTable(1, 256, CV_8U);
    uchar *p = lookUpTable.ptr();
    for (int i = 0; i < 256; ++i) {
        p[i] = table[i];
    }
    //! [table-init]

    //! [table-use]
    LUT(I, lookUpTable, J);
    //! [table-use]

    return J;
}
//! [scan-LUT]
