#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::App* GameEngine::CreateApp();

int main(int argc, char** argv) {
	auto app = GameEngine::CreateApp();
	app->run();
	delete app;
}
#endif
