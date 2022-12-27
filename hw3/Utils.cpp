//
// Created by 赵润朔 on 2022/12/23.
//

#include "Utils.h"
#include<iostream>
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

    Eigen::VectorXf Fitting_LeastSquare(const std::vector<Eigen::Vector2f> &points, int m)
    {
        // 获取最小二乘法所需要的向量
        int n = points.size();
        Eigen::MatrixXf B = Eigen::MatrixXf::Zero(n, m + 1);
        Eigen::VectorXf y = Eigen::VectorXf::Zero(n);
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j <= m; j ++) {
                B(i, j) = std::pow(points[i].x(), j);
            }
            y(i) = points[i].y();
        }
        return (B.transpose() * B).inverse() * (B.transpose() * y);
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
    std::vector<Eigen::Vector2f> points;
    int n = pos_x.size();
    for(int i = 0; i < n; i ++) points.emplace_back(pos_x[i], pos_y[i]);
    auto alpha = Fitting_LeastSquare(points, m);
    std::vector<float> res;
    for(float x = l; x <= r; x += step) {
        float temp = 0;
        for(int j = 0; j < alpha.size(); j ++) {
            temp += alpha[j] * std::pow(x, j);
        }
        res.push_back(temp);
    }
    return res;
}

std::vector<float>
Utils::CubicSpline(const std::vector<float> &pos_x, const std::vector<float> &pos_y, float l, float r, float step) {
    int n = pos_x.size();
    if(n == 1) return {0.0f};
    std::vector<float> diff_x(n - 1);
    for(int i = 0; i < n - 1; i ++) {
        diff_x[i] = pos_x[i + 1] - pos_x[i];
    }
    std::vector<float> coe0(n), coe1(n), coe2(n), coe3(n);
    for(int i = 0; i < n; i ++) coe0[i] = pos_y[i];
    Eigen::MatrixXf A(n, n);
    Eigen::VectorXf B(n);
    
    for(size_t i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++) {
            A(i, j) = 0.0f;
        }
        if(i == 0 || i == n - 1) {
            A(i, i) = 1.0f;
            B(i, 0) = 0.0f;
        }else {
            A(i, i) = 2 * (diff_x[i] + diff_x[i - 1]);
            A(i, i + 1) = diff_x[i];
            A(i, i - 1) = diff_x[i - 1];
            B(i, 0) = 3.0f / diff_x[i] * (coe0[i + 1] - coe0[i]) - 3.0 / diff_x[i - 1] * (coe0[i] - coe0[i - 1]);
        }
    }

    Eigen::VectorXf C = A.colPivHouseholderQr().solve(B);
    for (int i = 0; i < n; i++) {
        coe2[i] = C(i, 0);
    }
    for (int i = 0; i < n - 1; i++) {
        coe3[i] = (coe2[i + 1] - coe2[i]) / 3.0 / diff_x[i];
        coe1[i] = (coe0[i + 1] - coe0[i]) / diff_x[i] - coe2[i] * diff_x[i] - coe3[i] * diff_x[i] * diff_x[i];
    }

    size_t curr = 0;
    std::vector<float> result;
    for (float x = l; x <= r; x += step) {
        if (x > pos_x[curr + 1]) {
            ++curr;
        }
        float X = x - pos_x[curr];
        float y = coe0[curr] + coe1[curr] * X + coe2[curr] * X * X + coe3[curr] * X * X * X;
        result.push_back(y);
    }
    return result;
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
    int n = pos_x.size();
    if(n == 1) return {0.0f};
    float sum = 0.0f;
    std::vector<float> res(n);
    std::vector<float> dist(n - 1);
    for(int i = 1; i < n; i ++) {
        dist[i - 1] = (Eigen::Vector2f(pos_x[i - 1], pos_y[i - 1]) - Eigen::Vector2f(pos_x[i], pos_y[i])).norm();
        sum += dist[i - 1];
    }
    res[0] = 0.0f;
    for(int i = 1; i < n - 1; i ++) {
        res[i] = dist[i] / sum;
        res[i] += res[i - 1];
    }
    res[n - 1] = 1.0f;
    return res;
}

std::vector<float>
Utils::ParameterizationCentripetal(const std::vector<float> &pos_x, const std::vector<float> &pos_y) {
    int n = pos_x.size();
    if(n == 1) return {0.0f};
    float sum = 0.0f;
    std::vector<float> res(n);
    std::vector<float> dist(n - 1);
    for(int i = 1; i < n; i ++) {
        dist[i - 1] = (Eigen::Vector2f(pos_x[i - 1], pos_y[i - 1]) - Eigen::Vector2f(pos_x[i], pos_y[i])).norm();
        dist[i - 1] = std::sqrt(dist[i - 1]);
        sum += dist[i - 1];
    }
    res[0] = 0.0f;
    for(int i = 1; i < n - 1; i ++) {
        res[i] = dist[i] / sum;
        res[i] += res[i - 1];
    }
    res[n - 1] = 1.0f;
    return res;
}

std::vector<float> Utils::ParameterizationFoley(const std::vector<float> &pos_x, const std::vector<float> &pos_y) {
    int n = pos_x.size();
    if(n == 1) return {0.0f};
    std::vector<float> dist(n + 1);
    for(int i = 1; i < n; i ++) {
        dist[i] = (Eigen::Vector2f(pos_x[i], pos_y[i]) - Eigen::Vector2f(pos_x[i - 1], pos_y[i - 1])).norm();
    }
    dist[0] = dist[n] = 0.0f;
    std::vector<float> angle(n);
    for(int i = 1; i < n - 1; i ++) {
        Eigen::Vector2f a = Eigen::Vector2f(pos_x[i - 1], pos_y[i - 1]) - Eigen::Vector2f(pos_x[i], pos_y[i]);
        Eigen::Vector2f b = Eigen::Vector2f(pos_x[i + 1], pos_y[i + 1]) - Eigen::Vector2f(pos_x[i], pos_y[i]);
        angle[i] = a.dot(b) / dist[i] / dist[i + 1];
        angle[i] = std::min(Pi - angle[i], Pi / 2.0f);
    }
    angle[0] = angle[n - 1] = 0.0f;
    float sum = 0.0f;
    std::vector<float> res(n);
    res[0] = 0.0f;
    std::vector<float> diff(n);
    for(int i = 1; i < n; i ++) {
        diff[i - 1] = dist[i] * (1.0f + 1.5f * (angle[i - 1] * dist[i - 1]) / (dist[i - 1] + dist[i]) + 
                1.5f * (angle[i] * dist[i + 1]) / (dist[i] + dist[i + 1]));
        sum += diff[i - 1];
    }
    for(int i = 1; i < n - 1; i ++) {
        res[i] = diff[i - 1] / sum;
        res[i] += res[i - 1];
    }
    res[n - 1] = 1.0f;
    return res;
}
