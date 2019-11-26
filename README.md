# catalog

1. starting
    1. UsingOpenCV
2. core
    1. UsingMat
    2. ScanningImages：[使用查找表（LUT）缩减色彩空间（color space reduction）](https://blog.csdn.net/wonder_coole/article/details/80541725)
        - 为了减少色彩总量，降低软硬件消耗
        - 色彩空间，色温，伽马
    3. UsingMask：根据掩码矩阵（也称为内核）重新计算图像中的每个像素值（filter2D()）
    4. ImageOperation：输入输出，访问图像像素，内存管理和引用计数，截取和灰度、色彩空间转换，可视化
    5. AddingImages：图像混合（addWeighted()），samples::findFile()
    5. LinearTransforms：线性变换
        1. 亮度（α)和对比度调整（β），g(x)=αf(x)+β，Using convertTo()
        2. 伽马矫正，Using LUT()
        3. saturate_cast<uchar>()：转化为uchar（0~255）
        4. Using CommandLineParser()
    6. DiscreteFourierTransform：离散傅里叶变换
        1. 将图像展开至最佳尺寸：getOptimalDFTSize()，copyMakeBorder()
        2. 转换为 float 并增加虚数通道：Mat_<float>()，merge()
        3. 离散傅里叶变换：dft()
        4. 转换复数为大小：split()，magnitude()
        5. 转换到对数刻度：log()
        6. 裁剪和重新排列，将原点移到中心：Rect()，copyTo()
            - 奇数裁剪为偶数（& -2(11111……10)：7->6）
        7. 标准化：normalize()
    7. XMLAndYAML：序列化：XML 和 YAML
        1. FileStorage，FileNode
        2. 读写：OpenCV 数据结构，向量/数组和 Map，自定义数据结构
    8. 并行：ParallelFor 框架（parallel_for_(C++11), ParallelLoopBody）：绘制一个 Mandelbrot 集
3. imgproc
    1. BasicDrawing：基础绘图：Point()，Scalar()，line()，rectangle()，ellipse()，circle()，fillPoly()
    2. RandomAndText：随机和文本
        - 随机数生成器：RNG.uniform()
        - 绘制文本：putText()，getTextSize()
    3. Smoothing：平滑图像
        1. 归一化滤波：blur()
        2. 高斯滤波：GaussianBlur()
        3. 中值滤波：medianBlur()
        4. 双边滤波（保护边缘）：bilateralFilter()
            - 其他滤波会模糊图片的边缘细节，对于高频细节的保护效果并不明显；双边滤波可以在去噪的同时，保护图像的边缘特性
    4. ErodingAndDilating

---

# References

- [OpenCV 教程(官网)](https://docs.opencv.org/master/d9/df8/tutorial_root.html)
    - [代码](https://github.com/opencv/opencv/tree/master/samples/cpp/tutorial_code)
- [OpenCV 教程(w3cschool)](https://www.w3cschool.cn/opencv/opencv-2gnx28u3.html)
- [OpenCV 教程(中文论坛)](http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/tutorials.html)