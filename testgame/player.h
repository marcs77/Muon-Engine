#ifndef PLAYER_H
#define PLAYER_H

#include "muon.h"
#include "model.h"

namespace muongame {

class Player
{
public:
    Player(math::Vec3f position, bool *map, int levelWidth, int levelLength);

    static void load();

    void update(float dt, float mapScroll, int mapOffset);
    void draw(Shader *shader);

    static const float floorLevel;

    math::Vec3f position;

private:
    static GLfloat cubeV[];
    static GLuint cubeI[];
    static Model* model;

    static const float size;
    static const Color color;


    math::Vec3f velocity;
    math::Vec3f acceleration;

    bool isGrounded(float mapScroll, int mapOffset) const;
    bool *map;
    int levelWidth;
    int levelLength;
    float _scroll;
    int _offset;

};

}

#endif // PLAYER_H
