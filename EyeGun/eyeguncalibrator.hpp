//
//  EyeGunCalibrator.hpp
//  EyeGun_Calibration_Simulator
//
//  Created by HeoJaehun on 10/9/15.
//
//

#ifndef EyeGunCalibrator_hpp
#define EyeGunCalibrator_hpp

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define DEBUG

using namespace std;
using namespace cv;

typedef struct {
    int thetaH;
    int thetaV;
} eyeAngle;


class EyeGunCalibrator{
public:
    EyeGunCalibrator();
    ~EyeGunCalibrator();
    
    void init();
    void calculate();
    eyeAngle calib(Point2f src);
    void setData(Point2f src_point, Point2f dst_point);
    bool getCondition();
    
private:
    vector<Point2f> m_v_src_points;
    vector<Point2f> m_v_dst_points;
    Mat m_m_homography;
    
    bool m_b_ready;
};

#endif /* EyeGunCalibrator_hpp */
