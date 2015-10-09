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
    m_v_srcPoint.clear();
    m_v_srcAngle.clear();
    m_b_ready = false;
}


eyeGunAngle EyeGunCalibrator::calculate(int x, int y)
{
    if (m_v_srcData.size() != 2) {
        cerr << "Check data size!" << endl;
        eyeGunAngle result;
        result.thetaH = 90;
        result.thetaV = 90;
        return result;
    }
    
    /*
     
     first data: x1, y1, angle1
     second data: x2, y2, angle2
     
     alpha = (X - x1)/(x2 - x1)
     theta = alpha * (angle2 - angle1) + angle1
     
     */
    
    float alphaH;
    float alphaV;
    eyeGunAngle result;
    
    alphaH = (float)(x - m_v_srcData[0].first.x)/(m_v_srcData[1].first.x - m_v_srcData[0].first.x);
    result.thetaH = alphaH * (m_v_srcData[1].second.thetaH - m_v_srcData[0].second.thetaH) + m_v_srcData[0].second.thetaH;
    
    alphaV = (float)(y - m_v_srcData[0].first.y)/(m_v_srcData[1].first.y - m_v_srcData[0].first.y);
    result.thetaV = alphaV * (m_v_srcData[1].second.thetaV - m_v_srcData[0].second.thetaV) + m_v_srcData[0].second.thetaV;
    
    cout << "thetaH: " << result.thetaH << "   thetaV: " << result.thetaV << endl;
    
    
    
    return result;
}


void EyeGunCalibrator::setPoint(int x, int y)
{
    if (m_v_srcPoint.size() >= 2) {
        cerr << "Too many points" << endl;
        return;
    }
    
    eyeGunVector point;
    point.x = x;
    point.y = y;
    m_v_srcPoint.push_back(point);
}


void EyeGunCalibrator::setAngle(int angle)
{
    if (m_v_srcPoint.size() >= 2) {
        cerr << "Too many points" << endl;
        return;
    }
    
    m_v_srcAngle.push_back(angle);
}

void EyeGunCalibrator::setData(int x, int y, int angleH, int angleV)
{
    if (m_v_srcData.size() >= 2) {
        cerr << "Too many data" << endl;
        return;
    }
    
    eyeGunVector point;
    point.x = x;
    point.y = y;
    
    eyeGunAngle angle;
    angle.thetaH = angleH;
    angle.thetaV = angleV;
    
    pair<eyeGunVector, eyeGunAngle> tempData;
    tempData.first = point;
    tempData.second = angle;
    
    m_v_srcData.push_back(tempData);
    
    if (m_v_srcData.size() == 2) {
        m_b_ready = true;
    }
}


bool EyeGunCalibrator::getCondition()
{
    return m_b_ready;
}
