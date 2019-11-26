/**
 * 输入输出，访问图像像素，内存管理和引用计数，截取和灰度、色彩空间转换，可视化
 */

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    std::string filename = "./lena.jpg";
    // 输入和输出
    {
        //! [Load an image from a file]
        Mat img = imread(filename);
        //! [Load an image from a file]
        CV_UNUSED(img);
    }
    {
        //! [Load an image from a file in grayscale]
        Mat img = imread(filename, IMREAD_GRAYSCALE);
        //! [Load an image from a file in grayscale]
        CV_UNUSED(img);
    }
    {
        Mat img(4, 4, CV_8U);
        //! [Save image]
        imwrite("imwrite.jpg", img);
        //! [Save image]
    }
    // 访问图像强度
    {
        Mat img(4, 4, CV_8U);
        int y = 0, x = 0;
        {
            //! [Pixel access 1]
            Scalar intensity = img.at<uchar>(y, x);
            //! [Pixel access 1]
            CV_UNUSED(intensity);
        }
        {
            //! [Pixel access 2]
            Scalar intensity = img.at<uchar>(Point(x, y));
            //! [Pixel access 2]
            CV_UNUSED(intensity);
        }
        {
            //! [Pixel access 3]
            Vec3b intensity = img.at<Vec3b>(y, x);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
            //! [Pixel access 3]
            CV_UNUSED(blue);
            CV_UNUSED(green);
            CV_UNUSED(red);
        }
        {
            //! [Pixel access 4]
            Vec3f intensity = img.at<Vec3f>(y, x);
            float blue = intensity.val[0];
            float green = intensity.val[1];
            float red = intensity.val[2];
            //! [Pixel access 4]
            CV_UNUSED(blue);
            CV_UNUSED(green);
            CV_UNUSED(red);
        }
        {
            //! [Pixel access 5]
            img.at<uchar>(y, x) = 128;
            //! [Pixel access 5]
        }
        {
            int i = 0;
            //! [Mat from points vector]
            vector<Point2f> points;
            //... fill the array
            points.push_back(Point2f());
            Mat pointsMat = Mat(points);
            //! [Mat from points vector]

            //! [Point access]
            Point2f point = pointsMat.at<Point2f>(i, 0);
            //! [Point access]
            CV_UNUSED(point);
        }
    }
    // 内存管理和引用计数
    {
        // 不复制
        //! [Reference counting 1]
        std::vector<Point3f> points;
        // .. fill the array
        Mat pointsMat = Mat(points).reshape(1);
        //! [Reference counting 1]
        CV_UNUSED(pointsMat);
    }
    {
        //! [Reference counting 2]
        Mat img = imread("image.jpg");
        Mat img1 = img.clone();
        //! [Reference counting 2]
        CV_UNUSED(img1);
    }
    {
        // C-API，必须由开发人员创建输出图像，可以向每个功能提供空输出Mat。每个实现都为目标矩阵调用Mat :: create。如果矩阵为空，则此方法分配数据。如果它不是空且具有正确的大小和类型，该方法什么都不做。然而，如果大小或类型与输入参数不同，则数据被释放（并丢失）并分配新的数据。
        //! [Reference counting 3]
        Mat img = imread(filename);
        Mat sobelx;
        Sobel(img, sobelx, CV_32F, 1, 0);
        //! [Reference counting 3]
    }
    // 原始操作
    {
        Mat img = imread(filename);
        {
            //! [Set image to black]
            img = Scalar(0);
            //! [Set image to black]
        }
        {
            //! [Select ROI]
            Rect r(10, 10, 100, 100);
            Mat smallImg = img(r);
            //! [Select ROI]
            CV_UNUSED(smallImg);
        }
    }
    {
        //! [BGR to Gray]
        Mat img = imread(filename); // loading a 8UC3 image
        Mat grey;
        cvtColor(img, grey, COLOR_BGR2GRAY);
        //! [BGR to Gray]
    }
    {
        Mat dst, src;
        src = imread(filename);
        //! [Convert to CV_32F]
        src.convertTo(dst, CV_32F);
        //! [Convert to CV_32F]
    }
    // 可视化图像
    {
        //! [imshow 1]
        Mat img = imread(filename);
        namedWindow("image", WINDOW_AUTOSIZE);
        imshow("image", img);
        waitKey(1000);
        //! [imshow 1]
    }
    {
        //! [imshow 2]
        Mat img = imread(filename);
        Mat grey;
        cvtColor(img, grey, COLOR_BGR2GRAY);
        Mat sobelx;
        Sobel(grey, sobelx, CV_32F, 1, 0);
        double minVal, maxVal;
        minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
        Mat draw;
        sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
        namedWindow("image", WINDOW_AUTOSIZE);
        imshow("image", draw);
        waitKey(1000);
        //! [imshow 2]
    }

    return 0;
}
