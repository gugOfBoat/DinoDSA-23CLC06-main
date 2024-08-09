//
// Created by alex on 4/11/23.
//

#ifndef DINO_DINO_H
#define DINO_DINO_H
#include <raylib-cpp.hpp>

class Dino {
private:
    float scale = 1.5;
    raylib::Vector2 size = Vector2(44 * scale,47 * scale);
    raylib::Vector2 position;
    raylib::Texture* idleSprite = new raylib::Texture("../assets/images/dino0.png");
    raylib::Texture* runningSprites[4];
    raylib::Texture deadSprite = raylib::Texture("../assets/images/dead.png");

    int currentFrame = 0;
    bool alive = true;
    float animDelay = 0.1;
    float animTimer;

    float yVel = 0;
    float gravity = 5500;
    float jumpForce = 1600;

    float groundHeight = 460;
    bool onGround = true;
public:
    explicit Dino(raylib::Vector2 position);
    ~Dino();

    void render();
    void update(float dt);

    Vector2 getPosition();
    Vector2 getSize();
    float getScale();

    bool isAlive();
    void setAlive(bool alive);
};


#endif //DINO_DINO_H
