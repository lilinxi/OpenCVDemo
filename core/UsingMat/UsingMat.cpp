/**
 * The first thing you need to know about Mat is that you no longer need to manually allocate its memory and release it as soon as you do not need it. While doing this is still a possibility, most of the OpenCV functions will allocate its output data automatically. As a nice bonus if you pass on an already existing Mat object, which has already allocated the required space for the matrix, this will be reused. In other words we use at all times only as much memory as we need to perform the task.
 */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage: DisplayImage.out <Image_Path>" << endl;
        return -1;
    }

    // Mat
    {
        Mat A, C;                          // creates just the header parts
        A = imread(argv[1], IMREAD_COLOR); // here we'll know the method used (allocate matrix)
        Mat B(A);                                 // Use the copy constructor
        C = A;                                    // Assignment operator

        // a subsection of the full data
        Mat D(A, Rect(50, 50, 100, 100)); // using a rectangle
        Mat E = A(Range::all(), Range(50, 200)); // using row and column boundaries

        // 赋值运算符和复制构造函数只复制标题
        Mat F = A.clone();
        Mat G;
        A.copyTo(G);

        namedWindow("Display Image", WINDOW_AUTOSIZE);
        imshow("Display Image", E);
        waitKey(1000);
    }

    // 明确创建一个Mat对象
    {
        // 我们需要指定用于存储元素的数据类型和每个矩阵点的通道数，CV_8UC3意味着我们使用8位长的无符号字符类型，每个像素有三个形成三个通道
        Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
        cout << "M(1) =" << endl << " " << M << endl << endl;

        // 多于二维的矩阵无法显示
        int sz[3] = {2, 2, 2};
        Mat L(3, sz, CV_8UC(1), Scalar::all(0));

        M.create(4, 4, CV_8UC(2));
        cout << "M(2) = " << endl << " " << M << endl << endl;

        // MATLAB 样式初始化器：zeros，ones，eye
        Mat E = Mat::eye(4, 4, CV_64F);
        cout << "E = " << endl << " " << E << endl << endl;
        Mat O = Mat::ones(2, 2, CV_32F);
        cout << "O = " << endl << " " << O << endl << endl;
        Mat Z = Mat::zeros(3, 3, CV_8UC1);
        cout << "Z = " << endl << " " << Z << endl << endl;

        // 对于小矩阵，您可以使用逗号分隔的初始化器或初始化器列表
        Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
        cout << "C(1) = " << endl << " " << C << endl << endl;
        // 需要 C++11 支持
#ifdef CV_CXX11
        C = (Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3);
        cout << "C(2) = " << endl << " " << C << endl << endl;
#endif

        Mat RowClone = C.row(1).clone();
        cout << "RowClone = " << endl << " " << RowClone << endl << endl;

        // 随机矩阵
        Mat R = Mat(3, 2, CV_8UC3);
        randu(R, Scalar::all(0), Scalar::all(255));
        cout << "R = " << endl << " " << R << endl << endl;
    }

    // 输出格式
    {
        Mat R = Mat(3, 2, CV_8UC3);
        randu(R, Scalar::all(0), Scalar::all(255));

        cout << "R (default) = " << endl << R << endl << endl;
        cout << "R (python)  = " << endl << format(R, Formatter::FMT_PYTHON) << endl << endl;
        cout << "R (csv)     = " << endl << format(R, Formatter::FMT_CSV) << endl << endl;
        cout << "R (numpy)   = " << endl << format(R, Formatter::FMT_NUMPY) << endl << endl;
        cout << "R (c)       = " << endl << format(R, Formatter::FMT_C) << endl << endl;
    }

    // 输出常用数据结构
    {
        Point2f P(5, 1);
        cout << "Point (2D) = " << P << endl << endl;

        Point3f P3f(2, 6, 7);
        cout << "Point (3D) = " << P3f << endl << endl;

        vector<float> v;
        v.push_back((float) CV_PI);
        v.push_back(2);
        v.push_back(3.01f);
        cout << "Vector of floats via Mat = " << Mat(v) << endl << endl;

        vector<Point2f> vPoints(20);
        for (size_t i = 0; i < vPoints.size(); ++i) {
            vPoints[i] = Point2f((float) (i * 5), (float) (i % 7));
        }
        cout << "A vector of 2D Points = " << vPoints << endl << endl;
    }

    return 0;
}