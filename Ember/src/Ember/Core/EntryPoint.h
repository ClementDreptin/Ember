#pragma once

#ifdef EB_PLATFORM_WINDOWS

extern Ember::App* Ember::CreateApp();

int main(int argc, char** argv)
{
	Ember::Log::Init();

	EB_PROFILE_BEGIN_SESSION("Startup", "EmberProfile-Startup.json");
	auto app = Ember::CreateApp();
	EB_PROFILE_END_SESSION();

	EB_PROFILE_BEGIN_SESSION("Runtime", "EmberProfile-Runtime.json");
	app->Run();
	EB_PROFILE_END_SESSION();

	EB_PROFILE_BEGIN_SESSION("Shutdown", "EmberProfile-Shutdown.json");
	delete app;
	EB_PROFILE_END_SESSION();
}
#endif
