#include "../header/player.h"
#include <stdio.h>

void adjustButtonSize(int screenWidth, int screenHeight, float* buttonWidth, float* buttonHeight) {
	float buttonAspectRatio = (float)(*buttonWidth) / (*buttonHeight);
	float screenAspectRatio = (float)screenWidth / screenHeight;

	if (buttonAspectRatio > screenAspectRatio) {
		// Adjust button size based on screen height
		*buttonHeight = screenHeight * 0.08; // Adjust the factor as needed
		*buttonWidth = *buttonHeight * buttonAspectRatio;
	}
	else {
		// Adjust button size based on screen width
		*buttonWidth = screenWidth * 0.08; // Adjust the factor as needed
		*buttonHeight = *buttonWidth / buttonAspectRatio;
	}
}

int main() {
	int screenWidth = 800;
	int screenHeight = 700;
	int targetFPS = 60;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Character Select");
	SetTargetFPS(targetFPS);
	// float deltaTime = GetFrameTime();

	Rectangle backButton = { 0, 0, 150, 50 };
	Rectangle nextButton = { backButton.x + 160, 0, 150, 50 };
	int fontSize = (backButton.width < backButton.height ? backButton.width : backButton.height) / 5;
	
	loadPlayer();

	Camera2D camera = { 0 };
	Vector2 camPosition = { 20 , 20 };
	// camera.target = camPosition;
	camera.rotation = 0.0f;
	camera.zoom = 6.0f;

	camera.target.x = getPlayerPosition().x;
	camera.target.y = getPlayerPosition().y;
	camera.offset = (Vector2){ GetScreenWidth() / 2 - (getPlayer().width / 2), GetScreenHeight() / 2 - (getPlayer().height / 2)};

	Vector2 coordinates[20];
	int counter = 0;
	int x = 0;
	int y = 0;

	for (int i = 0; i < 20; i++) {
		// if we reach the max x frames reset x
		if (x > 4) {
			x = 0;
			y += 1;
		}
		coordinates[i].x = x;
		coordinates[i].y = y;
		x += 1;
	}

	char* character[20] = {
	"Zephyr",
	"Luna",
	"Aldric",
	"Faye",
	"Thorn",
	"Eira",
	"Kai",
	"Nyx",
	"Aria",
	"Galen",
	"Eldric",
	"Elara",
	"Dorian",
	"Lyra",
	"Soren",
	"Selene",
	"Rune",
	"Aurora",
	"Cyrus",
	"Nova"
	};

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground((Color) { 0x17, 0x17, 0x17, 0xFF });
		// deltaTime = GetFrameTime();

		if (GetScreenWidth() != screenWidth || GetScreenHeight() != screenHeight) {
			// screen resize event
			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();
			camera.target.x = getPlayerPosition().x;
			camera.target.y = getPlayerPosition().y;
			camera.offset = (Vector2){ GetScreenWidth() / 2 - (getPlayer().width / 2), GetScreenHeight() / 2 - (getPlayer().height / 2)};
		}
		fontSize = (backButton.width < backButton.height ? backButton.width : backButton.height) - 10;
		
		int actualScreenWidth = GetScreenWidth();
		int actualScreenHeight = GetScreenHeight();

		// Calculate the offset
		float offsetX = (actualScreenWidth - screenWidth) / 2.0f;
		float offsetY = (actualScreenHeight - screenHeight) / 2.0f;

		// Get mouse position
		Vector2 mousePos = GetMousePosition();

		// Apply offset
		mousePos.x -= offsetX;
		mousePos.y -= offsetY;

		if (CheckCollisionPointRec(mousePos, backButton)) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				if (counter > 0) {
					counter--;
				} else {
					counter = 19;
				}
				setPlayerRect(coordinates[counter]);
			}
		}
		
		if (CheckCollisionPointRec(mousePos, nextButton)) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				// x isnt greater than maxX then we can move right
				if (counter < 19) {
					counter++;
				}
				else {
					counter = 0;
				}
				setPlayerRect(coordinates[counter]);
			}
		}	
		BeginMode2D(camera);
			DrawTextureRec(getPlayer(), getPlayerRect(), getPlayerPosition(), WHITE);
			DrawText(character[counter], getPlayerPosition().x - MeasureText(character[counter], 10) / 2, getPlayerPosition().y - 10, 10, WHITE);
		EndMode2D();
		DrawRectangleRec(backButton, RED);
		DrawText("Back", backButton.x + (backButton.width / 2) - MeasureText("Back", fontSize) / 2, backButton.y + 5, fontSize, WHITE);
		DrawRectangleRec(nextButton, BLUE);
		DrawText("Next", nextButton.x + (nextButton.width / 2) - MeasureText("Next", fontSize) / 2, nextButton.y + 5, fontSize, WHITE);

		// snprintf(text, sizeof(text), "Score: %d", );
		// DrawText(text, 50, 150, 20, WHITE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

