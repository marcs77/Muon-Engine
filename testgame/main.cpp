
#include "muon.h"
#include "build_info.h"
#include "debugcam.h"
#include "model.h"
#include <ctime>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

#define PERFORMANCE_TEST 1

#define LEVEL_DISTANCE 40
#define LEVEL_LENGTH 120
#define LEVEL_WIDTH 5

/*
void drawRect(muon::graphics::DebugRenderer* dr, muon::math::Rectf r)
{
    using namespace muon;
    using namespace math;
    dr->addLine(Vec3f(r.x, r.y, 0), Vec3f(r.x,r.getBottom(),0));
    dr->addLine(Vec3f(r.x, r.y, 0), Vec3f(r.getRight(),r.y,0));
    dr->addLine(Vec3f(r.x, r.getBottom(), 0), Vec3f(r.getRight(),r.getBottom(),0));
    dr->addLine(Vec3f(r.getRight(), r.y, 0), Vec3f(r.getRight(),r.getBottom(),0));
}

*/


namespace muongame {

    using namespace muon;
    using namespace math;

    class TestGame : public Application
    {
    public:
        TestGame(graphics::Window* window) : Application(window), cam(Vec3f(0, 1, 1)),
        plane(planeV, sizeof(planeV), planeI, sizeof(planeI))
        {
            instance = this;
        }

        static TestGame* instance;

        DebugRenderer debugRenderer;


    private:

        static GLfloat planeV[12];
        static GLuint planeI[6];


        Texture *t,*t2,*t3;
        Shader* shader;
        DebugCam cam;
        Model plane;

        float mapScroll = 0;
        int mapOffset = 0;

        bool map[LEVEL_WIDTH*LEVEL_LENGTH];

        void loadResources() {
            t = TextureManager::instance().loadTexture("resources/textures/test.png", "test");
            t2 = TextureManager::instance().loadTexture("resources/textures/test2.png", "test2");
            t3 = TextureManager::instance().loadTexture("resources/textures/fat.jpg", "fat");

            shader = new Shader("resources/shaders/simpleVertex.glsl", "resources/shaders/simpleFragment.glsl");

        }

        void init() {

            glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            ShaderManager::useShader(shader);
            ShaderManager::setProjectionMatrix(Mat4::perspective(80, window->getAspectRatio(), 0.1f, 500.0f));

            for(int z = 0; z < LEVEL_LENGTH; z++) {
                for(int x = 0; x < LEVEL_WIDTH; x++) {
                    map[x+LEVEL_WIDTH*z] = x != z % LEVEL_WIDTH;
                }
            }


        }

        void update(double deltaTime) {
            cam.update(deltaTime);

            //map update
            if(mapOffset + LEVEL_DISTANCE < LEVEL_LENGTH) {
                mapScroll -= 0.5f * deltaTime;
                if(mapScroll < -1.0f) {
                    mapScroll = 0;
                    mapOffset++;
                }
            }
        }

        void render() {



            //Set view matrix
            ShaderManager::useShader(shader);
            ShaderManager::setViewMatrix(cam.viewMatrix);

            //Debug rendering
            debugRenderer.addAABB(AABBf(Vec3f(1,0,1), Vec3f(2,1,2)));

            debugRenderer.addLine(Vec3f::zero, Vec3f::i);
            debugRenderer.addLine(Vec3f::zero, Vec3f::j, Color(COL_GREEN));
            debugRenderer.addLine(Vec3f::zero, Vec3f::k, Color(COL_BLUE));

            debugRenderer.draw();

            //Map uniforms
            ShaderManager::useShader(shader);
            shader->setUniform3f("camPos", cam.position);
            shader->setUniform1f("colorDivisions", 30.0f);
            shader->setUniformColor("base_color", Color(COL_CYAN));
            shader->setUniform1f("mapScroll", mapScroll);

            for(int z = 0; z < LEVEL_DISTANCE; z++)
            {
                for(int x = 0; x < LEVEL_WIDTH; x++)
                {
                    if(map[x+(z+mapOffset)*5]) {
                        ShaderManager::setModelMatrix(Mat4::translation(Vec3f(x,0,z+mapScroll)));
                        plane.draw();
                    }
                }
            }

        }

        void dispose() {
            TextureManager::instance().unloadAllTextures();
        }
    };

    GLfloat TestGame::planeV[] = {
        0,0,0,
        0,0,1,
        1,0,1,
        1,0,0,
    };

    GLuint TestGame::planeI[] = {
        2,3,1,
        1,0,3,
    };

    TestGame* TestGame::instance = NULL;

}


int main(int argc, char* args[])
{
    using namespace muon;
    using namespace graphics;
    using namespace muongame;

    Window w("Muon Engine v0.01", 960, 540, Color(COL_PURPLE));

    TestGame game(&w);
    game.run();

    return 0;
}


