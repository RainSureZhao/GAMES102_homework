#include "fitcurve.h"

void ControlPointArray2D::calculateParam_extend(int range_num) {
    int stpoint = range_num, edpoint = range_num + 1;
    while (stpoint>=0 and fixed[stpoint] == false) {
        stpoint--;
    }
    stpoint = (stpoint<0)?0:stpoint;
    while (edpoint < fixed.size() and fixed[edpoint] == false) {
        edpoint++;
    }
    edpoint = (edpoint >= fixed.size()) ? (fixed.size()-1) : edpoint;

    auto xparm = ThreeOrderSample(xs, stpoint, edpoint + 1);
    auto yparm = ThreeOrderSample(ys, stpoint, edpoint + 1);

    for (int i = stpoint; i <= edpoint - 1; ++i) {
        int b = (i - stpoint) * 4;
        param[i] = { xparm[b], xparm[b + 1], xparm[b + 2], xparm[b + 3],
                    yparm[b], yparm[b + 1], yparm[b + 2], yparm[b + 3] };
        calculateRange(i);
    }
    update_drawarr();
    updateCtrlPoints();
}

void ControlPointArray2D::calculateRange(int p) {
    double st = p;
    std::vector<double> _xs(nodePerRange), _ys(nodePerRange);
    for (int i = 0; i < nodePerRange; ++i) {
        double t = st + (i * 1.0 / nodePerRange);
        _xs[i] = param[p][0] * pow(t, 3) + param[p][1] * pow(t, 2) + param[p][2] * t + param[p][3];
        _ys[i] = param[p][4] * pow(t, 3) + param[p][5] * pow(t, 2) + param[p][6] * t + param[p][7];
    }
    xs[p].rdiff = 3 * param[p][0] * pow(st, 2) + 2 * param[p][1] * st + param[p][2];
    xs[p+1].ldiff = 3 * param[p][0] * pow(st + 1, 2) + 2 * param[p][1] * (st + 1) + param[p][2];
    ys[p].rdiff = 3 * param[p][4] * pow(st, 2) + 2 * param[p][5] * st + param[p][6];
    ys[p+1].ldiff = 3 * param[p][4] * pow(st + 1, 2) + 2 * param[p][5] * (st + 1) + param[p][6];
    drawPoints[p].xs.swap(_xs);
    drawPoints[p].ys.swap(_ys);
    drawPoints[p].size = 100;
}

void ControlPointArray2D::push_back(double x, double y) {
    xs.push_back({ x, 0, 0, false });
    ys.push_back({ y, 0, 0, false });
    fixed.push_back(false);
    updateCtrlPoints();

    if (nodenum() >= 2) {
        drawPoints.push_back(NodeArr(nodePerRange));
        param.push_back(std::vector<double>(8));
        calculateParam_extend(param.size()-1);
    }
}

void ControlPointArray2D::delete_at(int pos) {
    //ɾ�����ǵ�
    int last = nodenum() - 1;
    {
        xs.erase(xs.begin() + pos);
        ys.erase(ys.begin() + pos);
        fixed.erase(fixed.begin() + pos);
    }
    if (pos == 0) {
        drawPoints.erase(drawPoints.begin());
        param.erase(param.begin());
    }
    else if (pos == last) {
        drawPoints.erase(drawPoints.end() - 1);
        param.erase(param.end() - 1);
    }
    else {
        drawPoints.erase(drawPoints.end() + pos);
        param.erase(param.end() + pos);
        calculateParam_extend(pos - 1);
    }
}

