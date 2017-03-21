#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "../common.h"
#include "shader/shader.h"
#include "shader/shadermanager.h"
#include <vector>
#include "../math/vec3.h"
#include "buffer/buffer.h"
#include "buffer/vertexarray.h"
#include "mat4.h"
#include "../math/aabb.h"


namespace muon {
namespace graphics {
	
	struct LineVertex 
	{
		math::Vec3f pos;
		unsigned int color;
	};

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
		constexpr static int VERTEX_SIZE = sizeof(LineVertex); 
		constexpr static int SIZE = MAX_LINES * VERTEX_SIZE;

		std::vector<LineVertex> currentLines;

		int drawnLines;

		Shader shader;
        Buffer* vertexBuffer;
        VertexArray* vao;
		
	};


}
}

#endif // !DEBUGRENDERER_H
