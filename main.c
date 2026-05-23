#include <raylib.h>

#define WIDTH 800
#define HEIGHT 800
#define TITLE "Chess"


int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        EndDrawing();
    }

    return 0;
}
