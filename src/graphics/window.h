#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../util/log.h"

namespace muon { namespace graphics {
	class Window {
	private:
		const char* _title;
		int _width, _height;
		GLFWwindow* _window;
		bool _running;

		bool init();

	public:
		Window(const char* title, int width, int height);
		~Window();
		
		void update();
		void clear() const;
		bool isRunning() const;
		void destroy() const;
		void close();

		inline int getWidth() const { return _width; }
		inline int getHeight() const { return _height; }

		inline GLFWwindow* getWindow() const { return _window; }

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void window_size_callback(GLFWwindow* window, int width, int height);
	

		
	};
}}


#endif // !WINDOW_H
