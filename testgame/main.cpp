
#include "muon.h"
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
		system("pause");
		return -1;
	}

	//glClearColor(0.5, 0.3, 0.8, 1);

	Color c(COL_PURPLE);

	glClearColor(c.getRf(), c.getGf(), c.getBf(), c.getAf());
	glfwSwapInterval(0);

	TextureManager texManager;

	Texture* t = texManager.loadTexture("resources/textures/test.png", "test");
	Texture* t2 = texManager.loadTexture("resources/textures/test2.png", "test2");
	Texture* t3 = texManager.loadTexture("resources/textures/fat.jpg", "test3");

	Shader shader("resources/shaders/basicVertex.glsl", "resources/shaders/basicFragment.glsl");

	BatchRenderer2D batchRenderer;

	TileLayer tileLayer(&batchRenderer, &shader);
	BasicLayer textLayer(&batchRenderer, &shader, Mat4::ortho(0, w.getWidth(), w.getHeight(), 0, -2, 10));

	Font font;

	Label l("xdDdDfDghfGuil97687Ñ", 0, 40, &font);

	Vec3f pos(-8, 5, 0);



	srand((unsigned int)time(NULL));

	read_file("killme");

#if PERFORMANCE_TEST


	float increment = 40;
	float sz = increment*0.9f;
	int count = 0;

	for (float y = 0; y < 540; y += increment) {
		for (float x = 0; x < 960; x += increment) {
			tileLayer.add(new Sprite(x, y, sz, sz,
				math::Vec4f(rand() % 1000 / 1000.0f, 1, 1, 1), count % 2 == 0 ? t : t3));
			count++;
		}
	}

	INFO("Sprites: " << count);

	//#else
	Group *g = new Group(Mat4::translation(pos));
	Group *g2 = new Group(Mat4::translation(Vec3f(0, 0, 0)));
	g->add(new Sprite(0, 0, 5, 3, Vec4f(1, 1, 1, 1), NULL, Vec2f(-0.3f, 0.5f)));
	g2->add(new Sprite(0, 0, 2, 2, Vec4f(1, 1, 1, 1), NULL, Vec2f(0.5f, 0.5f)));
	g->add(g2);

	tileLayer.add(g);
#endif

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
#if PERFORMANCE_TEST

		g->matrix.setIdentity();
		g->matrix.translate(pos + Vec3f(f, 0, 0));
		g->matrix *= Mat4::rotation(Vec3f(0, 0, th));
#endif


		shader.use();
		Vec2f mpos = Input::getMousePosition();
		shader.setUniform2f("lightpos", Vec2f(mpos.x * r / (float)w.getWidth()*2.0f - r, (b - mpos.y * b / (float)w.getHeight()) * 2 - b));
		shader.disable();

		th += 0.5f;

		//Rendering
		tileLayer.render();
		textLayer.submitLabel(&l);

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

	glfwTerminate();
	//system("PAUSE");
	return 0;
}



void printError(int error, const char* description)
{
	ERR(description);
}