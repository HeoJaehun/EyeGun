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


using namespace std;

typedef struct {
    int x;
    int y;
} eyeGunVector;

typedef struct {
    int thetaH;
    int thetaV;
} eyeGunAngle;


class EyeGunCalibrator{
public:
    EyeGunCalibrator();
    ~EyeGunCalibrator();
    
    void init();
    eyeGunAngle calculate(int x, int y);
    void setPoint(int x, int y);
    void setAngle(int angle);
    void setData(int x, int y, int angleH, int angleV);
    bool getCondition();
    
private:
    vector<eyeGunVector> m_v_srcPoint;
    vector<int> m_v_srcAngle;
    vector<pair<eyeGunVector, eyeGunAngle> > m_v_srcData;
    
    bool m_b_ready;
};

#endif /* EyeGunCalibrator_hpp */
