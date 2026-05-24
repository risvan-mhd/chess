#include <raylib.h>
#include <stddef.h>

#define ARRAY_LEN(arr) (sizeof((arr)) / sizeof((arr)[0]))

#define WIDTH 800
#define HEIGHT 800
#define TITLE "Chess"

#define ROWS 8
#define COLS 8
#define CELL_SIZE (WIDTH / 8)
#define DARK_CELL_COLOR ((Color){118, 150, 86, 255})
#define LIGHT_CELL_COLOR ((Color){238, 238, 210, 255})


typedef enum {
    EMPTY = -1,
    PAWN,

    PIECE_COUNT,
} PieceType;

typedef enum {
    PIECE_NONE = -1,
    PIECE_BLACK,
    PIECE_WHITE,
} PieceColor;

typedef struct {
    PieceType type;
    PieceColor color;
} Piece;


Piece board[ROWS][COLS];

// Piece textures
Texture2D pieces[2][PIECE_COUNT];


void set_piece(int row, int col, PieceType type, PieceColor color) {
    Piece *p = &board[row][col];
    p->type = type;
    p->color = color;
}

void init_board(void) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            set_piece(r, c, EMPTY, PIECE_NONE);
        }
    }

    // Black pawns
    for (int i = 0; i < COLS; i++) {
        set_piece(1, i, PAWN, PIECE_BLACK);
        set_piece(6, i, PAWN, PIECE_WHITE);
    }
}

void load_textures(void) {
    pieces[PIECE_BLACK][PAWN] = LoadTexture("./assets/bp.png");
    pieces[PIECE_WHITE][PAWN] = LoadTexture("./assets/wp.png");

    for (size_t i = 0; i < ARRAY_LEN(pieces); i++) {
        for (size_t j = 0; j < ARRAY_LEN(pieces[i]); j++) {
            SetTextureFilter(pieces[i][j], TEXTURE_FILTER_BILINEAR);
        }
    }
}
void unload_textures(void) {
    for (size_t i = 0; i < ARRAY_LEN(pieces); i++) {
        for (size_t j = 0; j < ARRAY_LEN(pieces[i]); j++) {
            UnloadTexture(pieces[i][j]);
        }
    }
}


void draw_piece(int row, int col) {
    Piece *p = &board[row][col];
    if (p->type == EMPTY || p->color == PIECE_NONE)
        return;

    Texture2D texture = pieces[p->color][p->type];
    int x = col * CELL_SIZE;
    int y = row * CELL_SIZE;

    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height},
                   (Rectangle){x, y, (int)CELL_SIZE, (int)CELL_SIZE},
                   (Vector2){0, 0}, 0.0f, WHITE);
}

void draw_board(void) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
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
