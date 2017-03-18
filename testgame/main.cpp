#include <muon.h>
#include "build_info.h"
#include "debugcam.h"
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
	using namespace graphics;

    class TestGame : public Application
    {
    public:
        TestGame(graphics::Window* window) : Application(window), cam(Vec3f(0, 1, 1)),
        plane(planeV, sizeof(planeV), planeI, sizeof(planeI)), 
			nano("resources/models/nanosuit.obj")
        {

		}	
		

        static TestGame* instance;

        DebugRenderer debugRenderer;
		StandardRenderer renderer;

    private:

        static GLfloat planeV[12];
        static GLuint planeI[6];

        static GLfloat texturedQuadV[32];
        static GLuint texturedQuadI[6];

        Texture *t,*t2,*t3;
        Shader* mapShader;
        Shader* standard;
        DebugCam cam;
        MeshData plane;
		MeshData* texQuad;
		Model nano;

        float mapScroll = 0;
        int mapOffset = 0;

        bool map[LEVEL_WIDTH*LEVEL_LENGTH];
		

		Vertex v[4];
		GLuint in[6];
		std::vector<Vertex> verts;
		std::vector<GLuint> indices;
		std::vector<Texture*> tex;

        void loadResources() {
            t = TextureManager::instance().loadTexture("resources/textures/test.png");
            t2 = TextureManager::instance().loadTexture("resources/textures/test2.png");
            t3 = TextureManager::instance().loadTexture("resources/textures/fat.jpg");

            mapShader = new Shader("resources/shaders/mapVertex.glsl", "resources/shaders/mapFragment.glsl");
            standard = new Shader("resources/shaders/simpleVertex.glsl", "resources/shaders/simpleFragment.glsl");

			
			v[0].position = Vec3f(0, 0, 0);
			v[1].position = Vec3f(0, 1, 0);
			v[2].position = Vec3f(1, 1, 0);
			v[3].position = Vec3f(1, 0, 0);
			v[0].uv = Vec2f(0, 0);
			v[1].uv = Vec2f(0, 1);
			v[2].uv = Vec2f(1, 1);
			v[3].uv = Vec2f(1, 0);

			
			for (int i = 0; i < 4; i++) {
				verts.push_back(v[i]);
			}
			in[0] = 2;
			in[1] = 3;
			in[2] = 1;
			in[3] = 1;
			in[4] = 3;
			in[5] = 0;

			
			for (int i = 0; i < 6; i++) {
				indices.push_back(in[i]);
			}
			tex.push_back(t);
			
			texQuad = new MeshData(verts, indices, tex);

        }

        void init() {

            INFO(Vec3f(2,-3,1).normalized());

            glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            ShaderManager::useShader(mapShader);
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
            ShaderManager::useShader(mapShader);
            ShaderManager::setViewMatrix(cam.viewMatrix);

            //Debug rendering
            debugRenderer.addAABB(AABBf(Vec3f(1,0,1), Vec3f(2,1,2)));

            debugRenderer.addLine(Vec3f::zero, Vec3f::i, Color(COL_RED));
            debugRenderer.addLine(Vec3f::zero, Vec3f::j, Color(COL_GREEN));
            debugRenderer.addLine(Vec3f::zero, Vec3f::k, Color(COL_BLUE));

            debugRenderer.draw();
			
            //Map uniforms
            ShaderManager::useShader(mapShader);
            mapShader->setUniform3f("camPos", cam.position);
            mapShader->setUniform1f("colorDivisions", 30.0f);
            mapShader->setUniformColor("base_color", Color(COL_CYAN));
            mapShader->setUniform1f("mapScroll", mapScroll);

            for(int z = 0; z < LEVEL_DISTANCE; z++)
            {
                for(int x = 0; x < LEVEL_WIDTH; x++)
                {
                    if(map[x+(z+mapOffset)*5]) {
                        ShaderManager::setModelMatrix(Mat4::translation(Vec3f(x,0,z+mapScroll)));
                        plane.drawElements();
                    }
                }
            }

            ShaderManager::useShader(standard);
            ShaderManager::setModelMatrix(Mat4::translation(Vec3f(-1,1,-1)));
			glActiveTexture(GL_TEXTURE0);
            t3->bind();
            texQuad->drawElements();
			
			ShaderManager::useShader(standard);
			Mat4 transform = Mat4::translation(Vec3f(0, 0, 0)) * Mat4::scale(0.3);
			renderer.drawModel(&transform, &nano);

        }

        void dispose() {
            TextureManager::instance().unloadAllTextures();
            delete mapShader;
            delete standard;
			delete texQuad;
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
        1,3,0,
    };

    GLfloat TestGame::texturedQuadV[] = {
        0,0,0, 0,0, 0.9345, -0.801, 0.267,
        0,1,0, 0,1, 0.5345, 0.801, 0.267,
        1,1,0, 1,1, 0.2345, -0.301, 0.667,
        1,0,0, 1,0, 0.1345, 0.401, 0.967,
    };

    GLuint TestGame::texturedQuadI[] = {
        2,1,3,
        1,0,3
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


