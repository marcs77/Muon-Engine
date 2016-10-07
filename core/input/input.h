#ifndef INPUT_H
#define INPUT_H

//#define USEARRAY

#include <map>
#include "../graphics/window.h"
#include "../math/vec2.h"

namespace muon { namespace input {

	class Input
	{
	public:
		static void init(const graphics::Window& window);

		static void beginFrame(const graphics::Window& window);

		inline static bool isKeyPressed(int key)	{ return m_PressedKeys[key]; }
		inline static bool isKeyReleased(int key)	{ return !m_PressedKeys[key]; } //TODO: Add released array
		inline static bool isKeyHeld(int key)		{ return m_HeldKeys[key]; }

		static bool isMouseButtonPressed(int mb)	{ return m_PressedMouseButtons[mb]; }
		static bool isMouseButtonReleased(int mb)	{ return !m_PressedMouseButtons[mb]; }
		static bool isMouseButtonHeld(int mb)		{ return m_HeldMouseButtons[mb]; }

		inline static double getMouseX() { return mx; }
		inline static double getMouseY() { return my; }
		inline static math::Vec2f getMousePosition() { return math::Vec2f((float)mx, (float)my); }

	private:

		static bool m_PressedKeys[];
		static bool m_HeldKeys[];

		static bool m_PressedMouseButtons[];
		static bool m_HeldMouseButtons[];

		
		static double mx, my;

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	};

}
}

#endif // !INPUT_H
