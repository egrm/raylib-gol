#include "raylib.h"
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} IntVector2;

const int screenWidth = 400;
const int screenHeight = 400;

const int boardSide = 20;
const float cellSide = screenHeight > screenWidth ? screenWidth / boardSide
                                                  : screenHeight / boardSide;

Color deadColor = DARKBLUE;
Color aliveColor = RAYWHITE;

void DrawBoard(short cells[][boardSide], float cellSide) {
    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            DrawRectangle(cellSide * x, cellSide * y, cellSide, cellSide,
                          cells[x][y] == 0 ? deadColor : aliveColor);
        }
    }
}

IntVector2 GetMousePositionOnBoard() {
    Vector2 mousePosition = GetMousePosition();

    IntVector2 boardPosition;

    boardPosition.x = mousePosition.x / boardSide;
    boardPosition.y = mousePosition.y / boardSide;

    return boardPosition;
}

int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int boardSide = 20;

    InitWindow(screenWidth, screenHeight, "game of life");

    Vector2 rectPosition = {-100.0f, -100.0f};
    Vector2 rectSize = {20.0f, 20.0f};

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //-------------s--------------------------------------------------------------------------

    short board[boardSide][boardSide];

    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            board[x][y] = rand() % 2;
        }
    }

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            IntVector2 mousePositionOnBoard = GetMousePositionOnBoard();

            // TODO: clean this up (bit operations?)
            short cellState =
                board[mousePositionOnBoard.x][mousePositionOnBoard.y];

            board[mousePositionOnBoard.x][mousePositionOnBoard.y] =
                cellState == 0 ? 1 : 0;
        }

        /*     cellColor = MAROON; */
        /* else if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) */
        /*     cellColor = LIME; */
        /* else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) */
        /*     cellColor = DARKBLUE; */
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawBoard(board, cellSide);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
