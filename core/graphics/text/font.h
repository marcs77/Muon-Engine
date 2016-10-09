#ifndef FONT_H
#define FONT_H

#include <freetype-gl.h>
#include <map>
#include <string>

namespace muon {
	namespace graphics {

		class FontManager;

		class Font {
			friend class FontManager;
		public:
			//~Font();
			

			inline ftgl::texture_atlas_t* getAtlas() const { return _ftAtlas; }
			inline ftgl::texture_font_t* getFont() const { return _ftFont; }
			inline std::string getPath() const { return _path; }
			inline std::string getName() const { return _name; }

		private:

			Font(std::string path, std::string name, ftgl::texture_atlas_t* _ftAtlas, ftgl::texture_font_t* _ftFont);

			ftgl::texture_atlas_t *_ftAtlas;
			ftgl::texture_font_t *_ftFont;

			std::string _path;
			std::string _name;
		};

		class FontManager {
		public:
			FontManager();
			//~FontManager();
			inline Font* getFont(std::string name) { return _fonts[name]; }
			Font* load(std::string path, std::string name);
			Font* load(std::string path);

		private:
			std::map<std::string, Font*> _fonts;
		};
	}
}

#endif // !FONT_H
