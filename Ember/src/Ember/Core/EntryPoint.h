#pragma once

#ifdef EB_PLATFORM_WINDOWS

extern Ember::App* Ember::CreateApp();

int main(int argc, char** argv) {
	Ember::Log::Init();
	EB_CORE_INFO("Log initialized!");

	auto app = Ember::CreateApp();
	app->Run();
	delete app;
}
#endif
