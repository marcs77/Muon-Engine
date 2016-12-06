#include "debugrenderer.h"

namespace muon {
namespace graphics {
	
	DebugRenderer::DebugRenderer() : 
		shader("resources/shaders/debugVertex.glsl", "resources/shaders/debugFragment.glsl"), 
        drawnLines(0), vao(new VertexArray()), vertexBuffer(new Buffer())
	{
        vertexBuffer->load(NULL, SIZE * sizeof(GLfloat), GL_DYNAMIC_DRAW);
        VertexArray::bind(vao);
		//TODO: use 4 bytes for loading the color
        vao->addVertexAttributePointer(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        vao->addVertexAttributePointer(vertexBuffer, 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
		VertexArray::unbind();

		setLineWidth(2);
	}

	void DebugRenderer::addLine(math::Vec3f a, math::Vec3f b, Color color)
	{
		addLine(a, b, color, color);
	}

	void DebugRenderer::addLine(math::Vec3f a, math::Vec3f b, Color c1, Color c2)
	{

		if (drawnLines == MAX_LINES) {
			WARNING("Reached limit of debug lines: " << MAX_LINES);
			return;
		}

		currentLines.push_back(a.x);
		currentLines.push_back(a.y);
		currentLines.push_back(a.z);
		currentLines.push_back(c1.getRf());
		currentLines.push_back(c1.getGf());
		currentLines.push_back(c1.getBf());

		currentLines.push_back(b.x);
		currentLines.push_back(b.y);
		currentLines.push_back(b.z);
		currentLines.push_back(c2.getRf());
		currentLines.push_back(c2.getGf());
		currentLines.push_back(c2.getBf());

		drawnLines++;
	}

	void DebugRenderer::draw()
	{
		ShaderManager::useShader(&shader);
		ShaderManager::setModelMatrix(math::Mat4::identity());

        Buffer::bind(vertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, currentLines.size() * sizeof(GLfloat), currentLines.data());
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

}
}
