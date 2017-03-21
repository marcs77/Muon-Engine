#include "color.h"

namespace muon {
	Color::Color() : hex(0) {}
	Color::Color(uint32 hex) : hex(hex) {}
	Color::Color(byte r, byte g, byte b, byte a)
		: r(r), g(g), b(b), a(a) {}
	Color::Color(math::Vec4f vec) : r(vec.x * 255.0f), g(vec.y * 255.0f), b(vec.z * 255.0f), a(vec.w * 255.0f) {}
}
