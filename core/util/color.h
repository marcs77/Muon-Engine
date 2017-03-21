#ifndef COLOR_H
#define COLOR_H

#include "../types.h"

#define COL_WHITE		0xFFFFFFFF
#define COL_LIGHT_GREY	0xBDBDBDFF
#define COL_GREY		0x7F7F7FFF
#define COL_DARK_GREY	0x3F3F3FFF
#define COL_BLACK		0x000000FF
#define COL_RED			0xFF0000FF
#define COL_GREEN		0x00FF00FF
#define COL_BLUE		0x0000FFFF
#define COL_CYAN		0x00FFFFFF
#define COL_MAGENTA		0xFF00FFFF
#define COL_YELLOW		0xFFFF00FF
#define COL_PURPLE		0x7F4CCCFF


#include "../math/vec4.h"

namespace muon {
	struct Color {

		union {
			uint32 hex;
			struct {
				byte a, b, g, r;
			};
		};

		Color();
		Color(uint32 h);
		Color(byte r, byte g, byte b, byte a);
		Color(math::Vec4f vec);

		inline math::Vec4f getColor4f() const { return math::Vec4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }
		inline unsigned int ABGR() const { return a << 24 | b << 16 | g << 8 | r; }
		inline float getRf() const { return r / 255.0f; }
		inline float getGf() const { return g / 255.0f; }
		inline float getBf() const { return b / 255.0f; }
		inline float getAf() const { return a / 255.0f; }

	};
}

#endif // !COLOR_H
