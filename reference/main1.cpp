#include <iostream>
#include "Window.hpp"
#include "C:\\raylib\\raylib\\src\\raylib.h"
#include "Game.h"
#include "Ground.h"
#include "Cactus.h"

Game::Game() {
    window = new raylib::Window(1280, 720, "Dino");
    dino = new Dino(Vector2(150, 460));
    ground1 = new Ground(Vector2(0, dino->getPosition().y + dino->getSize().y - 12), this);
    ground2 = new Ground(Vector2(ground1->getPosition().x + ground1->getSize().x, ground1->getPosition().y), this);

    obstacleSpawnTimer = obstacleSpawnRate;

    window->SetTargetFPS(60);
}

Game::~Game() {
    delete dino;
    delete ground1;
    delete ground2;
    delete window;
}

void Game::loop() {

    while (!window->ShouldClose()) {

        float dt = GetFrameTime();
        dino->update(dt);
        ground1->update(dt);
        ground2->update(dt);

        if (ground1->getPosition().x <= -ground1->getSize().x) {
            ground1->setPosition(Vector2(ground2->getPosition().x + ground2->getSize().x, ground1->getPosition().y));
        } else if (ground2->getPosition().x <= -ground2->getSize().x) {
            ground2->setPosition(
                    Vector2(ground1->getPosition().x + ground1->getSize().x - 50, ground2->getPosition().y));
        }

        if (dino->isAlive()) {
            if (obstacleSpawnTimer <= 0) {
                auto cactus = new Cactus(raylib::Vector2(1280, ground1->getPosition().y - 25), this);
                obstacles.push_back(cactus);
                obstacleSpawnTimer = obstacleSpawnRate;
            } else {
                obstacleSpawnTimer -= dt;
            }
        }

        for (auto &obstacle: obstacles) {
            obstacle->update(dt);
        }

        if (dino->isAlive()) {

            score += 20 * dt;

            if ((int) score % 100 == 0 && (int) score != 0) {
                shouldFlash = true;
                scoreString = std::to_string((int) score);
            }
            if (shouldFlash) {
                scoreHoldTimer -= dt;
                if (scoreHoldTimer > 0) {
                    scoreHoldTimer -= dt;
                } else {
                    scoreHoldTimer = flashRate;
                    shouldFlash = false;
                }

                if (flashTimer > 0) {
                    flashTimer -= dt;
                } else {
                    flashTimer = flashDuration;
                    whiteScore = !whiteScore;
                    if (whiteScore)
                        scoreColor = RAYWHITE;
                    else
                        scoreColor = BLACK;
                }
            } else {
                scoreString = std::to_string((int) score);
                if (whiteScore) {
                    whiteScore =  false;
                    scoreColor = BLACK;
                }
            }

        } else {
            scoreString = std::to_string((int) score);
            if(whiteScore){
                whiteScore = false;
                scoreColor = BLACK;
            }
        }

        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);
        dino->render();
        ground1->render();
        ground2->render();

        for (auto &obstacle: obstacles) {
            obstacle->render();
        }


        DrawText(scoreString.c_str(), 10, 10, 24, scoreColor);

        window->EndDrawing();
    }

}

int main() {

    Game *game = new Game();
    game->loop();

    delete game;
    return 0;
}
