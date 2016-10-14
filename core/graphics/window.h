#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../util/log.h"
#include "../util/color.h"

namespace muon { namespace graphics {
	class Window {
	private:
		const char* _title;
		int _width, _height;
		GLFWwindow* _window;
		bool _running;

        Color _clearColor;

		bool init();


	public:
        Window(const char* title, int width, int height, Color clearColor = Color(COL_PURPLE));
		~Window();
		
		void update();
		void clear() const;
		bool isRunning() const;
		void destroy() const;
		void close();

        void setClearColor(const Color& c);

        inline const Color* getClearColor() const { return &_clearColor; }

		inline int getWidth() const { return _width; }
		inline int getHeight() const { return _height; }

		inline GLFWwindow* getWindow() const { return _window; }

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void window_size_callback(GLFWwindow* window, int width, int height);
	

		
	};
}}


#endif // !WINDOW_H
