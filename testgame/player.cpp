#include "player.h"
#include "input/input.h"

namespace muongame {

GLfloat Player::cubeV[] = {
        0.5f,0, 0.5f,//
        0.5f,0,-0.5f,//
       -0.5f,0,-0.5f,
       -0.5f,0, 0.5f,

       0.5f,1, 0.5f,//
       0.5f,1,-0.5f,//
      -0.5f,1,-0.5f,
      -0.5f,1, 0.5f,
};

GLuint Player::cubeI[]  = {
    0,1,3,
    3,2,1,

    4,5,7,
    7,6,5,

    4,0,7,
    7,3,0,

    6,2,5,
    5,1,2,

    7,3,6,
    6,2,3,

    5,1,4,
    4,0,1
};

Model* Player::model = nullptr;
const float Player::floorLevel = 0;
const Color Player::color = Color(COL_BLUE);
const float Player::size = 0.5f;

Player::Player(math::Vec3f position, bool *map, int levelWidth, int levelLength) : position(position), velocity(0,5,0), acceleration(0,-9.8f, 0),
    map(map), levelWidth(levelWidth), levelLength(levelLength)
{

}

void Player::load() {
    model = new Model(cubeV, sizeof(cubeV), cubeI, sizeof(cubeI));
}

void Player::update(float dt, float mapScroll, int mapOffset)
{
    //position += velocity * dt;
    //velocity += acceleration * dt;
    /*
    if(isGrounded()) {
        position.y = floorLevel;
    }
    */

    if(input::Input::isKeyPressed(GLFW_KEY_SPACE)) velocity.y = 5;

    if(input::Input::isKeyHeld(GLFW_KEY_LEFT)) position.x += 2 * dt;
    if(input::Input::isKeyHeld(GLFW_KEY_RIGHT)) position.x -= 2 * dt;
    if(input::Input::isKeyHeld(GLFW_KEY_UP)) position.z += 2 * dt;
    if(input::Input::isKeyHeld(GLFW_KEY_DOWN)) position.z -= 2 * dt;

    _scroll = mapScroll;
    _offset = mapOffset;

}

void Player::draw(Shader *shader)
{
    using namespace math;
    ShaderManager::setModelMatrix(Mat4::translation(position) * Mat4::scale(Vec3f(size, size, size)));
    shader->setUniformColor("base_color", Color(isGrounded(_scroll, _offset) ? COL_BLUE : COL_RED));
    model->draw();
}

bool Player::isGrounded(float mapScroll, int mapOffset) const
{
    using namespace math;

    bool isIntersecting = false;
    float right = position.x-size/2;
    float left = position.x+size/2;
    float bot = position.z-size/2;
    float top = position.z+size/2;


    Vec2i tilepos(position.x+x, position.z+mapScroll);
    Vec2i tileposMap = tilepos + Vec2i(0, mapOffset);




    for(int z = -1; z <= 1; z++) {
        for(int x = -1; x <= 1; x++) {

            if(tilepos.x < 0 || tilepos.x >= levelWidth || tilepos.y < 0) continue;
            float rright = tilepos.x;
            float rleft = tilepos.x + 1;
            float rtop = tilepos.y + 1;
            float rbot = tilepos.y;

            if(left > rright &&
               right < rleft &&
               top > rbot &&
               bot < rtop && map[tileposMap.x+tileposMap.y*levelWidth]) {
                isIntersecting = true;
                break;
            }
        }
    }

    return isIntersecting; // position.y <= floorLevel &&
}

}


