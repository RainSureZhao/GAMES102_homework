//
// Created by 赵润朔 on 2022/12/23.
//

#include "Utils.h"

namespace Calculate {
    Eigen::VectorXf Interpolation_PolynomialBase(const std::vector<Eigen::Vector2f> &points)
    {
        // 获取多项式插值的向量
        int n = points.size();
        Eigen::MatrixXf B = Eigen::MatrixXf::Zero(n, n);
        Eigen::VectorXf y = Eigen::VectorXf::Zero(n);
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < n; j ++) {
                B(i, j) = std::pow(points[i].x(), j);
            }
            y(i) = points[i].y();
        }
        return B.inverse() * y;
    }
};
using namespace Calculate;
std::vector<float>
Utils::InterpolationPolygon(const std::vector<float> &pos_x, const std::vector<float> &pos_y, float l, float r,
                            float step) {
    const int n = pos_x.size();
    std::vector<float> result;
    for (float x = l; x <= r; x += step) {
        float y = 0;
        for (int i = 0; i < n; i++) {
            float temp = pos_y[i];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    temp = temp * (x - pos_x[j]) / (pos_x[i] - pos_x[j]);
                }
            }
            y += temp;
        }
        result.push_back(y);
    }
    return result;
}

std::vector<float>
Utils::ApproximationPolygon(const std::vector<float> &pos_x, const std::vector<float> &pos_y, int m, float l, float r,
                            float step) {
    return std::vector<float>();
}

std::vector<float>
Utils::CubicSpline(const std::vector<float> &pos_x, const std::vector<float> &pos_y, float l, float r, float step) {
    return std::vector<float>();
}

std::vector<float> Utils::ParameterizationUniform(const std::vector<float> &pos_x, const std::vector<float> &pos_y) {
    int n = pos_x.size();
    if(n == 1) return {0.0f};
    float inv = 1.0f / (n - 1);
    std::vector<float> res(n);
    for(int i = 0; i < n; i ++) res[i] = i * inv;
    return res;
}

std::vector<float> Utils::ParameterizationChoral(const std::vector<float> &pos_x, const std::vector<float> &pos_y) {
    return std::vector<float>();
}

std::vector<float>
Utils::ParameterizationCentripetal(const std::vector<float> &pos_x, const std::vector<float> &pos_y) {
    return std::vector<float>();
}

std::vector<float> Utils::ParameterizationFoley(const std::vector<float> &pos_x, const std::vector<float> &pos_y) {
    return std::vector<float>();
}