int ControlPointArray2D::findSuitableCtrlPoint(double x, double y) {
    int res = -1;
    double minv = 1e10;
    for (int i = 0; i < xs.size(); ++i) {
        double dist = sqrt(pow(x - xs[i].val, 2) + pow(y - ys[i].val, 2));
        if (dist < minv and dist < maxChoosedist) {
            minv = dist;
            res = i;
        }
    }
    for (int i = 1; i < xs.size(); ++i) {
        double dist = sqrt(pow(x - ctrl_l_xs[i], 2) + pow(y - ctrl_l_ys[i], 2));
        if (dist < minv and dist < maxChoosedist) {
            minv = dist;
            res = i+nodenum();
        }
    }
    for (int i = 0; i < xs.size()-1; ++i) {
        double dist = sqrt(pow(x - ctrl_r_xs[i], 2) + pow(y - ctrl_r_ys[i], 2));
        if (dist < minv and dist < maxChoosedist) {
            minv = dist;
            res = i + 2 * nodenum();
        }
    }
    return res;
}

std::vector<double> ThreeOrderSample(const std::vector<controlPoint> &ctrlarr, int begin, int end) {
    using namespace Eigen;

    int pointnum = end - begin;
    assert(pointnum >= 2);
    int n = pointnum - 1;

    Matrix<double, Dynamic, Dynamic> A(4*n, 4*n);
    VectorXd b(4*n), x(4*n);
    A.setZero();
    b.setZero();
    int disp = 1;
    for (auto it = begin; it != end-1; ++it) {
        int num = it - begin;

        //lvalue
        A(num * 4 + disp, num * 4) = pow(it, 3);
        A(num * 4 + disp, num * 4 + 1) = pow(it, 2);
        A(num * 4 + disp, num * 4 + 2) = it;
        A(num * 4 + disp, num * 4 + 3) = 1;
        b(num * 4 + disp) = ctrlarr[it].val;

        //rvalue
        A(num * 4 + 1 + disp, num * 4) = pow(it + 1, 3);
        A(num * 4 + 1 + disp, num * 4 + 1) = pow(it + 1, 2);
        A(num * 4 + 1 + disp, num * 4 + 2) = it + 1;
        A(num * 4 + 1 + disp, num * 4 + 3) = 1;
        b(num * 4 + 1 + disp) = ctrlarr[it + 1].val;

        if (num != 0) {
            A(num * 4 - 1, num * 4) = 3 * pow(it, 2);
            A(num * 4 - 1, num * 4 + 1) = 2 * it;
            A(num * 4 - 1, num * 4 + 2) = 1;
            A(num * 4 - 1, (num - 1) * 4) = -3 * pow(it, 2);
            A(num * 4 - 1, (num - 1) * 4 + 1) = -2 * it;
            A(num * 4 - 1, (num - 1) * 4 + 2) = -1;

            A(num * 4, num * 4) = 3 * it;
            A(num * 4, num * 4 + 1) = 1;
            A(num * 4, (num - 1) * 4) = -3 * it;
            A(num * 4, (num - 1) * 4 + 1) = -1;
        }

    }
    if (ctrlarr[begin].fixed_diff == true) {
        A(0, 0) = 3 * pow(begin, 2);
        A(0, 1) = 2 * begin;
        A(0, 2) = 1;
        b(0) = ctrlarr[begin].rdiff;
    }
    else {
        A(0, 0) = 6 * begin;
        A(0, 1) = 2;
    }
    if (ctrlarr[end - 1].fixed_diff == true) {
        A(n * 4 - 1, (n - 1) * 4) = 3 * pow(end-1, 2);
        A(n * 4 - 1, (n - 1) * 4 + 1) = 2 * (end-1);
        A(n * 4 - 1, (n - 1) * 4 + 2) = 1;
        b(n * 4 - 1) = ctrlarr[end - 1].ldiff;
    }
    else {
        A(n * 4 - 1, (n - 1) * 4) = 3 * (end-1);
        A(n * 4 - 1, (n - 1) * 4 + 1) = 1;
    }
    x = A.colPivHouseholderQr().solve(b);
    std::vector<double> res;
    for (int i = 0; i < 4*n; ++i)
        res.push_back(x(i));
    return res;
}
