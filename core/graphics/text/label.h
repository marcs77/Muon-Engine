#ifndef LABEL_H
#define LABEL_H


#include "../../math/vec2.h"
#include "../../util/color.h"
#include "font.h"
#include <string>

#include "../renderable2d.h"

namespace muon {
	namespace graphics {

		class Label {

		public:
			
			Label(std::string text, float x, float y, Font* f, Color color = Color(COL_WHITE));
			Label(std::string text, math::Vec2f position, Font* f, Color color = Color(COL_WHITE));

			Font* font;
			std::string text;
			math::Vec2f position;
			Color color;

		};
	}
}

#endif // !LABEL_H
