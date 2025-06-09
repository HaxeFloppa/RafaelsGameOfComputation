#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

unsigned char UCRand(int range) {
	return static_cast<unsigned char>(rand()%range);
};

Color RandomColor() {
	return {UCRand(256),UCRand(256),UCRand(256),255};
};

float SELECTOR_X = 0;
float SELECTOR_Y = 0;
float SELECTOR_W = 5;
float SELECTOR_H = 5;
Rectangle SELECTOR = { SELECTOR_X, SELECTOR_Y, SELECTOR_W, SELECTOR_H };
vector<Rectangle> CELL_REF;
bool SELEC_COLLIDE(int CELL_CHECK) {
	return CheckCollisionRecs(SELECTOR, CELL_REF[CELL_CHECK]);
};

int main(void) {
	float TILE_X = 0;
	float TILE_Y = 0;
	float TILE_COUNT = 0;
	Color COLOR_CHOICE = RAYWHITE;
	int COLOR_TOG = 0;
	int COLOR_IDEN = 0;
	int CELL_GENERATING = 0;
	vector<int> ALIVE_REF;
	int COL_CHECK;
	Color SELEC_COL = { 255, 255, 255, 100 };
	for (int i = 0; i < 40000; i++) {
		ALIVE_REF.push_back(0);
	};
	InitWindow(1000, 800, "Rafael's Game Of Computation");
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(DARKGRAY);
		if (IsKeyPressed(KEY_E)) {
			switch (COLOR_TOG) {
				case 0:
					COLOR_CHOICE = RAYWHITE;
					if (CELL_GENERATING == 1) {
						COLOR_TOG = 1;
					};
					COLOR_IDEN = 0;
					break;
				case 1:
					if (CELL_GENERATING == 1) {
						COLOR_CHOICE = RandomColor();
						COLOR_TOG = 0;
						COLOR_IDEN = 1;
						break;
					};
			};
		};
		if (IsKeyPressed(KEY_SPACE)) {
			CELL_GENERATING = 1;
		};
		while (!(TILE_X >= 1000) && !(TILE_Y >= 1000)) {
			CELL_REF.push_back({TILE_X, TILE_Y, 5, 5});
			if (ALIVE_REF[TILE_COUNT] == 1) {
				DrawRectangleRec(CELL_REF[TILE_COUNT], COLOR_CHOICE);
			} else {
				DrawRectangleRec(CELL_REF[TILE_COUNT], BLACK);
			};
			if (COLOR_IDEN == 1) {
				COLOR_CHOICE = RandomColor();
			};
			TILE_X = TILE_X + 5;
			TILE_COUNT++;
			if (TILE_X == 1000) {
				TILE_Y = TILE_Y + 5;
				TILE_X = 0;
			};
		};
		if (CELL_GENERATING == 0) {
			DrawText("press space to start", 0, 0, 25, DARKGRAY);
			DrawText("press a to fill screen", 0, 25, 25, DARKGRAY);
			DrawText("arrow keys to move tiles", 0, 50, 25, DARKGRAY);
			DrawText("enter to place cell", 0, 75, 25, DARKGRAY);
			DrawText("press c to clear screen", 0, 100, 25, DARKGRAY);
			DrawText("press w to increase brush size", 0, 125, 25, DARKGRAY);
			DrawText("press s to decrease brush size", 0, 150, 25, DARKGRAY);
			if (IsKeyDown(KEY_LEFT) && SELECTOR_X != 0) {
				SELECTOR_X = SELECTOR_X - 5;
			};
			if (IsKeyDown(KEY_RIGHT) && SELECTOR_X != 1000) {
				SELECTOR_X = SELECTOR_X + 5;
			};
			if (IsKeyDown(KEY_UP) && SELECTOR_Y != 0) {
				SELECTOR_Y = SELECTOR_Y - 5;
			};
			if (IsKeyDown(KEY_DOWN) && SELECTOR_Y != 1000) {
				SELECTOR_Y = SELECTOR_Y + 5;
			};
			if (IsKeyPressed(KEY_ENTER)) {
				COL_CHECK = 0;
				for (int i = 0; i < 40000; i++) {
					if (SELEC_COLLIDE(i)) {
						if (ALIVE_REF[i] == 0) {
							ALIVE_REF[i] = 1;
						}
						else {
							ALIVE_REF[i] = 0;
						};
					};
				};
			};
			if (IsKeyPressed(KEY_A)) {
				ALIVE_REF.clear();
				for (int i = 0; i < 40000; i++) {
					ALIVE_REF.push_back(1);
				};
			};
			if (IsKeyPressed(KEY_C)) {
				ALIVE_REF.clear();
				for (int i = 0; i < 40000; i++) {
					ALIVE_REF.push_back(0);
				};
			};
			if (IsKeyPressed(KEY_W)) {
				SELECTOR_W = SELECTOR_W + 5;
				SELECTOR_H = SELECTOR_H + 5;
			};
			if (IsKeyPressed(KEY_S)) {
				SELECTOR_W = SELECTOR_W - 5;
				SELECTOR_H = SELECTOR_H - 5;
			};
			SELECTOR = { SELECTOR_X, SELECTOR_Y, SELECTOR_W, SELECTOR_H };
			DrawRectangleRec(SELECTOR, SELEC_COL);
		};
		if (CELL_GENERATING == 1) {
			for (int i = 0; i < 40000; i++) {
				if (ALIVE_REF[i] == 1) {
					if ((i + 1) % 200 != 0 && i % 200 != 0 && i > 199 && i < 39799) {
						if (ALIVE_REF[i - 1] == 1 && ALIVE_REF[i+1] == 1) {
							ALIVE_REF[i] = 0;
						}
						else if (ALIVE_REF[i + 1] == 1 || ALIVE_REF[i-1] == 1) {
							ALIVE_REF[i] = 1;
						}
						else {
							ALIVE_REF[i] = 0;
						};
					};
				} else {
					if ((i + 1) % 200 != 0 && i % 200 != 0 && i > 199 && i < 39799) {
						if (ALIVE_REF[i - 1] == 1 || ALIVE_REF[i + 1] == 1) {
							ALIVE_REF[i] = 1;
						};
					};
				};
			};
			this_thread::sleep_for(0.05s);
		};
		EndDrawing();
		TILE_X = 0;
		TILE_Y = 0;
		TILE_COUNT = 0;
		CELL_REF.clear();
	};
	CloseWindow();
	return 0;
};