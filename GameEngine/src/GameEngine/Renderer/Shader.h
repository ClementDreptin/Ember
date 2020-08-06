#pragma once

#include <string>

namespace GameEngine {
	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;
	private:
		uint32_t m_RendererID;
	};
}