
#include "muon.h"
#include "graphics/shadermanager.h"
#include "build_info.h"

#define PERFORMANCE_TEST 1

void printError(int error, const char* description);

int main(int argc, char* args[])
{
	using namespace muon;
	using namespace graphics;
	using namespace input;
	using namespace math;

	glfwSetErrorCallback(printError);

	INFO("Muon Engine Starting...");
	INFO("Version " << ME_VERSION_MAJOR << "." << ME_VERSION_MINOR);

	Window w("Muon Engine v0.01", 960, 540);

	if (!w.isRunning()) {
		return -1;
	}

	//glClearColor(0.5, 0.3, 0.8, 1);

	Color c(COL_PURPLE);

    //TODO: Change
	glClearColor(c.getRf(), c.getGf(), c.getBf(), c.getAf());
	glfwSwapInterval(0);

    TextureManager texManager;

    Texture* t = texManager.loadTexture("resources/textures/test.png", "test");
    Texture* t2 = texManager.loadTexture("resources/textures/test2.png", "test2");
    Texture* t3 = texManager.loadTexture("resources/textures/fat.jpg", "fat");

    Shader* shader = new Shader("resources/shaders/basicVertex.glsl", "resources/shaders/basicFragment.glsl");

	Vec3f pos(-8, 5, 0);

	srand((unsigned int)time(NULL));



	Input::init(w);

	float f = 0;
	float z = 0;
	float th = 0;

	Timer fps;
	Timer delta;
	double dt = 0;
	int frames = 0;

	float r = w.getWidth() / 60.0f;
	float b = w.getHeight() / 60.0f;



	while (w.isRunning()) {

		//Pre-update
		Input::beginFrame(w);
		delta.reset();
		glfwPollEvents();

		//Input checks
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) w.close();

		//Pre-render
		w.clear();


		//Update

        ShaderManager::useShader(shader);
		Vec2f mpos = Input::getMousePosition();
        shader->setUniform2f("lightpos", Vec2f(mpos.x * r / (float)w.getWidth()*2.0f - r, (b - mpos.y * b / (float)w.getHeight()) * 2 - b));

		th += 0.5f;

		//Rendering


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

	glfwTerminate();
	//system("PAUSE");
	return 0;
}



void printError(int error, const char* description)
{
	ERR(description);
}
