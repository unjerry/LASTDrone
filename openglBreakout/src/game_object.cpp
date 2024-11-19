/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game_object.h"

GameObject::GameObject() : Position(0.0f, 0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) {}

GameObject::GameObject(glm::vec3 pos, glm::vec2 size, Texture2D sprite, b2WorldId worldid, glm::vec3 color, glm::vec2 velocity) : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false), wdid(worldid)
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2({pos.x, pos.y});
    bodyId = b2CreateBody(wdid, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void GameObject::Draw(SpriteRenderer &renderer)
{
    for (size_t k = 0; k <= 2; k++)
    {
        renderer.DrawSprite(this->Sprite, glm::vec3(this->Position.x, this->Position.y, -.05f * (2 - k)), this->Size, this->Rotation, this->Color);
    }
}