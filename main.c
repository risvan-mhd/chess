#include <raylib.h>

#define WIDTH 800
#define HEIGHT 800
#define TITLE "Chess"

#define ROWS 8
#define COLS 8
#define CELL_SIZE (WIDTH / 8)
#define DARK_CELL_COLOR ((Color){118, 150, 86, 255})
#define LIGHT_CELL_COLOR ((Color){238, 238, 210, 255})


typedef enum {
    EMPTY,
    PAWN,
} PieceType;

typedef enum {
    PIECE_NONE,
    PIECE_BLACK,
    PIECE_WHITE,
} PieceColor;

typedef struct {
    PieceType type;
    PieceColor color;
} Piece;


Piece board[ROWS][COLS];

// Piece textures
Texture2D black_pawn;
Texture2D white_pawn;


void set_piece(int row, int col, PieceType type, PieceColor color) {
    Piece *p = &board[row][col];
    p->type = type;
    p->color = color;
}

void init_board(void) {
    set_piece(0, 0, PAWN, PIECE_BLACK);
    set_piece(0, 1, PAWN, PIECE_WHITE);
}

void load_textures(void) {
    black_pawn = LoadTexture("./assets/bp.png");
    white_pawn = LoadTexture("./assets/wp.png");

    SetTextureFilter(black_pawn, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(white_pawn, TEXTURE_FILTER_BILINEAR);
}
void unload_textures(void) {
    UnloadTexture(black_pawn);
    UnloadTexture(white_pawn);
}


void draw_piece(int row, int col) {
    Piece *p = &board[row][col];
    if (p->type == EMPTY)
        return;

    Texture2D texture;
    if (p->type == PAWN) {
        texture = p->color == PIECE_BLACK ? black_pawn : white_pawn;
    }

    int x = col * CELL_SIZE;
    int y = row * CELL_SIZE;

    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height},
                   (Rectangle){x, y, (int)CELL_SIZE, (int)CELL_SIZE},
                   (Vector2){0, 0}, 0.0f, WHITE);
}

void draw_board(void) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            int x = c * CELL_SIZE;
            int y = r * CELL_SIZE;
            Color color = (r + c) % 2 == 0 ? LIGHT_CELL_COLOR : DARK_CELL_COLOR;

            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, color);
            draw_piece(r, c);
        }
    }
}


int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(60);

    init_board();
    load_textures();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_board();
        EndDrawing();
    }

    unload_textures();
    CloseWindow();
    return 0;
}
