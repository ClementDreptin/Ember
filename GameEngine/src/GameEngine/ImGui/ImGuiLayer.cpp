#include "gepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "GameEngine/App.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GameEngine {
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::onAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach() {

	}

	void ImGuiLayer::onUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        App& app = App::get();
        io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        time = m_Time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseButtonPressedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::onMouseButtonPressedEvent));
        dispatcher.dispatch<MouseButtonReleasedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::onMouseButtonReleasedEvent));
        dispatcher.dispatch<MouseMovedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::onMouseMovedEvent));
        dispatcher.dispatch<MouseScrolledEvent>(GE_BIND_EVENT_FN(ImGuiLayer::onMouseScrolledEvent));
        dispatcher.dispatch<KeyPressedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::onKeyPressedEvent));
        dispatcher.dispatch<KeyReleasedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::onKeyReleasedEvent));
        dispatcher.dispatch<KeyTypedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::onKeyTypedEvent));
        dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(ImGuiLayer::onWindowResizeEvent));
	}

    bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.getMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.getMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(event.getX(), event.getY());

        return false;
    }

    bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += event.getYOffset();
        io.MouseWheelH += event.getXOffset();

        return false;
    }

    bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.getKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.getKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        int keyCode = event.getKeyCode();

        if (keyCode > 0 && keyCode < 0x10000) {
            io.AddInputCharacter((unsigned short)keyCode);
        }

        return false;
    }

    bool ImGuiLayer::onWindowResizeEvent(WindowResizeEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(event.getWidth(), event.getHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, event.getWidth(), event.getHeight());

        return false;
    }
}