
#include "muon.h"
#include "graphics/shadermanager.h"
#include "build_info.h"
#include "debugcam.h"
#include "model.h"
#include <ctime>
#include <vector>

#define PERFORMANCE_TEST 1

#define LEVEL_DISTANCE 40
#define LEVEL_LENGTH 120
#define LEVEL_WIDTH 5

void printError(int error, const char* description);

int main(int argc, char* args[])
{
	using namespace muon;
	using namespace graphics;
	using namespace input;
	using namespace math;
    using namespace muongame;

	glfwSetErrorCallback(printError);

	INFO("Muon Engine Starting...");
	INFO("Version " << ME_VERSION_MAJOR << "." << ME_VERSION_MINOR);

    Window w("Muon Engine v0.01", 960, 540, Color(COL_LIGHT_GREY));

    //int tu;
    //glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &tu);
    //INFO("Texture units: "<< tu);

	if (!w.isRunning()) {
		return -1;
    }

    TextureManager texManager;

    Texture* t = texManager.loadTexture("resources/textures/test.png", "test");
    Texture* t2 = texManager.loadTexture("resources/textures/test2.png", "test2");
    Texture* t3 = texManager.loadTexture("resources/textures/fat.jpg", "fat");

    Shader* shader = new Shader("resources/shaders/simpleVertex.glsl", "resources/shaders/simpleFragment.glsl");

	Input::init(w);

	Timer fps;
	Timer delta;
	double dt = 0;
	int frames = 0;

    srand((unsigned int)time(NULL));

    GLfloat planeV[] {
        0,0,0,
        0,0,1,
        1,0,1,
        1,0,0,
    };
    GLuint planeI[] = {
        2,3,1,
        1,0,3,
    };



    Model* plane = new Model(planeV, sizeof(planeV), planeI, sizeof(planeI));

    float theta = 0;

	ShaderManager::useShader(shader);
	ShaderManager::setProjectionMatrix(Mat4::perspective(80, w.getAspectRatio(), 0.1f, 500.0f));
	


    DebugCam debCam(Vec3f(0,1,1));
    glfwSetInputMode(w.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    bool map[LEVEL_WIDTH*LEVEL_LENGTH];

    for(int z = 0; z < LEVEL_LENGTH; z++) {
        for(int x = 0; x < LEVEL_WIDTH; x++) {
            map[x+LEVEL_WIDTH*z] = x != z % LEVEL_WIDTH;
        }
    }

    int mapOffset = 0;
    float mapScroll = 0;


	while (w.isRunning()) {

		//Pre-update
		Input::beginFrame(w);
		delta.reset();
		glfwPollEvents();

		//Input checks
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) w.close();


		//Update
        debCam.update(dt);

        ShaderManager::setViewMatrix(debCam.viewMatrix);
        shader->setUniform3f("camPos", debCam.position);

        if(mapOffset + LEVEL_DISTANCE < LEVEL_LENGTH) {
            mapScroll -= 0.5f * dt;
            if(mapScroll < -1.0f) {
                mapScroll = 0;
                mapOffset++;
            }
        }

        theta += 2 * dt;

		//Pre-render
		w.clear();

		//Rendering


        shader->setUniform1f("colorDivisions", 30.0f);
        shader->setUniformColor("base_color", Color(COL_CYAN));

        for(int z = 0; z < LEVEL_DISTANCE; z++)
        {
            for(int x = 0; x < LEVEL_WIDTH; x++)
            {
                if(map[x+(z+mapOffset)*LEVEL_WIDTH]) {
                    ShaderManager::setModelMatrix(Mat4::translation(Vec3f(x,0,z+mapScroll)));
                    plane->draw();
                }
            }
        }


        shader->setUniform1f("mapScroll", mapScroll);

		//End rendering
		w.update();

		//Time
		frames++;
		if (fps.elapsed() >= 1.0f) {
			fps.reset();
			INFO("FPS: " << frames);
			frames = 0;
		}
		dt = delta.elapsed();
	}

    texManager.unloadAllTextures();

    delete plane;

	glfwTerminate();
	//system("PAUSE");
	return 0;
}



void printError(int error, const char* description)
{
	ERR(description);
}
