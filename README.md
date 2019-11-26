# catalog

1. starting
    1. UsingOpenCV
2. core
    1. UsingMat
    2. ScanningImages：[使用查找表（LUT）缩减色彩空间（color space reduction）](https://blog.csdn.net/wonder_coole/article/details/80541725)
        - 为了减少色彩总量，降低软硬件消耗
        - 色彩空间，色温，伽马
    3. UsingMask：根据掩码矩阵（也称为内核）重新计算图像中的每个像素值（filter2D）
    4. ImageOperation：输入输出，访问图像像素，内存管理和引用计数，截取和灰度、色彩空间转换，可视化
    5. AddingImages：图像混合（addWeighted），samples::findFile
    5. LinearTransforms：线性变换
        1. 亮度（α)和对比度调整（β），g(x)=αf(x)+β，Using convertTo
        2. 伽马矫正，Using LUT
        3. saturate_cast：转化为uchar（0~255）
3. imgproc
    1. 基础绘图：Point，Scalar，line，rectangle，ellipse，circle，fillPoly

---

# References

- [OpenCV 教程(官网)](https://docs.opencv.org/master/d9/df8/tutorial_root.html)
    - [代码](https://github.com/opencv/opencv/tree/master/samples/cpp/tutorial_code)
- [OpenCV 教程(w3cschool)](https://www.w3cschool.cn/opencv/opencv-2gnx28u3.html)
- [OpenCV 教程(中文论坛)](http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/tutorials.html)