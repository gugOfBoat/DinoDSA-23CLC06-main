#include "C:\\raylib\\raylib\\src\\raylib.h"
#include "Dino.h"
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include "moving_object.h"
#include "deque.h"
#include <chrono>

               
std::chrono::steady_clock::time_point lastGeneratedTime = std::chrono::steady_clock::now();
std::random_device rd;
std::mt19937 gen(rd());  // Initialize the random generator once
std::uniform_int_distribution<> dist(1, 10);


const float windowWidth = 1000;
const float windowHeight = 600;
const int InitialObjectCount = 20;

int score = 0;
int topscore;

void LoadTopScores() {
    std::ifstream inFile("src/topscores.txt");
    if (!(inFile >> topscore))
        topscore = 0;
    inFile.close();
}

void UpdateTopScores(int newscore) {
    std::ofstream outFile("src/topscores.txt");
    if (score > topscore) {
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

void GenerateInitialMovingObjects(Deque<MovingObject*>& movingObjects, Texture2D cactus1, Texture2D cactus2, Texture2D cactus3, Texture2D appleTex, Texture2D shieldTex) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    for (int i = 0; i < InitialObjectCount; ++i) {
        Vector2 position = {1000.0f + i * 200, 500.0f};  // Cách đều các objects

        int randNum = dist(gen);

        if (randNum <= 5) {  // 50% sinh bẫy
            int trapType = dist(gen) % 3;
            Texture2D selectedCactus = (trapType == 0) ? cactus1 : (trapType == 1) ? cactus2 : cactus3;
            movingObjects.push_back(new Trap(position, selectedCactus, 5));
        } else if (randNum <= 7) {  // 20% sinh Shield
            movingObjects.push_back(new Shield(position, shieldTex, 5));
        } else {  // 30% sinh Apple
            movingObjects.push_back(new Apple(position, appleTex, 5));
        }
    }
}

void GenerateNextMovingObject(Deque<MovingObject*>& movingObjects, Texture2D cactus1, Texture2D cactus2, Texture2D cactus3, Texture2D appleTex, Texture2D shieldTex) {
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - lastGeneratedTime;

    if (elapsedTime.count() >= 1.0f) {  // Generate a new object every second
        Vector2 position = {1000.0f, 500.0f};  // Set position at (1000, 500)
        int randNum = dist(gen);  // Generate a random number

        if (randNum <= 5) {  // 50% chance to generate a Trap
            int trapType = dist(gen) % 3;
            Texture2D selectedCactus = (trapType == 0) ? cactus1 : (trapType == 1) ? cactus2 : cactus3;
            movingObjects.push_back(new Trap(position, selectedCactus, 5));
        } else if (randNum <= 7) {  // 20% chance to generate a Shield
            movingObjects.push_back(new Shield(position, shieldTex, 5));
        } else {  // 30% chance to generate an Apple
            movingObjects.push_back(new Apple(position, appleTex, 5));
        }

        lastGeneratedTime = currentTime;  // Reset the timer
    }
}

void UpdateGame(Dino* dino, Deque<MovingObject*>& movingObjects, float& groundX1, float& groundX2, bool& isPaused, Texture2D stopButton, Texture2D cactus1, Texture2D cactus2, Texture2D cactus3, Texture2D appleTex, Texture2D shieldTex) {
    if (!isPaused) {
        score += 1;
        dino->Update();
        groundX1 -= 5.0f;
        groundX2 -= 5.0f;

        if (groundX1 <= -windowWidth)
            groundX1 = windowWidth;
        if (groundX2 <= -windowWidth)
            groundX2 = windowWidth;

        if (!movingObjects.isEmpty()) {
            MovingObject* frontObject = movingObjects.front();
            frontObject->Update();

            if (frontObject->GetRect().x <= -frontObject->GetRect().width) {
                movingObjects.pop_front();  // Remove the object that left the screen

                if (movingObjects.isEmpty() || movingObjects.back()->GetRect().x < windowWidth - 200) {
                    GenerateNextMovingObject(movingObjects, cactus1, cactus2, cactus3, appleTex, shieldTex);
                }
            }

            if (frontObject->IsCollision(dino)) {
                if (dynamic_cast<Trap*>(frontObject)) {
                    dino->Decrease(50);
                } else if (dynamic_cast<Apple*>(frontObject)) {
                    dino->Increase(50);
                } else if (dynamic_cast<Shield*>(frontObject)) {
                    dino->ActivateInvincibility(10.0f);
                }
                movingObjects.pop_front();  // Remove object after handling collision
            }
        } else {
            GenerateNextMovingObject(movingObjects, cactus1, cactus2, cactus3, appleTex, shieldTex);
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

void DrawGame(Dino* dino, Deque<MovingObject*>& movingObjects, float groundX1, float groundX2, Texture2D groundTexture, Texture2D stopButton) {
    BeginDrawing();
    ClearBackground(WHITE);

    DrawTextureEx(groundTexture, {groundX1, windowHeight - groundTexture.height}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(groundTexture, {groundX2, windowHeight - groundTexture.height}, 0.0f, 1.0f, WHITE);

    if (!movingObjects.isEmpty()) {
        MovingObject* frontObject = movingObjects.front();
        frontObject->Draw();
    }

    dino->Draw();
    dino->DrawHitbox(false); // Adjust this if needed to display hitboxes

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
    Texture2D cactus1 = LoadTexture("Graphics/Cactus1.png");
    Texture2D cactus2 = LoadTexture("Graphics/Cactus2.png");
    Texture2D cactus3 = LoadTexture("Graphics/Cactus3.png");
    Texture2D appleTex = LoadTexture("Graphics/Apple.png");
    Texture2D shieldTex = LoadTexture("Graphics/Shield.png");

    Dino* dino = new Dino();

    float groundX1 = 0;
    float groundX2 = windowWidth;
    bool isPaused = false;

    Deque<MovingObject*> movingObjects;
    GenerateInitialMovingObjects(movingObjects, cactus1, cactus2, cactus3, appleTex, shieldTex);

    while (!WindowShouldClose()) {
        if (!dino->isDead()) {
            UpdateGame(dino, movingObjects, groundX1, groundX2, isPaused, stopButton, cactus1, cactus2, cactus3, appleTex, shieldTex);
            DrawGame(dino, movingObjects, groundX1, groundX2, groundTexture, stopButton);
        } else {
            break;
        }
    }

    Cleanup(groundTexture, stopButton, dino);

    return 0;
}
