#include "debugcam.h"

namespace muongame {



DebugCam::DebugCam(math::Vec3f pos, math::Vec3f up)
    : position(pos), _up(up), speed(2), sensitivityX(0.2f), sensitivityY(0.2f), clampMax(80), clampMin(-80)
    , _eulerRot(math::Vec2f())
{
    viewMatrix = math::Mat4::lookAt(position, position + math::Vec3f(0,0,-1), up);
}

void DebugCam::update(float deltaTime)
{
    using namespace input;
    using namespace math;
    Vec2f deltaMouse =  Input::getMousePosition() - _prevMousePos;
    //INFO(deltaMouse);
    _eulerRot.y -= deltaMouse.x * sensitivityY; //Horizontal
    _eulerRot.x += deltaMouse.y * sensitivityY; //Vertical

    if(_eulerRot.x >= clampMax) {
        _eulerRot.x = clampMax;
    }else if (_eulerRot.x <= clampMin) {
        _eulerRot.x = clampMin;
    }


    float movement = speed * deltaTime;
    Mat4 rotation = Mat4::rotation(Vec3f(0, _eulerRot.y, 0)) * Mat4::rotation(Vec3f(_eulerRot.x, 0, 0));
    Vec3f forward = rotation * Vec3f(0, 0, 1);
    Vec3f up = rotation * _up;
    Vec3f right = rotation * Vec3f(1,0,0);


    if (Input::isKeyHeld(GLFW_KEY_W)) position += forward * movement;
    if (Input::isKeyHeld(GLFW_KEY_S)) position -= forward * movement;
    if (Input::isKeyHeld(GLFW_KEY_A)) position += right * movement;
    if (Input::isKeyHeld(GLFW_KEY_D)) position -= right * movement;
    //if (Input::isKeyHeld(GLFW_KEY_SPACE)) position += Vec3f(0, movement, 0);
    //if (Input::isKeyHeld(GLFW_KEY_LEFT_SHIFT)) position -= Vec3f(0, movement, 0);

    //INFO("hor(y): " << _eulerRot.y << " ver(x): " << _eulerRot.x);

    viewMatrix = Mat4::lookAt(position, position + forward);

    _prevMousePos = Input::getMousePosition();
}

}
