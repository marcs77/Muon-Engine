#include "font.h"
#include "../../util/log.h"

namespace muon {
	namespace graphics {

		Font::Font()
		{
            _ftAtlas = ftgl::texture_atlas_new(1024, 1024, 1);
            _ftFont = ftgl::texture_font_new_from_file(_ftAtlas, 50, "resources/fonts/unifont.ttf");

			if (!_ftFont) {
				ERR("Font not found.");
			}
 

            for (char c = -128; c < 127; c++) {
				ftgl::texture_font_load_glyph(_ftFont, (char*)&c);
			}


            char c = 0xF1;
            ftgl::texture_font_load_glyph(_ftFont, &c);

			glGenTextures(1, &_ftAtlas->id);
			glBindTexture(GL_TEXTURE_2D, _ftAtlas->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			GLint swizzle_mask[] = { GL_ONE, GL_ONE, GL_ONE, GL_RED }; 
			glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle_mask);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _ftAtlas->width, _ftAtlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, _ftAtlas->data);
		}

		void Font::load() const
		{

		}

	}
}
