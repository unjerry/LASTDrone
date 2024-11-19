/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <ball_object.h>

BallObject::BallObject()
    : GameObject(), Radius(12.5f), Stuck(true) {}

BallObject::BallObject(glm::vec3 pos, float radius,b2WorldId worldid, glm::vec2 velocity, Texture2D sprite)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite,worldid, glm::vec3(1.0f), velocity), Radius(radius), Stuck(true) {}

glm::vec2 BallObject::Move(float dt, float window_width)
{
    // if not stuck to player board
    if (!this->Stuck)
    {
        // move the ball
        this->Position += glm::vec3(this->Velocity, 0.0f) * dt;
        // then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= -window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = -window_width;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y + this->Size.y >= 1.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 1.0f - this->Size.y;
        }
    }
    return this->Position;
}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObject::Reset(glm::vec3 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}