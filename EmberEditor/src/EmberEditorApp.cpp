#include <Ember.h>
#include <Ember/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Ember {
	class EmberEditor : public App
	{
	public:
		EmberEditor()
			: App("Ember Editor")
		{
			PushLayer(new EditorLayer());
		}

		~EmberEditor() {}
	};

	App* CreateApp()
	{
		return new EmberEditor();
	}
}
