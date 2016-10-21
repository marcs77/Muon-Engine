#include "window.h"

namespace muon {
	namespace graphics {

        Window::Window(const char * title, int width, int height, Color clearColor) :
            _title(title), _width(width), _height(height)
		{
			if (!init()) {
				_running = false;
				glfwTerminate();
			}
			else {
				_running = true;
                setClearColor(clearColor);
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{

			if (glfwInit()) {
				DEBUG("GLFW initialized.");
			}
			else {
                ERR("GLFW failed to init.");
				return false;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

			_window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
			if (!_window) {
                ERR("Could not create window.");
				return false;
			}
			glfwMakeContextCurrent(_window);
			glfwSetWindowSizeCallback(_window, window_size_callback);
			glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
			
			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			INFO("OpenGL: " << glGetString(GL_VERSION));

            glViewport(0, 0, _width, _height);

			glfwSetWindowUserPointer(_window, this);

			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //TODO: Add VSYNC, fps lock, ...
            glfwSwapInterval(0);

			return true;
		}

		void Window::update() 
		{
			if (glfwWindowShouldClose(_window)) {
				_running = false;
			}

			glfwSwapBuffers(_window);
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::isRunning() const {
			return _running;
		}

		void Window::destroy() const {
			glfwDestroyWindow(_window);
		}

		void Window::close()
		{
			_running = false;
		}

		void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void Window::window_size_callback(GLFWwindow* window, int width, int height) 
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->_width = width;
			win->_height = height;

		}

        void Window::setClearColor(const Color& c) {
            if(!_running) return;
            _clearColor = c;
            glClearColor(_clearColor.getRf(), _clearColor.getGf(), _clearColor.getBf(), _clearColor.getAf());
        }
	}
}
