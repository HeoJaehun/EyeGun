//
//  EyeGunCalibrator.cpp
//  EyeGun_Calibration_Simulator
//
//  Created by HeoJaehun on 10/9/15.
//
//

#include "eyeguncalibrator.hpp"


EyeGunCalibrator::EyeGunCalibrator()
{
    
}


EyeGunCalibrator::~EyeGunCalibrator()
{
    
}


void EyeGunCalibrator::init()
{
    m_v_src_points.clear();
    m_v_dst_points.clear();
    m_m_homography.zeros(Size(3, 3), CV_64FC1);
    m_b_ready = false;
}


void EyeGunCalibrator::calculate()
{
#ifdef DEBUG
    cout << "Source Points:\n" << m_v_src_points << endl;
    cout << "Destination Points:\n" << m_v_dst_points << endl;
#endif

    m_m_homography = findHomography(m_v_src_points, m_v_dst_points);

#ifdef DEBUG
    cout << "Homography:\n" << m_m_homography << endl;
#endif
}

eyeAngle EyeGunCalibrator::calib(Point2f src)
{
    Mat src_mat = Mat::zeros(3, 1, CV_64FC1);
    Mat dst_mat = Mat::zeros(3, 1, CV_64FC1);
    Point2f dst_point;
    eyeAngle dst_theta;

    src_mat.at<float>(0) = (float)src.x;
    src_mat.at<float>(1) = (float)src.y;
    src_mat.at<float>(2) = 1.0;

    gemm(m_m_homography, src_mat, 1, 0, 0, dst_mat);

    dst_point.x = dst_mat.at<float>(0);
    dst_point.y = dst_mat.at<float>(1);
//    dst_point.x = dst_mat.at<float>(0) / dst_mat.at<float>(2);
//    dst_point.y = dst_mat.at<float>(1) / dst_mat.at<float>(2);

#ifdef DEBUG
    cout << "dst_point:\n" << dst_point << endl;
#endif

    dst_theta.thetaH = (dst_point.x/(2.0/sqrt(3)))*60+60;
    dst_theta.thetaV = (dst_point.y/(2.0/sqrt(3)))*60+60;

    return dst_theta;
}


void EyeGunCalibrator::setData(Point2f src_point, Point2f dst_point)
{
    m_v_src_points.push_back(src_point);
    m_v_dst_points.push_back(dst_point);

    if (m_v_src_points.size() == 4)
        m_b_ready = true;
}


bool EyeGunCalibrator::getCondition()
{
    return m_b_ready;
}
