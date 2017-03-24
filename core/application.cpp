#include "application.h"
#include "build_info.h"
#include "input/input.h"

namespace muon {

    Application::Application(graphics::Window* window) : window(window), deltaTime(0), frames(0) {}

    void Application::run()
    {
        glfwSetErrorCallback(printError);

        INFO("Muon Engine Starting...");
        INFO("Version " << ME_VERSION_MAJOR << "." << ME_VERSION_MINOR);

        if (!window->isRunning()) {
            return;
        }

        input::Input::init(*window);

        loadResources();
        init();

        while (window->isRunning()) {

            //Pre-update
            input::Input::beginFrame(*window);
            delta.reset();
            glfwPollEvents();


            //if (input::Input::isKeyPressed(GLFW_KEY_ESCAPE)) window->close();

            update(deltaTime);

            window->clear();
            render();
            window->update();

            //Time
            frames++;
            if (fps.elapsed() >= 1.0f) {
                fps.reset();
                INFO("FPS: " << frames);
                frames = 0;
            }
            deltaTime = delta.elapsed();
        }

        dispose();
    }


    void Application::init() {}
    void Application::loadResources() {}
    void Application::update(double deltaTime) {}
    void Application::render() {}
    void Application::dispose() {}


    void printError(int error, const char* description)
    {
        ERR(description);
    }
}
