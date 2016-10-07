#include "batchrenderer2d.h"

namespace muon {
	namespace graphics {
		BatchRenderer2D::BatchRenderer2D()
		{
			glGenVertexArrays(1, &_vao);
			glGenBuffers(1, &_vbo);

			glBindVertexArray(_vao);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)offsetof(VertexData, VertexData::uv));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)offsetof(VertexData, VertexData::tid));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const void*)offsetof(VertexData, VertexData::color));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLushort indices[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
				indices[ i ] = offset + 0;
				indices[i+1] = offset + 1;
				indices[i+2] = offset + 2;
				indices[i+3] = offset + 2;
				indices[i+4] = offset + 3;
				indices[i+5] = offset + 0;

				offset += 4;
			}

			_ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
			glBindVertexArray(0);

		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete _ibo;
			glDeleteBuffers(1, &_vbo);
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D& renderable)
		{

			const math::Vec4f& color = renderable.getColor();
			const math::Vec2f *uvs = renderable.getUVs();
			const GLuint tid = renderable.getTextureID();

			unsigned int c = Color(color).ABGR();
			
			int ts = getTextureSlot(tid);
			
			_buffer->vertex = *_back * renderable.getVertex(0);
			_buffer->uv = uvs[0];
			_buffer->tid = ts;
			_buffer->color = c;
			_buffer++;

			_buffer->vertex = *_back * renderable.getVertex(1);
			_buffer->uv = uvs[1];
			_buffer->tid = ts;
			_buffer->color = c;
			_buffer++;

			_buffer->vertex = *_back * renderable.getVertex(2);
			_buffer->uv = uvs[2];
			_buffer->tid = ts;
			_buffer->color = c;
			_buffer++;

			_buffer->vertex = *_back * renderable.getVertex(3);
			_buffer->uv = uvs[3];
			_buffer->tid = ts;
			_buffer->color = c;
			_buffer++;

			_indexCount += 6;

		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush()
		{

			for (int i = 0; i < _textureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, _textureSlots[i]);
			}

			glBindVertexArray(_vao);
			_ibo->bind();
			
			glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, NULL);

			glBindVertexArray(0);
			_ibo->unbind();

			_indexCount = 0;
		}

		int BatchRenderer2D::getTextureSlot(const GLuint tid)
		{
			int ts = 0;

			if (tid > 0) {

				bool found = false;
				for (int i = 0; i < _textureSlots.size(); i++) {
					if (_textureSlots[i] == tid) {
						return i;
					}
				}

				if (_textureSlots.size() >= 32) {
					end();
					flush();
					begin();
					_textureSlots.clear();
				}

				_textureSlots.push_back(tid);
				return _textureSlots.size() - 1;

			}
			
			return -1;
		}

		void BatchRenderer2D::submitLabel(const Label & label)
		{
/*
            //TODO: Remove atlas debug
            {
                const GLuint tid = label.font->getAtlas()->id;

                unsigned int c = Color(COL_WHITE).ABGR();

                int ts = getTextureSlot(tid);

                _buffer->vertex = *_back * math::Vec3f(0,0,0);
                _buffer->uv = math::Vec2f(0,0);
                _buffer->tid = ts;
                _buffer->color = c;
                _buffer++;

                _buffer->vertex = *_back * math::Vec3f(0,1024,0);
                _buffer->uv = math::Vec2f(0,1);
                _buffer->tid = ts;
                _buffer->color = c;
                _buffer++;

                _buffer->vertex = *_back * math::Vec3f(1024,1024,0);
                _buffer->uv = math::Vec2f(1,1);
                _buffer->tid = ts;
                _buffer->color = c;
                _buffer++;

                _buffer->vertex = *_back * math::Vec3f(1024,0,0);
                _buffer->uv = math::Vec2f(1,0);
                _buffer->tid = ts;
                _buffer->color = c;
                _buffer++;

                _indexCount += 6;
            }

            /////////*/



			const GLuint tid = label.font->getAtlas()->id;

			unsigned int c = label.color.ABGR();

			int ts = getTextureSlot(tid);

			float off = 0.0f;

			for (int i = 0; i < label.text.length(); i++) {
				char ch = label.text.at(i);
				texture_glyph_t* glyph = texture_font_get_glyph(label.font->getFont(), &ch);

				if(glyph != NULL) {
					if (i > 0) {
						float kerning = texture_glyph_get_kerning(glyph, &label.text.at(i-1));
						off += kerning;
					}


					float x0 = label.position.x + glyph->offset_x + off;
					float y0 = label.position.y - glyph->offset_y;
					float x1 = x0 + glyph->width;
					float y1 = y0 + glyph->height;
					float& u0 = glyph->s0;
					float& v0 = glyph->t0;
					float& u1 = glyph->s1;
					float& v1 = glyph->t1;

					_buffer->vertex = math::Vec3f(x0, y0, 0);
					_buffer->uv = math::Vec2f(u0, v0);
					_buffer->tid = ts;
					_buffer->color = c;
					_buffer++;

					_buffer->vertex = math::Vec3f(x0, y1, 0);
					_buffer->uv = math::Vec2f(u0, v1);
					_buffer->tid = ts;
					_buffer->color = c;
					_buffer++;

					_buffer->vertex = math::Vec3f(x1, y1, 0);
					_buffer->uv = math::Vec2f(u1, v1);
					_buffer->tid = ts;
					_buffer->color = c;
					_buffer++;

					_buffer->vertex = math::Vec3f(x1, y0, 0);
					_buffer->uv = math::Vec2f(u1, v0);
					_buffer->tid = ts;
					_buffer->color = c;
					_buffer++;

					_indexCount += 6;

					off += glyph->advance_x;

				}
			}
			
		}

	}
}
