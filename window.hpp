#pragma once
#include "raylib.h"
#include "rlimgui.h"
#include "imgui.h"

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

template<size_t W, size_t H>
class Window final
{
public:
	explicit Window(const char *title)
		: M_camera{}, M_target{}
	{
		InitWindow(W, H, title);
		SetTargetFPS(120);
		rlImGuiSetup(true);

		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::GetIO().DeltaTime = 1.f / 120.f;

		M_camera = Camera(
			{ 4.f, 2.f, 4.f },
			{ 0.f, 1.f, 0.f },
			{ 0.f, 1.f, 0.f },
			45.f,
			CAMERA_PERSPECTIVE
		);

		M_target = LoadRenderTexture(W, H);
		SetTextureFilter(M_target.texture, TEXTURE_FILTER_BILINEAR);
	}

	Window(Window &&) = delete;
	Window(const Window &) = delete;
	Window &operator=(Window &&) = delete;
	Window &operator=(const Window &) = delete;

	~Window()
	{
		rlImGuiShutdown();
		CloseWindow();
	}

	void operator()()
	{
		unsigned frames = 0;
		auto time = std::chrono::steady_clock::now();

		float inc = 0.1f;

		while (!WindowShouldClose())
		{
			if (M_camera.position.x > 10.f)
				inc = -.1f;
			else if (M_camera.position.x < -10.f)
				inc = 0.1f;

			M_camera.position.x += inc;

			BeginDrawing();

			BeginTextureMode(M_target);
			ClearBackground(SKYBLUE);
			BeginMode3D(M_camera);
			DrawText("It works!", 20, 20, 20, BLACK);
			DrawGrid(10, 1.f);
			DrawCube({0, 1, 0}, 2, 2, 2, RED);
			EndMode3D();
			EndTextureMode();

			rlImGuiBegin();
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			ImGui::Begin("Viewport");
			rlImGuiImageRenderTexture(&M_target);
			ImGui::End();
			rlImGuiEnd();

			EndDrawing();

			frames++;
			auto now = std::chrono::steady_clock::now();

			if (now - time > 1s)
			{
				std::cout << "fps: " << frames << std::endl;
				frames = 0;
				time = now;
			}
		}
	}

private:
	Camera M_camera;
	RenderTexture2D M_target  ;
};