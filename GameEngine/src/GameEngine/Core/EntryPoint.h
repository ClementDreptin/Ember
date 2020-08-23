#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::App* GameEngine::CreateApp();

int main(int argc, char** argv) {
	GameEngine::Log::init();
	GE_CORE_INFO("Log initialized!");

	auto app = GameEngine::CreateApp();
	app->run();
	delete app;
}
#endif
