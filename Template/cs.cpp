//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <cmath>
//
//using namespace std;
//
//// 定义图像结构体
//struct Image {
//    int width;
//    int height;
//    vector<unsigned char> data;
//};
//
//// 读取PGM格式图像
//Image readPic(const char* filename) {
//    ifstream file(filename, ios::binary);
//    if (!file) {
//        cerr << "Error: Cannot open file " << filename << endl;
//        exit(1);
//    }
//
//    string magic;
//    int width, height, maxval;
//    file >> magic >> width >> height >> maxval;
//    if (magic != "P5" || maxval != 255) {
//        cerr << "Error: Invalid PGM format" << endl;
//        exit(1);
//    }
//
//    Image img;
//    img.width = width;
//    img.height = height;
//    img.data.resize(width * height);
//
//    file.read((char*)img.data.data(), width * height);
//    file.close();
//
//    return img;
//}
//
//// 写入PGM格式图像
//void writePGM(const char* filename, const Image& img) {
//    ofstream file(filename, ios::binary);
//    if (!file) {
//        cerr << "Error: Cannot open file " << filename << endl;
//        exit(1);
//    }
//
//    file << "P5\n" << img.width << " " << img.height << "\n255\n";
//    file.write((char*)img.data.data(), img.width * img.height);
//    file.close();
//}
//
//// 计算两个像素之间的欧几里得距离
//double euclideanDistance(const unsigned char* p1, const unsigned char* p2, int n) {
//    double sum = 0.0;
//    for (int i = 0; i < n; i++) {
//        double diff = p1[i] - p2[i];
//        sum += diff * diff;
//    }
//    return sqrt(sum);
//}
//
//// 计算两个图像之间的均方误差
//double meanSquaredError(const Image& img1, const Image& img2) {
//    double sum = 0.0;
//    for (int i = 0; i < img1.width * img1.height; i++) {
//        sum += pow(img1.data[i] - img2.data[i], 2);
//    }
//    return sum
//        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//        / (img1.width * img1.height);
//}
//
//// 计算两个图像之间的归一化互相关系数
//double normalizedCrossCorrelation(const Image& img1, const Image& img2) {
//    double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
//    for (int i = 0; i < img1.width * img1.height; i++) {
//        sum1 += img1.data[i];
//        sum2 += img2.data[i];
//    }
//    double mean1 = sum1 / (img1.width * img1.height);
//    double mean2 = sum2 / (img2.width * img2.height);
//    for (int i = 0; i < img1.width * img1.height; i++) {
//        sum3 += (img1.data[i] - mean1) * (img2.data[i] - mean2);
//    }