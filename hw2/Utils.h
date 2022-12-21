//
// Created by 赵润朔 on 2022/12/15.
//
#pragma once
#ifndef HW2_UTILS_H
#define HW2_UTILS_H

#endif //HW2_UTILS_H

#include <vector>
#include "Eigen/Eigen"
#include <cmath>

class Utils {
public:
    static std::vector<Eigen::Vector2f>
    Polygon_Inter(const std::vector<Eigen::Vector2f> &points, float l, float r, float step);

    static std::vector<Eigen::Vector2f>
    Gauss_Inter(const std::vector<Eigen::Vector2f> &points, float l, float r, float step, float sigma = 1);

    static std::vector<Eigen::Vector2f>
    Approach_Poly(const std::vector<Eigen::Vector2f> &points, float l, float r, float step, int m = 3);

    static std::vector<Eigen::Vector2f>
    Approach_Poly_Norm(const std::vector<Eigen::Vector2f> &points, float l, float r, float step, int m = 3, float lambda = 0.5);

};