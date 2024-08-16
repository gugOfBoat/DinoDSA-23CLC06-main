#include "C:\\raylib\\raylib\\src\\raylib.h"
#include "Dino.h"
#include <fstream>
#include <string>
#include <algorithm>
#include "moving_object.h"
#include "deque.h"

// Constants
const float windowWidth = 1000;
const float windowHeight = 600;

// Game Variables
int score = 0;
int topscore;
Deque<Trap*> traps;

// Load the top scores from the file
void LoadTopScores() {
    std::ifstream inFile("src/topscores.txt");
    if (!(inFile >> topscore)) topscore = 0;
    inFile.close();
}

// Update the top scores in the file
void UpdateTopScores(int newscore) {
    if (score > topscore) {
        topscore = score;
        std::ofstream outFile("src/topscores.txt");
        outFile << topscore;
        outFile.close();
    }
}

// Draw the start screen
void DrawStartScreen(Texture2D startScreen) {
    BeginDrawing(); 
    ClearBackground(RAYWHITE);
    DrawTexture(startScreen, 112, 84, WHITE);
    EndDrawing(); 
}

// Handle the start screen events
void HandleStartScreen(Texture2D startScreen) {
    while (!WindowShouldClose()) {
        DrawStartScreen(startScreen);
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }
    UnloadTexture(startScreen);
}

// Spawn a new trap with a random type
void SpawnTrap(Texture2D cactus1, Texture2D cactus2, Texture2D cactus3) {
    int cactusType = rand() % 3;
    Texture2D selectedCactus;
    
    switch (cactusType) {
        case 0:
            selectedCactus = cactus1;
            break;
        case 1:
            selectedCactus = cactus2;
            break;
        case 2:
            selectedCactus = cactus3;
            break;
    }

    Vector2 spawnPos = {1000, 500};  // Position of spawn
    int speed = 5;
    
    Trap* newTrap = new Trap(spawnPos, selectedCactus, speed);
    traps.push_back(newTrap);
}

// Update traps and check for collisions
void UpdateTraps(Dino* dino) {
    for (int i = 0; i < traps.size(); ++i) {
        traps[i]->Update();

        if (traps[i]->IsCollision(dino)) {
            dino->TakeDamage(50);
        }

        // Remove trap if it goes off-screen
        if (traps[i]->GetRect().x + traps[i]->GetRect().width < 0) {
            delete traps[i];
            traps.pop_front();
            i--;  // Adjust index after pop front
        }
    }
}

// Draw all traps in the deque
void DrawTraps() {
    for (int i = 0; i < traps.size(); ++i) {
        traps[i]->Draw();
    }
}

// Clean up traps when they are no longer needed
void CleanupTraps() {
    while (!traps.isEmpty()) {
        delete traps.front();
        traps.pop_front();
    }
}

// Update the game state, including Dino, traps, and score
void UpdateGame(Dino* dino, float& groundX1, float& groundX2, bool& isPaused, Texture2D stopButton, Texture2D cactus1, Texture2D cactus2, Texture2D cactus3) {
    if (!isPaused) {
        score += 1;
        dino->Update();
        groundX1 -= 5.0f;
        groundX2 -= 5.0f;

        if (groundX1 <= -windowWidth) groundX1 = windowWidth;
        if (groundX2 <= -windowWidth) groundX2 = windowWidth;

        // Randomly spawn a new trap every 2 seconds on average
        if (rand() % 120 == 0) {
            SpawnTrap(cactus1, cactus2, cactus3);
        }

        // Update traps
        UpdateTraps(dino);

        if (dino->isDead()) {
            isPaused = true;
        }
    }

    // Pause the game if the stop button is clicked
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (mousePos.x >= 950 && mousePos.x <= 950 + static_cast<float>(stopButton.width) &&
            mousePos.y >= 0 && mousePos.y <= static_cast<float>(stopButton.height)) {
            isPaused = true;
        }
    }
}

// Draw the game, including Dino, traps, ground, and score
void DrawGame(Dino* dino, float groundX1, float groundX2, Texture2D groundTexture, Texture2D stopButton, bool isGameOver, Texture2D replayButton) {
    BeginDrawing();
    ClearBackground(WHITE);

    DrawTextureEx(groundTexture, {groundX1, windowHeight - groundTexture.height}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(groundTexture, {groundX2, windowHeight - groundTexture.height}, 0.0f, 1.0f, WHITE);

    // Draw traps from deque
    DrawTraps();
    
    dino->Draw();

    DrawText(TextFormat("Score: %i", score / 5), 10, 10, 20, BLACK);
    if (topscore > (score / 5)) {
        DrawText(TextFormat("HighestScore: %i", topscore), 10, 30, 20, BLACK);
    } else {
        DrawText(TextFormat("HighestScore: %i", (score / 5)), 10, 30, 20, BLACK);
    }

    DrawTexture(stopButton, 950, 0, WHITE);

    if (isGameOver) {
        DrawText("Game Over", windowWidth / 2 - 100, windowHeight / 2 - 40, 40, RED);
        DrawTexture(replayButton, windowWidth / 2 - static_cast<float>(replayButton.width) / 2, windowHeight / 2, WHITE);
    }

    EndDrawing();
}

// Handle game over and check if the replay button is clicked
bool HandleGameOver(Texture2D replayButton) {
    Vector2 mousePos = GetMousePosition();
    Rectangle replayRect = {windowWidth / 2 - static_cast<float>(replayButton.width) / 2, windowHeight / 2, static_cast<float>(replayButton.width), static_cast<float>(replayButton.height)};
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, replayRect)) {
        return true;
    }
    return false;
}

// Clean up resources before exiting the game
void Cleanup(Texture2D groundTexture, Texture2D stopButton, Texture2D replayButton, Dino* dino, Texture2D cactus1, Texture2D cactus2, Texture2D cactus3) {
    UnloadTexture(groundTexture);
    UnloadTexture(stopButton);
    UnloadTexture(replayButton);
    UnloadTexture(cactus1);
    UnloadTexture(cactus2);
    UnloadTexture(cactus3);
    CleanupTraps();
    delete dino;
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
    Texture2D replayButton = LoadTexture("Graphics/replay.png");
    Texture2D cactus1 = LoadTexture("Graphics/cactus1.png");
    Texture2D cactus2 = LoadTexture("Graphics/cactus2.png");
    Texture2D cactus3 = LoadTexture("Graphics/cactus3.png");

    Dino* dino = new Dino();

    float groundX1 = 0.0f;
    float groundX2 = windowWidth;
    bool isPaused = false;
    bool isGameOver = false;

    while (!WindowShouldClose()) {
        if (!isGameOver) {
            UpdateGame(dino, groundX1, groundX2, isPaused, stopButton, cactus1, cactus2, cactus3);
            isGameOver = dino->isDead();
        } else {
            if (HandleGameOver(replayButton)) {
                isGameOver = false;
                dino->resetHP();
                score = 0;
                CleanupTraps(); // Clear traps for the new game
            }
        }

        DrawGame(dino, groundX1, groundX2, groundTexture, stopButton, isGameOver, replayButton);
    }

    UpdateTopScores(score / 5);
    Cleanup(groundTexture, stopButton, replayButton, dino, cactus1, cactus2, cactus3);

    return 0;
}
