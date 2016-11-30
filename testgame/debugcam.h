#ifndef DEBUG_CAM_H
#define DEBUG_CAM_H

#include "muon.h"
namespace muongame {

    using namespace muon;
class DebugCam{

public:

    math::Vec3f position;
    float speed;
    float sensitivityX, sensitivityY;
    math::Mat4 viewMatrix;
    float clampMax, clampMin;

    DebugCam(math::Vec3f pos, math::Vec3f up = math::Vec3f(0,1,0));

    void update(float deltaTime);

private:
    math::Vec3f _up;
    math::Vec2f _prevMousePos;
    math::Vec2f _eulerRot;
};

}

#endif
