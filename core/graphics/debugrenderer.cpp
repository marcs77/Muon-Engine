#include "debugrenderer.h"

namespace muon {
namespace graphics {
	
	DebugRenderer::DebugRenderer() : 
		shader("resources/shaders/debugVertex.glsl", "resources/shaders/debugFragment.glsl"), 
        drawnLines(0), vao(new VertexArray()), vertexBuffer(new Buffer())
	{
        vertexBuffer->load(NULL, SIZE, GL_DYNAMIC_DRAW);
        VertexArray::bind(vao);
        vao->addVertexAttributePointer(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (GLvoid*)0);
        vao->addVertexAttributePointer(vertexBuffer, 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(LineVertex), (GLvoid*)offsetof(LineVertex, LineVertex::color));
		VertexArray::unbind();

		setLineWidth(2);
	}

    void DebugRenderer::addLine(const math::Vec3f& a, const math::Vec3f& b, Color color)
	{
		addLine(a, b, color, color);
	}

    void DebugRenderer::addLine(const math::Vec3f& a, const math::Vec3f& b, Color c1, Color c2)
	{

		if (drawnLines == MAX_LINES) {
			WARNING("Reached limit of debug lines: " << MAX_LINES);
			return;
		}

		currentLines.push_back({ a, c1.ABGR() });
		currentLines.push_back({ b, c2.ABGR() });

		drawnLines++;
	}

	void DebugRenderer::draw()
	{
		ShaderManager::useShader(&shader);
		ShaderManager::setModelMatrix(math::Mat4::identity());
		//NOTE: Maybe use glMapBuffer?
        Buffer::bind(vertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, currentLines.size() * sizeof(LineVertex), currentLines.data());
        Buffer::unbind(vertexBuffer);

        VertexArray::bind(vao);
		glDrawArrays(GL_LINES, 0, drawnLines * 2);
		VertexArray::unbind();

        ShaderManager::disableShader();

		currentLines.clear();
		drawnLines = 0;
	}

	void DebugRenderer::setLineWidth(float width) const
	{
		glLineWidth(width);
	}

    DebugRenderer::~DebugRenderer() {
        delete vao;
        delete vertexBuffer;
    }

    void DebugRenderer::addAABB(const math::AABBf &box, Color color)
    {
        using namespace math;
        addLine(box.min, Vec3f(box.max.x, box.min.y, box.min.z), color);
        addLine(box.min, Vec3f(box.min.x, box.max.y, box.min.z), color);
        addLine(box.min, Vec3f(box.min.x, box.min.y, box.max.z), color);

        addLine(box.max, Vec3f(box.min.x, box.max.y, box.max.z), color);
        addLine(box.max, Vec3f(box.max.x, box.min.y, box.max.z), color);
        addLine(box.max, Vec3f(box.max.x, box.max.y, box.min.z), color);

        addLine(Vec3f(box.min.x, box.max.y, box.min.z), Vec3f(box.max.x, box.max.y, box.min.z), color);
        addLine(Vec3f(box.min.x, box.max.y, box.max.z), Vec3f(box.min.x, box.max.y, box.min.z), color);
        addLine(Vec3f(box.min.x, box.min.y, box.max.z), Vec3f(box.min.x, box.max.y, box.max.z), color);
        addLine(Vec3f(box.max.x, box.min.y, box.min.z), Vec3f(box.max.x, box.max.y, box.min.z), color);
        addLine(Vec3f(box.max.x, box.min.y, box.min.z), Vec3f(box.max.x, box.min.y, box.max.z), color);
        addLine(Vec3f(box.min.x, box.min.y, box.max.z), Vec3f(box.max.x, box.min.y, box.max.z), color);
    }

    void DebugRenderer::addCross(const math::Vec3f &point, float size)
    {
        using namespace math;
        Vec3f x(size,0,0);
        Vec3f y(0,size,0);
        Vec3f z(0,0,size);
        addLine(point - x, point + x);
        addLine(point - y, point + y);
        addLine(point - z, point + z);
    }

}
}
