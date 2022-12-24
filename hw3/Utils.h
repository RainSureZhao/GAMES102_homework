//
// Created by 赵润朔 on 2022/12/23.
//
#include <vector>
#include <cmath>
#include "Eigen/Dense"
#ifndef HW3_UTILS_H
#define HW3_UTILS_H


class Utils {
public:
    constexpr static const float Pi = 3.141592653589793f;

    static std::vector<float> InterpolationPolygon(const std::vector<float> &pos_x, const std::vector<float> &pos_y,
                                            float l, float r, float step );
    static std::vector<float> ApproximationPolygon(const std::vector<float> &pos_x, const std::vector<float> &pos_y,
                                            int m, float l, float r, float step );
    static std::vector<float> CubicSpline(const std::vector<float> &pos_x, const std::vector<float> &pos_y,
                                   float l, float r, float step);
    static std::vector<float> ParameterizationUniform(const std::vector<float> &pos_x, const std::vector<float> &pos_y);
    static std::vector<float> ParameterizationChoral(const std::vector<float> &pos_x, const std::vector<float> &pos_y);
    static std::vector<float> ParameterizationCentripetal(const std::vector<float> &pos_x, const std::vector<float> &pos_y);
    static std::vector<float> ParameterizationFoley(const std::vector<float> &pos_x, const std::vector<float> &pos_y);
};


#endif //HW3_UTILS_H
