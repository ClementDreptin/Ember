#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GameEngine {
	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;

		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void uploadUniformFloat4(const std::string& name, const glm::vec4& values);
	private:
		uint32_t m_RendererID;
	};
}