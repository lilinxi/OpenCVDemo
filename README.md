# catalog

## starting

1. UsingOpenCV
    
## core

- 核心功能模块

1. UsingMat
2. ScanningImages：[使用查找表（LUT）缩减色彩空间（color space reduction）](https://blog.csdn.net/wonder_coole/article/details/80541725)
    - 为了减少色彩总量，降低软硬件消耗
    - 色彩空间，色温，伽马
3. UsingMask：根据掩码矩阵（也称为内核）重新计算图像中的每个像素值（filter2D()）
4. ImageOperation：输入输出，访问图像像素(at<uchar>())，内存管理和引用计数(CV_UNUSED()，截取和灰度(cvtColor())、色彩空间转换(convertTo())，可视化
5. AddingImages：图像混合（addWeighted()），samples::findFile()
6. LinearTransforms：线性变换
    1. 亮度（α)和对比度调整（β），g(x)=αf(x)+β，Using convertTo()
    2. 伽马矫正，Using LUT()
    3. saturate_cast<uchar>()：转化为uchar（0~255）
    4. Using CommandLineParser()
7. DiscreteFourierTransform：离散傅里叶变换
    1. 将图像展开至最佳尺寸：getOptimalDFTSize()，copyMakeBorder()
    2. 转换为 float 并增加虚数通道：Mat_<float>()，merge()
    3. 离散傅里叶变换：dft()
    4. 转换复数为大小：split()，magnitude()
    5. 转换到对数刻度：log()
    6. 裁剪和重新排列，将原点移到中心：Rect()，copyTo()
        - 奇数裁剪为偶数（& -2(11111……10)：7->6）
    7. 标准化：normalize()
8. XMLAndYAML：序列化：XML 和 YAML
    1. FileStorage，FileNode
    2. 读写：OpenCV 数据结构，向量/数组和 Map，自定义数据结构
9. 并行：ParallelFor 框架（parallel_for_(C++11), ParallelLoopBody）：绘制一个 Mandelbrot 集
    
## imgproc

- 图像处理模块，其主要包括图像滤波、几何变换、直方图、特征检测与目标检测

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
4. ErodingAndDilating：形态操作将结构元素应用于输入图像并生成输出图像。最基本的形态作用是：侵蚀（erode，最小值滤波）和扩张（dilate，最大值滤波）
    - 作用：1. 消除噪音；2. 隔离单个元素并连接图像中的不同元素；3. 查找图像中的强度凸点或孔
    - createTrackbar(), getStructuringElement(), erode(), dilate()
    - Element（核形状）：矩形框，十字架，椭圆
5. AdvanceMorphology：更多形态转化
    1. Opening：侵蚀后扩张
        - 作用：去除小物体（白色）
    2. Closing：扩张后侵蚀
        - 作用：去除小孔（黑色）
    3. Morphological Gradient：扩张减侵蚀
        - 作用：物体轮廓检测
    4. Top Hat：源减 Opening
        - 作用：顶帽运算往往用来分离比邻近点亮一些的斑块，在一幅图像具有大幅的背景，而微小物品比较有规律的情况下，可以使用顶帽运算进行背景提取
    5. Black Hat：源减 Closing
        - 作用：黑帽运算后的效果图突出了比原图轮廓周围的区域更暗的区域，黑帽运算用来分离比临近点暗一点的斑块，效果图有着非常完美的轮廓
6. HitOrMiss：匹配查找和不匹配查找
7. HorizontalAndVertical：使用形态学操作来提取水平和垂直线
    - 二值：adaptiveThreshold()
    - 反相：bitwise_not()
8. ImagePyramids：图像金字塔：pyrDown and pyrUp
9. BasicThresholding：基本阈值操作(threshold())：分离对应于我们想要分析的对象的图像的区域。该分离基于对象像素和背景像素之间的强度变化。
    1. 阈值二进制
    2. 阈值二进制，倒数
    3. 截短
    4. 阈值为零
    5. 阈值为零，倒数
10. ThresholdingInRange：阈值操作(inRange())，setTrackbarPos()
11. LinearFilters：线性滤波：filter2D()
12. AddingBorders：增加边框：copyMakeBorder(), BORDER_CONSTANT, BORDER_REPLICATE
13. SobelDerivatives：Sobel 衍生物：Sobel(ksize, scale, delta), Scharr(ksize=3, scale, delta), convertScaleAbs()
14. LaplaceOperator：拉普拉斯算子
    1. GaussianBlur()
    2. cvtColor()
    3. Laplacian()
    4. convertScaleAbs()
15. CannyEdgeDetector：Canny 边缘检测
    - 标准：
        1. 低错误率：意味着只有现有边缘的良好检测。
        2. 良好的定位：检测到的边缘像素与实际边缘像素之间的距离必须最小化。
        3. 最小响应：每个边缘只有一个检测器响应。
    - 步骤：
        1. 滤除任何噪音（高斯滤波）
        2. 求图像强度梯度，查找梯度方向（Sobel）
        3. 非最大抑制
        4. 双阈值检验
16. HoughLineTransform：霍夫直线变换：
    - 标准 Hough 变换：HoughLines()
    - 概率 Hough 变换：HoughLinesP()，更有效
17. HoughCircleTransform：霍夫圆变换：HoughCircles()
18. Remapping：重新映射：remap(map_x, map_y)
19. AffineTransformations：仿射变换：warpAffine()
    1. Rotations (linear transformation)：getRotationMatrix2D()
    2. Translations (vector addition)：getAffineTransform()
    3. Scale operations (linear transformation)：getRotationMatrix2D()
20. HistogramEqualization：直方图均衡化：equalizeHist()
21. HistogramCalculation：计算直方图
    1. split()：将图像分割成对应的通道
    2. calcHist()：来计算图像数组的直方图
    3. normalize()：对数组进行归一化
22. HistogramComparison：直方图比较：compareHist()
    1. Correlation ( CV_COMP_CORREL )
    2. Chi-Square ( CV_COMP_CHISQR )
    3. Intersection ( method=CV_COMP_INTERSECT )
    4. Intersection ( method=CV_COMP_INTERSECT )
23. BackProjection：反向投影
    1. 转换为 HSV 格式
    2. mixChannels()：提取 H 或 H-S
    3. calcBackProject()：反向投影
24. MatchingTemplate：模板匹配
    1. matchTemplate(img_tmpl, tmpl, (mask))：搜索匹配
    2. minMaxLoc()：求数组最大，最小值的位置（根据算法可能是最大匹配或最小匹配，但是不一定是极值匹配）
25. FindingContours：查找轮廓（轮廓是边缘的一部分）：findContours(), drawContours()
26. ConvexHull：凸包：convexHull()
27. CreatingBounding：为轮廓创建边界框和圆：boundingRect(), minEnclosingCircle()
    - approxPolyDP()：把一个连续光滑曲线折线化
28. CreatingBounding2：为轮廓创建边界框（旋转）和椭圆：minAreaRect(), fitEllipse()
29. ImageMoments：图像特征：
    - moments()：计算图像中心矩（最高三阶）
    - contourArea()：计算轮廓面积
    - arcLength()：计算封闭轮廓的周长或曲线的长度
30. PointPolygonTest：点多边形测试：pointPolygonTest()，判断点在轮廓上，内，外，或者到轮廓的最近距离
31. DistanceImageSegmentation：图像距离分割：
    - distanceTransform()：计算图像中每一个非零点距离离自己最近的零点的距离
    - watershed()：分水岭算法，分离前景和背景

## highgui

- 高层GUI图形用户界面

1. AddingTrackbar：添加跟踪栏：createTrackbar(), CallbackFunc(int, void *)

## imgcodecs

- 用GDAL读取地理空间栅格文件

## videoio

- 视频输入输出

## calib3d

- 相机校准和 3D 重建

## feature2d

- 2D 特征

## objdetect

- 对象检测

## dnn

- 深度神经网络

## ml

- 机器学习

## gapi

- 加速常规的图像处理

## photo

- 计算摄影

## stitching

- 图像拼接

## cuda

- GPU 加速计算机视觉

---

# References

- [OpenCV 教程(官网)](https://docs.opencv.org/master/d9/df8/tutorial_root.html)
    - [代码](https://github.com/opencv/opencv/tree/master/samples/cpp/tutorial_code)
- [OpenCV 教程(w3cschool)](https://www.w3cschool.cn/opencv/opencv-2gnx28u3.html)
- [OpenCV 教程(中文论坛)](http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/tutorials.html)