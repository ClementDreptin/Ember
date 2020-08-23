#include "gepch.h"
#include "Layer.h"

namespace GameEngine {
	Layer::Layer(const std::string& name) : m_DebugName(name) {}
	Layer::~Layer() {}
}