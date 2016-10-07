#include "label.h"

namespace muon {
	namespace graphics {

		Label::Label(std::string text, float x, float y, Font* f, Color color)
			: text(text), position(x, y), font(f), color(color) {}

		Label::Label(std::string text, math::Vec2f position, Font* f, Color color)
			: text(text), position(position), font(f), color(color) {}

	}
}