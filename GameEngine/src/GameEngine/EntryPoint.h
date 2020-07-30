#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::App* GameEngine::CreateApp();

int main(int argc, char** argv) {
	GameEngine::Log::init();
	GE_CORE_WARN("Log");
	int a = 5;
	GE_INFO("Hello! Var={0}", a);

	auto app = GameEngine::CreateApp();
	app->run();
	delete app;
}
#endif
