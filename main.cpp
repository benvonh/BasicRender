#include "raylib.h"
#include "rlimgui.h"
#include "imgui.h"

#include <iostream>

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Raylib basic window");
	SetTargetFPS(60);
	rlImGuiSetup(true);
	char buf[1024];
	float f = 0.f;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("It works!", 20, 20, 20, BLACK);
		rlImGuiBegin();
		ImGui::Text("Hello, world %d", 123);
		if (ImGui::Button("Save"))
			std::cout << "hi\n";
		ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		rlImGuiEnd();
		EndDrawing();
	}
	rlImGuiShutdown();
	CloseWindow();
	return 0;
}