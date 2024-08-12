//
// Created by alex on 4/11/23.
//

#include "Dino.h"

Dino::Dino(raylib::Vector2 position){
    this->position = position;

    runningSprites[0] = idleSprite;
    runningSprites[1] = new raylib::Texture("../assets/images/dino1.png");
    runningSprites[2] = idleSprite;
    runningSprites[3] = new raylib::Texture("../assets/images/dino2.png");

    animTimer = animDelay;
}

Dino::~Dino(){
    delete idleSprite;
    delete runningSprites[1];
    delete runningSprites[3];
}

void Dino::render(){
    if(alive){
        runningSprites[currentFrame]->Draw(position, 0, scale);
    } else {
        deadSprite.Draw(position, 0, scale);
    }
}

void Dino::update(float dt) {

    if(!alive)
        return;

    if(IsKeyPressed(KEY_SPACE) && onGround){
        yVel = -jumpForce;
        onGround = false;
    }

    if(!onGround)
        yVel += gravity * dt;
    position.y += yVel * dt;

    if(position.y >= groundHeight){
        position.y = groundHeight;
        onGround = true;
    }

    // Update animation
    if(animTimer <= 0){
        animTimer = animDelay;
        currentFrame++;
        if(currentFrame >= 4)
            currentFrame = 0;
    } else {
        animTimer -= dt;
    }

}

Vector2 Dino::getPosition() {
    return position;
}

Vector2 Dino::getSize() {
    return size;
}

float Dino::getScale() {
    return scale;
}

bool Dino::isAlive() {
    return alive;
}

void Dino::setAlive(bool alive) {
    this->alive = alive;
}