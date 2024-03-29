/**
 * 序列化：XML 和 YAML
 * 1. FileStorage，FileNode
 * 2. 读写：OpenCV 数据结构，向量/数组和 Map，自定义数据结构
 */

#include <opencv2/core.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class MyData {
public:
    MyData() : A(0), X(0), id() {}

    explicit MyData(int) : A(97), X(CV_PI), id("mydata1234") // explicit to avoid implicit conversion
    {}

    void write(FileStorage &fs) const                        //Write serialization for this class
    {
        fs << "{" << "A" << A << "X" << X << "id" << id << "}";
    }

    void read(const FileNode &node)                          //Read serialization for this class
    {
        A = (int) node["A"];
        X = (double) node["X"];
        id = (string) node["id"];
    }

public:   // Data Members
    int A;
    double X;
    string id;
};

//These write and read functions must be defined for the serialization in FileStorage to work
static void write(FileStorage &fs, const std::string &, const MyData &x) {
    x.write(fs);
}

static void read(const FileNode &node, MyData &x, const MyData &default_value = MyData()) {
    if (node.empty()) {
        x = default_value;
    } else {
        x.read(node);
    }
}

// This function will print our custom class to the console
static ostream &operator<<(ostream &out, const MyData &m) {
    out << "{ id = " << m.id << ", ";
    out << "X = " << m.X << ", ";
    out << "A = " << m.A << "}";
    return out;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    string filename = argv[1];
    { //write
        Mat R = Mat_<uchar>::eye(3, 3),
                T = Mat_<double>::zeros(3, 1);
        MyData m(1);

        FileStorage fs(filename, FileStorage::WRITE);

        fs << "iterationNr" << 100;
        fs << "strings" << "[";                              // text - string sequence
        fs << "image1.jpg" << "Awesomeness" << "../data/baboon.jpg";
        fs << "]";                                           // close sequence

        fs << "Mapping";                              // text - mapping
        fs << "{" << "One" << 1;
        fs << "Two" << 2 << "}";

        fs << "R" << R;                                      // cv::Mat
        fs << "T" << T;

        fs << "MyData" << m;                                // your own data structures

        fs.release();                                       // explicit close
        cout << "Write Done." << endl;
    }

    {//read
        cout << endl << "Reading: " << endl;
        FileStorage fs;
        fs.open(filename, FileStorage::READ);

        int itNr;
        //fs["iterationNr"] >> itNr;
        itNr = (int) fs["iterationNr"];
        cout << itNr;
        if (!fs.isOpened()) {
            cerr << "Failed to open " << filename << endl;
            return 1;
        }

        FileNode n = fs["strings"];                         // Read string sequence - Get node
        if (n.type() != FileNode::SEQ) {
            cerr << "strings is not a sequence! FAIL" << endl;
            return 1;
        }

        FileNodeIterator it = n.begin(), it_end = n.end(); // Go through the node
        for (; it != it_end; ++it) {
            cout << (string) *it << endl;
        }

        n = fs["Mapping"];                                // Read mappings from a sequence
        cout << "Two  " << (int) (n["Two"]) << "; ";
        cout << "One  " << (int) (n["One"]) << endl << endl;


        MyData m;
        Mat R, T;

        fs["R"] >> R;                                      // Read cv::Mat
        fs["T"] >> T;
        fs["MyData"] >> m;                                 // Read your own structure_

        cout << endl
             << "R = " << R << endl;
        cout << "T = " << T << endl << endl;
        cout << "MyData = " << endl << m << endl << endl;

        //Show default behavior for non existing nodes
        cout << "Attempt to read NonExisting (should initialize the data structure with its default).";
        fs["NonExisting"] >> m;
        cout << endl << "NonExisting = " << endl << m << endl;
    }

    cout << endl
         << "Tip: Open up " << filename << " with a text editor to see the serialized data." << endl;

    return 0;
}
