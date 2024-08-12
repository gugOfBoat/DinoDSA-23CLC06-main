#include "C:\\raylib\\raylib\\src\\raylib.h"
#include "Dino.h"
#include <fstream>
#include <string>
#include <algorithm>
#include "moving_object.h"
#include "deque.h"

const float windowWidth = 1000;
const float windowHeight = 600;

int score = 0;
int topscore;

void LoadTopScores() {
    std::ifstream inFile("src/topscores.txt");
    if (!(inFile >> topscore))
        topscore = 0;
    inFile.close();
}

void UpdateTopScores(int newscore)
{
    std::ofstream outFile("src/topscores.txt");
    if (score > topscore)
    {
        topscore = score;
        outFile << topscore;
    }
    outFile.close();
}

void DrawStartScreen(Texture2D startScreen) {
    BeginDrawing(); 
    ClearBackground(RAYWHITE);
    DrawTexture(startScreen, 112, 84, WHITE);
    EndDrawing(); 
}

void HandleStartScreen(Texture2D startScreen) {
    while (!WindowShouldClose()) {
        DrawStartScreen(startScreen);
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }
    UnloadTexture(startScreen);
}

void UpdateGame(Dino* dino, Rectangle& obstacle, float& groundX1, float& groundX2, bool& isPaused, Texture2D stopButton) {
    if (!isPaused) {
        score += 1;
        dino->Update();
        groundX1 -= 5.0f;
        groundX2 -= 5.0f;

        if (groundX1 <= -windowWidth)
            groundX1 = windowWidth;
        if (groundX2 <= -windowWidth)
            groundX2 = windowWidth;

        obstacle.x -= 5.0f;
        if (obstacle.x <= -obstacle.width)
            obstacle.x = windowWidth;

        bool isColliding = CheckCollisionRecs(dino->GetRect(), obstacle);
        if (isColliding) {
            dino->TakeDamage(50);
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (mousePos.x >= 950 && mousePos.x <= 950 + stopButton.width &&
            mousePos.y >= 0 && mousePos.y <= stopButton.height) {
            isPaused = true;
        }
    }
}

void DrawGame(Dino* dino, Rectangle obstacle, float groundX1, float groundX2, Texture2D groundTexture, Texture2D stopButton) {
    BeginDrawing();
    ClearBackground(WHITE);

    DrawTextureEx(groundTexture, {groundX1, windowHeight - groundTexture.height}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(groundTexture, {groundX2, windowHeight - groundTexture.height}, 0.0f, 1.0f, WHITE);
    DrawRectangleRec(obstacle, BLACK);
    dino->Draw();
    dino->DrawHitbox(CheckCollisionRecs(dino->GetRect(), obstacle));

    DrawText(TextFormat("Score: %i", score / 5), 10, 10, 20, BLACK);
    if (topscore > (score / 5))
        DrawText(TextFormat("HighestScore: %i", topscore), 10, 30, 20, BLACK);
    else 
        DrawText(TextFormat("HighestScore: %i", (score / 5)), 10, 30, 20, BLACK);

    DrawTexture(stopButton, 950, 0, WHITE);

    if (dino->isDead()) {
        UpdateTopScores(score / 5);
        DrawText("Game Over", windowWidth / 2 - 100, windowHeight / 2, 40, RED);
    }

    EndDrawing();
}

void Cleanup(Texture2D groundTexture, Texture2D stopButton, Dino* dino) {
    UnloadTexture(groundTexture);
    UnloadTexture(stopButton);
    delete dino;  // Giải phóng bộ nhớ của Dino
    CloseWindow();
}

int main() {
    LoadTopScores();
    InitWindow(windowWidth, windowHeight, "Dino Run");
    SetTargetFPS(60);

    Texture2D startScreen = LoadTexture("Graphics/started.png");
    HandleStartScreen(startScreen);

    Texture2D groundTexture = LoadTexture("Graphics/ground.png");
    Texture2D stopButton = LoadTexture("Graphics/stopButton.png");

    Dino* dino = new Dino();  // Cấp phát động cho Dino

    Rectangle obstacle = Rectangle{950, 550, 30, 30};

    float groundX1 = 0.0f;
    float groundX2 = windowWidth;
    bool isPaused = false;

    while (!WindowShouldClose()) {
        UpdateGame(dino, obstacle, groundX1, groundX2, isPaused, stopButton);
        DrawGame(dino, obstacle, groundX1, groundX2, groundTexture, stopButton);

        if (dino->isDead()) {
            break;
        }
    }

    Cleanup(groundTexture, stopButton, dino);

    return 0;
}
