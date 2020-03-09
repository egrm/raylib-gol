#include "raylib.h"
#include <stdlib.h>
#include <string.h>

#define screenWidth 800
#define screenHeight 800

#define deadColor DARKBLUE
#define aliveColor RAYWHITE

#define boardSide 80

typedef struct {
    int x;
    int y;
} IntVector2;

const float cellSide = (screenHeight > screenWidth)
                           ? (screenWidth / boardSide)
                           : (screenHeight / boardSide);

void DrawBoard(unsigned char board[boardSide][boardSide], float cellSide) {
    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            DrawRectangle(cellSide * x, cellSide * y, cellSide, cellSide,
                          board[x][y] == 0 ? deadColor : aliveColor);
        }
    }
}

IntVector2 GetMousePositionOnBoard() {
    Vector2 mousePosition = GetMousePosition();

    IntVector2 boardPosition;

    boardPosition.x = boardSide * mousePosition.x / screenWidth;
    boardPosition.y = boardSide * mousePosition.y / screenHeight;

    return boardPosition;
}

void NextBoard(unsigned char board[boardSide][boardSide]) {
    /* Any live cell with two or three neighbors survives. */
    /* Any dead cell with three live neighbors becomes a live cell. */
    /* All other live cells die in the next generation. Similarly, all other
     * dead cells stay dead. */

    unsigned char tempBoard[boardSide][boardSide];

    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            unsigned char livingNeighbors = 0;

            livingNeighbors += board[x][y - 1];
            livingNeighbors += board[x][y + 1];
            livingNeighbors += board[x + 1][y];
            livingNeighbors += board[x - 1][y];
            livingNeighbors += board[x - 1][y - 1];
            livingNeighbors += board[x + 1][y + 1];
            livingNeighbors += board[x + 1][y - 1];
            livingNeighbors += board[x - 1][y + 1];

            if (board[x][y] == 1 &&
                (livingNeighbors == 2 || livingNeighbors == 3)) {
                tempBoard[x][y] = 1;
            } else if (board[x][y] == 0 && livingNeighbors == 3) {
                tempBoard[x][y] = 1;
            } else {
                tempBoard[x][y] = 0;
            }
        }
    }

    // TODO: is this a memory leak?
    memcpy(board, tempBoard, sizeof(unsigned char[boardSide][boardSide]));
}

void RandomizeBoard(unsigned char board[boardSide][boardSide]) {
    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            board[x][y] = rand() % 2;
        }
    }
}

void NullifyBoard(unsigned char board[boardSide][boardSide]) {
    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            board[x][y] = 0;
        }
    }
}

int main(void) {
    /* Initialization */

    InitWindow(screenWidth, screenHeight, "game of life");

    Vector2 rectPosition = {-100.0f, -100.0f};
    Vector2 rectSize = {20.0f, 20.0f};

    SetTargetFPS(60);

    unsigned char board[boardSide][boardSide];

    NullifyBoard(board);

    IntVector2 lastMousePositionOnBoard;
    lastMousePositionOnBoard.x = boardSide + 1;
    lastMousePositionOnBoard.y = boardSide + 1;

    /* Main game loop */
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        /* Update */

        IntVector2 mousePositionOnBoard = GetMousePositionOnBoard();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
            // TODO: can the repetition in the conditions be removed here?
            (mousePositionOnBoard.x != lastMousePositionOnBoard.x ||
             mousePositionOnBoard.y != lastMousePositionOnBoard.y)) {

            // TODO: clean this up (bit operations?)
            unsigned char cellState =
                board[mousePositionOnBoard.x][mousePositionOnBoard.y];

            board[mousePositionOnBoard.x][mousePositionOnBoard.y] =
                cellState == 0 ? 1 : 0;

            lastMousePositionOnBoard = mousePositionOnBoard;
        }

        if (IsKeyDown(KEY_SPACE)) {
            NextBoard(board);
        }

        if (IsKeyPressed(KEY_R)) {
            RandomizeBoard(board);
        }

        if (IsKeyPressed(KEY_C)) {
            NullifyBoard(board);
        }

        /* Draw */

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawBoard(board, cellSide);

        EndDrawing();
    }

    /* De-Initialization */

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
