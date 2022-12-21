//
// Created by 赵润朔 on 2022/12/15.
//
#include "Utils.h"

namespace Calculate{
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

    float GaussBaseFunction(float x, float xi, float sigma)
    {
        // 高斯基函数计算
        return std::exp(-(x - xi) * (x - xi) / (2 * sigma * sigma));
    }

    Eigen::VectorXf Interpolation_GaussBaseFunction(const std::vector<Eigen::Vector2f> &points, float sigma = 1)
    {
        // 获取高斯函数插值的向量
        int n = points.size();
        Eigen::MatrixXf B = Eigen::MatrixXf::Zero(n + 1, n + 1);
        Eigen::VectorXf y = Eigen::VectorXf::Zero(n + 1);
        for(int i = 0; i < n; i ++) {
            B(i, 0) = 1;
            for(int j = 1; j < n + 1; j ++) {
                B(i, j) = GaussBaseFunction(points[i].x(), points[j - 1].x(), sigma);
            }
            y(i) = points[i].y();
        }
        B(n, 0) = 1;
        y(n) = (points[n - 2].y() + points[n - 1].y()) / 2.0f;
        for(int i = 1; i < n + 1; i ++) {
            B(n, i) = GaussBaseFunction((points[n - 2].x() + points[n - 1].x()) / 2.0f, points[i - 1].x(), sigma);
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

    Eigen::VectorXf Fitting_RidgeRegression(const std::vector<Eigen::Vector2f> &points, int m, float lambda)
    {
        int n = points.size();
        Eigen::MatrixXf B = Eigen::MatrixXf::Zero(n, m + 1);
        Eigen::VectorXf y = Eigen::VectorXf::Zero(n);
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j <= m; j ++) {
                B(i, j) = std::pow(points[i].x(), j);
            }
            y(i) = points[i].y();
        }
        Eigen::MatrixXf I;
        I.setIdentity(m + 1, m + 1);
        return ( B.transpose() * B + I * lambda).inverse() * (B.transpose() * y);
    }

};
using namespace Calculate;

std::vector<Eigen::Vector2f>
Utils::Polygon_Inter(const std::vector<Eigen::Vector2f> &points, float l, float r, float step) {
    auto alpha = Interpolation_PolynomialBase(points);
    int n = points.size();
    std::vector<Eigen::Vector2f> res;
    for(int i = l; i <= r; i += step) {
        float temp = 0;
        for(int j = 0; j < n; j ++) {
            temp += alpha[j] * std::pow(i, j);
        }
        res.emplace_back(i, temp);
    }
    return res;
}


std::vector<Eigen::Vector2f>
Utils::Gauss_Inter(const std::vector<Eigen::Vector2f> &points, float l, float r, float step, float sigma) {
    int n = points.size();
    auto alpha = Interpolation_GaussBaseFunction(points, sigma);
    std::vector<Eigen::Vector2f> res;
    for(int i = l; i <= r; i += step) {
        float temp = alpha[0];
        for(int j = 1; j < n + 1; j ++) {
            temp += alpha[j] * GaussBaseFunction(i, points[j - 1].x(), sigma);
        }
        res.emplace_back(i, temp);
    }
    return res;
}

std::vector<Eigen::Vector2f>
Utils::Approach_Poly(const std::vector<Eigen::Vector2f> &points, float l, float r, float step, int m) {
    int n = points.size();
    auto alpha = Fitting_LeastSquare(points, m);
    std::vector<Eigen::Vector2f> res;
    for(int i = l; i <= r; i += step) {
        float temp = 0;
        for(int j = 0; j <= m; j ++) {
            temp += alpha[j] * std::pow(i, j);
        }
        res.emplace_back(i, temp);
    }
    return res;
}

std::vector<Eigen::Vector2f>
Utils::Approach_Poly_Norm(const std::vector<Eigen::Vector2f> &points, float l, float r, float step, int m,
                          float lambda) {
    int n = points.size();
    auto alpha = Fitting_RidgeRegression(points, m, lambda);
    std::vector<Eigen::Vector2f> res;
    for(int i = l; i <= r; i += step) {
        float temp = 0;
        for(int j = 0; j <= m; j ++) {
            temp += alpha[j] * std::pow(i, j);
        }
        res.emplace_back(i, temp);
    }
    return res;

}





