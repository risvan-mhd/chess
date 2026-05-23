#include <raylib.h>

#define WIDTH 800
#define HEIGHT 800
#define TITLE "Chess"

#define CELL_SIZE (WIDTH / 8)
#define DARK_CELL_COLOR ((Color){118, 150, 86, 255})
#define LIGHT_CELL_COLOR ((Color){238, 238, 210, 255})


void draw_board(void) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int x = i * CELL_SIZE;
            int y = j * CELL_SIZE;
            Color color = (i + j) % 2 == 0 ? LIGHT_CELL_COLOR : DARK_CELL_COLOR;

            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, color);
        }
    }
}


int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_board();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
