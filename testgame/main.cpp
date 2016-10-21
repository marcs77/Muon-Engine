
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

    Window w("Muon Engine v0.01", 960, 540, Color(COL_LIGHT_GREY));

	if (!w.isRunning()) {
		return -1;
    }

    TextureManager texManager;

    Texture* t = texManager.loadTexture("resources/textures/test.png", "test");
    Texture* t2 = texManager.loadTexture("resources/textures/test2.png", "test2");
    Texture* t3 = texManager.loadTexture("resources/textures/fat.jpg", "fat");

    Shader* shader = new Shader("resources/shaders/testVertex.glsl", "resources/shaders/testFragment.glsl");

	Input::init(w);

	Timer fps;
	Timer delta;
	double dt = 0;
	int frames = 0;

	float r = w.getWidth() / 60.0f;
	float b = w.getHeight() / 60.0f;

    GLfloat vertices[] = {
         0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  // Top Right F
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,  // Bottom Right F
        -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,  // Bottom Left F
        -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // Top Left F
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f, 1.0f,  // Top Right F
		 0.5f, -0.5f,-0.5f, 1.0f, 0.0f, 1.0f,  // Bottom Right F
		-0.5f, -0.5f,-0.5f, 1.0f, 1.0f, 0.0f,  // Bottom Left F
		-0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 1.0f,  // Top Left F
    };

    GLuint indices[] = {
        0,1,3,
        3,2,1,
		4,5,7,
		7,6,5,

    };

    VertexArray* vao = new VertexArray();
    Buffer* vbo = new Buffer();
    Buffer* ebo = new Buffer(GL_ELEMENT_ARRAY_BUFFER);

    vbo->load(vertices, sizeof(vertices));
    ebo->load(indices, sizeof(indices));

    VertexArray::bind(vao);
    vao->addVertexAttributePointer(vbo, 0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
    vao->addVertexAttributePointer(vbo, 1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)12);
    Buffer::bind(ebo);
    VertexArray::unbind();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	ShaderManager::useShader(shader);
	ShaderManager::setProjectionMatrix(Mat4::perspective(80, w.getAspectRatio(), 0.1f, 500.0f));
	
	

	Vec3f position(0, 0, -2.0f);
	float angle = 0;

	Mat4 view;


	while (w.isRunning()) {

		//Pre-update
		Input::beginFrame(w);
		delta.reset();
		glfwPollEvents();

		//Input checks
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) w.close();
		
		if (Input::isKeyHeld(GLFW_KEY_W)) position -= Vec3f(0, 0, 2 * dt);
		if (Input::isKeyHeld(GLFW_KEY_S)) position += Vec3f(0, 0, 2 * dt);
		if (Input::isKeyHeld(GLFW_KEY_A)) position -= Vec3f(2 * dt, 0, 0);
		if (Input::isKeyHeld(GLFW_KEY_D)) position += Vec3f(2 * dt, 0, 0);
		if (Input::isKeyHeld(GLFW_KEY_SPACE)) position += Vec3f(0, 2 * dt, 0);
		if (Input::isKeyHeld(GLFW_KEY_LEFT_SHIFT)) position -= Vec3f(0, 2 * dt, 0);


		//Update


		//angle += dt * 1.1f;
		//Vec3f camPos = position + Vec3f(std::cosf(angle)*3.0f, 0, std::sinf(angle)*3.0f);
		view = Mat4::lookAt(Vec3f(), position);

		ShaderManager::setViewMatrix(view);
        //ShaderManager::useShader(shader);
        //Vec2f mpos = Input::getMousePosition();
        //shader->setUniform2f("lightpos", Vec2f(mpos.x * r / (float)w.getWidth()*2.0f - r, (b - mpos.y * b / (float)w.getHeight()) * 2 - b));

		//Pre-render
		w.clear();

		//Rendering
		ShaderManager::setModelMatrix(Mat4::translation(position));
        VertexArray::bind(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        VertexArray::unbind();
		

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

    delete vao;
    delete vbo;
    delete ebo;

    texManager.unloadAllTextures();

	glfwTerminate();
	//system("PAUSE");
	return 0;
}



void printError(int error, const char* description)
{
	ERR(description);
}
