#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cmath>

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
	int NEIGHBOUR_COUNT = 0;
	vector<int> TO_DIE;
	vector<int> TO_LIVE;
	vector<int> ALIVE_REF;
	int AUTOMATA_OFCHOICE = 0;
	int COL_CHECK;
	int COOLDOWN_CONFIRM = 1;
	Color SELEC_COL = { 255, 255, 255, 100 };
	for (int i = 0; i < 40000; i++) {
		ALIVE_REF.push_back(0);
	};
	InitWindow(1000, 1000, "Rafael's Game Of Computation");
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
			CELL_REF.push_back({TILE_X, TILE_Y, 4, 4});
			if (ALIVE_REF[TILE_COUNT] == 1 && (fmod(TILE_COUNT + 1, 200) != 0 && fmod(TILE_COUNT, 200) != 0 && TILE_COUNT > 199 && TILE_COUNT < 39799)) {
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
			if (IsKeyPressed(KEY_LEFT_SHIFT)) {
				switch (COOLDOWN_CONFIRM) {
					case 0:
						COOLDOWN_CONFIRM = 1;
						break;
					case 1:
						COOLDOWN_CONFIRM = 0;
						break;
				};
			};
			if (IsKeyPressed(KEY_R)) {
				for (int i = 0; i < 40000; i++) {
					ALIVE_REF[i] = round(rand()%2);
				};
			};
			if (IsKeyPressed(KEY_A)) {
				for (int i = 0; i < 40000; i++) {
					ALIVE_REF[i] = 1;
				};
			};
			if (IsKeyPressed(KEY_C)) {
				for (int i = 0; i < 40000; i++) {
					ALIVE_REF[i] = 0;
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
			if (IsKeyPressed(KEY_F)) {
				switch (AUTOMATA_OFCHOICE) {
					case 0:
						AUTOMATA_OFCHOICE = 1;
						break;
					case 1:
						AUTOMATA_OFCHOICE = 0;
						break;
				};
			};
			SELECTOR = { SELECTOR_X, SELECTOR_Y, SELECTOR_W, SELECTOR_H };
			DrawRectangleRec(SELECTOR, SELEC_COL);
			DrawText("press space to start", 0, 0, 25, LIGHTGRAY);
			DrawText("press a to fill screen", 0, 25, 25, LIGHTGRAY);
			DrawText("arrow keys to move tiles", 0, 50, 25, LIGHTGRAY);
			DrawText("enter to place cell", 0, 75, 25, LIGHTGRAY);
			DrawText("press c to clear screen", 0, 100, 25, LIGHTGRAY);
			DrawText("press w to increase brush size", 0, 125, 25, LIGHTGRAY);
			DrawText("press s to decrease brush size", 0, 150, 25, LIGHTGRAY);
			DrawText("press f to switch automatas", 0, 175, 25, LIGHTGRAY);
			DrawText("press r for a random arrangement of cells", 0, 200, 25, LIGHTGRAY);
			DrawText("press left shift to toggle cooldown", 0, 225, 25, LIGHTGRAY);
			if (COOLDOWN_CONFIRM == 1) {
				DrawText("COOLDOWN: ON", 0, 950, 25, GREEN);
			} else {
				DrawText("COOLDOWN: OFF", 0, 950, 25, GREEN);
			};
			if (AUTOMATA_OFCHOICE == 0) {
				DrawText("CONWAY'S GAME OF LIFE", 0, 975, 25, GREEN);
			} else {
				DrawText("RAFAEL'S GAME OF COMPUTATION", 0, 975, 25, GREEN);
			};
		};
		if (CELL_GENERATING == 1) {
			if (IsKeyPressed(KEY_P)) {
				CELL_GENERATING = 0;
			};
			if (COOLDOWN_CONFIRM == 1) {
				this_thread::sleep_for(0.05s);
			};
			for (int i = 0; i < TO_DIE.size(); i++) {
				ALIVE_REF[TO_DIE[i]] = 0;
			};
			for (int i = 0; i < TO_LIVE.size(); i++) {
				ALIVE_REF[TO_LIVE[i]] = 1;
			};
			TO_DIE.clear();
			TO_LIVE.clear();
			for (int i = 0; i < 40000; i++) {
				NEIGHBOUR_COUNT = 0;
				if (AUTOMATA_OFCHOICE == 0) {
					// CONWAY'S GAME OF LIFE
					if (ALIVE_REF[i] == 1) {
						if ((i + 1) % 200 != 0 && i % 200 != 0 && i > 199 && i < 39799) {
							if (ALIVE_REF[i + 1] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 1] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 200] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 200] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 201] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 199] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 201] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 199] == 1) {
								NEIGHBOUR_COUNT++;
							};
							switch (NEIGHBOUR_COUNT) {
								case 2:
									break;
								case 3:
									break;
								default:
									TO_DIE.push_back(i);
									break;
							};
						};
					}
					else {
						if ((i + 1) % 200 != 0 && i % 200 != 0 && i > 199 && i < 39799) {
							if (ALIVE_REF[i + 1] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 1] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 200] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 200] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 201] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 199] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 201] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 199] == 1) {
								NEIGHBOUR_COUNT++;
							};
							switch (NEIGHBOUR_COUNT) {
								case 3:
									TO_LIVE.push_back(i);
									break;
								default:
									break;
							};
						};
					};
				} else {
					// RAFAEL'S GAME OF COMPUTATION
					if (ALIVE_REF[i] == 1) {
						if ((i + 1) % 200 != 0 && i % 200 != 0 && i > 199 && i < 39799) {
							if (ALIVE_REF[i + 1] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 1] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 200] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 200] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 201] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 199] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 201] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 199] == 1) {
								NEIGHBOUR_COUNT++;
							};
							switch (NEIGHBOUR_COUNT) {
								case 1:
									break;
								case 2:
									break;
								default:
									TO_DIE.push_back(i);
									break;
							};
						};
					}
					else {
						if ((i + 1) % 200 != 0 && i % 200 != 0 && i > 199 && i < 39799) {
							if (ALIVE_REF[i + 1] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 1] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 200] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 200] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 201] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i + 199] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 201] == 1) {
								NEIGHBOUR_COUNT++;
							};
							if (ALIVE_REF[i - 199] == 1) {
								NEIGHBOUR_COUNT++;
							};
							switch (NEIGHBOUR_COUNT) {
								case 2:
									TO_LIVE.push_back(i);
									break;
								default:
									break;
							};
						};
					};
				};
			};
			DrawFPS(0, 0);
			DrawText("press p to pause", 0, 20, 25, RAYWHITE);
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