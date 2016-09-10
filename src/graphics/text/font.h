#ifndef FONT_H
#define FONT_H

#include <freetype-gl.h>
#include <map>
#include <string>

namespace muon {
	namespace graphics {
		class Font {
		public:
			Font();
			//~Font();
			void load() const;

			inline ftgl::texture_atlas_t* getAtlas() const { return _ftAtlas; }
			inline ftgl::texture_font_t* getFont() const { return _ftFont; }

		private:
			ftgl::texture_atlas_t *_ftAtlas;
			ftgl::texture_font_t *_ftFont;

		};

		class FontManager {

			FontManager();
			//~FontManager();

			std::map<std::string, Font> _fonts;

		};
	}
}

#endif // !FONT_H
