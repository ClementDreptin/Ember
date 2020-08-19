#pragma once

#include <string>

namespace GameEngine {
	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Ref<Shader> create(const std::string& path);
		static Ref<Shader> create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}