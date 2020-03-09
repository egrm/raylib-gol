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

void NextBoard(short board[][boardSide]) {
    /* Any live cell with two or three neighbors survives. */
    /* Any dead cell with three live neighbors becomes a live cell. */
    /* All other live cells die in the next generation. Similarly, all other
     * dead cells stay dead. */

    short tempBoard[boardSide][boardSide];

    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            short livingNeighbors = 0;

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
    memcpy(board, tempBoard, sizeof(short[boardSide][boardSide]));
}

void RandomizeBoard(short board[][boardSide]) {
    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            board[x][y] = rand() % 2;
        }
    }
}

void NullifyBoard(short board[][boardSide]) {
    for (int x = 0; x < boardSide; x++) {
        for (int y = 0; y < boardSide; y++) {
            board[x][y] = 0;
        }
    }
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

    NullifyBoard(board);

    IntVector2 lastMousePositionOnBoard;
    lastMousePositionOnBoard.x = boardSide + 1;
    lastMousePositionOnBoard.y = boardSide + 1;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        IntVector2 mousePositionOnBoard = GetMousePositionOnBoard();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
            // TODO: can the repetition in the conditions be removed here?
            mousePositionOnBoard.x != lastMousePositionOnBoard.x &&
            mousePositionOnBoard.y != lastMousePositionOnBoard.y) {

            // TODO: clean this up (bit operations?)
            short cellState =
                board[mousePositionOnBoard.x][mousePositionOnBoard.y];

            board[mousePositionOnBoard.x][mousePositionOnBoard.y] =
                cellState == 0 ? 1 : 0;
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