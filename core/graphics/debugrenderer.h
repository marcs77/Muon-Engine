#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H
#include "shader.h"
#include "shadermanager.h"
#include <vector>
#include "../math/vec3.h"
#include "buffer/buffer.h"
#include "buffer/vertexarray.h"
#include "../util/log.h"
#include "mat4.h"
#include "../math/aabb.h"
#include "util/color.h"

namespace muon {
namespace graphics {
	
	class DebugRenderer
	{

	public:
		DebugRenderer();
        ~DebugRenderer();

        void addLine(const math::Vec3f& a, const math::Vec3f& b, Color color = Color(COL_RED));
        void addLine(const math::Vec3f& a, const math::Vec3f& b, Color c1, Color c2);

        void addAABB(const math::AABBf& box, Color color = Color(COL_GREEN));
        void addCross(const math::Vec3f& point, float size = 0.2f);

        void draw();


		void setLineWidth(float width) const;

	private:
        constexpr static int MAX_LINES = 200;
		constexpr static int FLOATS_PER_LINE = 6; // x,y,z, r,g,b
		constexpr static int SIZE = MAX_LINES * 2 * FLOATS_PER_LINE;
		GLfloat lines [SIZE];
		std::vector<GLfloat> currentLines;

		int drawnLines;

		Shader shader;
        Buffer* vertexBuffer;
        VertexArray* vao;
		
	};


}
}

#endif // !DEBUGRENDERER_H
