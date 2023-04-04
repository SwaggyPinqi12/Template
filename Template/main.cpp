#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

// ����ͼ���ƽ��ֵ�ͱ�׼��
void calcMeanStd(const unsigned char* data, int width, int height, double& mean, double& std) {
    double sum = 0, sum2 = 0;
    for (int i = 0; i < width * height; i++) {
        sum += data[i];
        sum2 += data[i] * data[i];
    }
    mean = sum / (width * height);
    std = sqrt(sum2 / (width * height) - mean * mean);
}

// ��һ������ͼ��
void normalizeImage(unsigned char* data, int width, int height) {
    double mean, std;
    calcMeanStd(data, width, height, mean, std);
    for (int i = 0; i < width * height; i++) {
        data[i] = (data[i] - mean) / std;
    }
}

// ��������ͼ�������Ե÷�
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
    // ��ȡģ��ͼ���Ŀ��ͼ��
    ifstream file1(".\\rc\\template.jpg", ios::binary);
    ifstream file2(".\\rc\\target.jpg", ios::binary);
    if (!file1 || !file2) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    // ��ȡ�ļ�����
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

    // �����ļ�����
    // ת��Ϊ�Ҷ�ͼ��
    int width = 277, height = 396;
    unsigned char* data1 = new unsigned char[width * height];
    unsigned char* data2 = new unsigned char[width * height];
    for (int i = 0; i < width * height; i++) {
        data1[i] = (unsigned char)((unsigned char)buffer1[i * 3] * 0.299 + (unsigned char)buffer1[i * 3 + 1] * 0.587 + (unsigned char)buffer1[i * 3 + 2] * 0.114);
        data2[i] = (unsigned char)((unsigned char)buffer2[i * 3] * 0.299 + (unsigned char)buffer2[i * 3 + 1] * 0.587 + (unsigned char)buffer2[i * 3 + 2] * 0.114);
    }

    // ��һ������ģ��ͼ��
    normalizeImage(data1, width, height);

    // ��Ŀ��ͼ���л���ģ��ͼ�񣬼���ÿ��λ�õ�����Ե÷�
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

    // ��ӡ���
    cout << "Max score: " << maxScore << endl;
    cout << "Max position: (" << maxX << ", " << maxY << ")" << endl;

    // �ͷ��ڴ�
    delete[] buffer1;
    delete[] buffer2;
    delete[] data1;
    delete[] data2;
    file1.close();
    file2.close();

    return 0;
}