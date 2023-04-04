#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

// 计算图像的平均值和标准差
void calcMeanStd(const unsigned char* data, int width, int height, double& mean, double& std) {
    double sum = 0, sum2 = 0;
    for (int i = 0; i < width * height; i++) {
        sum += data[i];
        sum2 += data[i] * data[i];
    }
    mean = sum / (width * height);
    std = sqrt(sum2 / (width * height) - mean * mean);
}

// 归一化处理图像
void normalizeImage(unsigned char* data, int width, int height) {
    double mean, std;
    calcMeanStd(data, width, height, mean, std);
    for (int i = 0; i < width * height; i++) {
        data[i] = (data[i] - mean) / std;
    }
}

// 计算两个图像的相关性得分
double calcCorrelation(const unsigned char* data1, const unsigned char* data2, int width, int height) {
    double sum1 = 0, sum2 = 0, sum12 = 0, sum1sq = 0, sum2sq = 0;
    for (int i = 0; i < width * height; i++) {
        sum1 += data1[i];
        sum2 += data2[i];
        sum12 += data1[i] * data2[i];
        sum1sq += data1[i] * data1[i];
        sum2sq += data2[i] * data2[i];
    }
    double numerator = sum12 - sum1 * sum2 / (width
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        * height);
    double denominator = sqrt((sum1sq - sum1 * sum1 / (width * height)) * (sum2sq - sum2 * sum2 / (width * height)));
    return numerator / denominator;
}

int main() {
    // 读取模板图像和目标图像
    ifstream file1(".\\rc\\template.jpg", ios::binary);
    ifstream file2(".\\rc\\target.jpg", ios::binary);
    if (!file1 || !file2) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    // 读取文件内容
    file1.seekg(0, ios::end);
    int size1 = file1.tellg();
    file1.seekg(0, ios::beg);
    char* buffer1 = new char[size1];
    file1.read(buffer1, size1);

    file2.seekg(0, ios::end);
    int size2 = file2.tellg();
    file2.seekg(0, ios::beg);
    char* buffer2 = new char[size2];
    file2.read(buffer2, size2);

    // 处理文件内容
    // 转换为灰度图像
    int width = 277, height = 396;
    unsigned char* data1 = new unsigned char[width * height];
    unsigned char* data2 = new unsigned char[width * height];
    for (int i = 0; i < width * height; i++) {
        data1[i] = (unsigned char)((unsigned char)buffer1[i * 3] * 0.299 + (unsigned char)buffer1[i * 3 + 1] * 0.587 + (unsigned char)buffer1[i * 3 + 2] * 0.114);
        data2[i] = (unsigned char)((unsigned char)buffer2[i * 3] * 0.299 + (unsigned char)buffer2[i * 3 + 1] * 0.587 + (unsigned char)buffer2[i * 3 + 2] * 0.114);
    }

    // 归一化处理模板图像
    normalizeImage(data1, width, height);

    // 在目标图像中滑动模板图像，计算每个位置的相关性得分
    double maxScore = -1;
    int maxX = 0, maxY = 0;
    for (int y = 0; y < height - 100; y++) {
        for (int x = 0; x < width - 100; x++) {
            double score = calcCorrelation(data1, data2 + y * width + x, 100, 100);
            if (score > maxScore) {
                maxScore = score;
                maxX = x;
                maxY = y;
            }
        }
    }

    // 打印结果
    cout << "Max score: " << maxScore << endl;
    cout << "Max position: (" << maxX << ", " << maxY << ")" << endl;

    // 释放内存
    delete[] buffer1;
    delete[] buffer2;
    delete[] data1;
    delete[] data2;
    file1.close();
    file2.close();

    return 0;
}