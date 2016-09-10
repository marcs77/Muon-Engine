#include "input.h"
#include "../util/log.h"


namespace muon {
	namespace input {

		bool Input::m_PressedKeys[GLFW_KEY_LAST];
		bool Input::m_HeldKeys[GLFW_KEY_LAST];

		bool Input::m_PressedMouseButtons[GLFW_MOUSE_BUTTON_LAST];
		bool Input::m_HeldMouseButtons[GLFW_MOUSE_BUTTON_LAST];

		double Input::mx;
		double Input::my;

		void Input::init(const graphics::Window& window)
		{
			glfwSetKeyCallback(window.getWindow(), key_callback);
			glfwSetMouseButtonCallback(window.getWindow(), mouse_button_callback);

			for (int i = 0; i < GLFW_KEY_LAST; i++) m_PressedKeys[i] = false;
			for (int i = 0; i < GLFW_KEY_LAST; i++) m_HeldKeys[i] = false;
			for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) m_PressedMouseButtons[i] = false;
			for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) m_HeldMouseButtons[i] = false;
		}

		void Input::beginFrame(const graphics::Window& window)
		{
			glfwGetCursorPos(window.getWindow(), &mx, &my);

			for (int i = 0; i < GLFW_KEY_LAST; i++) m_PressedKeys[i] = false;
			for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) m_PressedMouseButtons[i] = false;	
		}


		void Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{

			if (key == GLFW_KEY_UNKNOWN) {
				DEBUG("Unknown key pressed or released.");
				return;
			}

			if (action == GLFW_PRESS) {
				m_PressedKeys[key] = true;
				m_HeldKeys[key] = true;
				DEBUG("Key: " << key);
			}
			else if (action == GLFW_RELEASE) {
				m_PressedKeys[key] = false;
				m_HeldKeys[key] = false;
			}
		}

		void Input::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			m_PressedMouseButtons[button] = action != GLFW_RELEASE;
			m_HeldMouseButtons[button] = action != GLFW_RELEASE;
		}
	}
}
