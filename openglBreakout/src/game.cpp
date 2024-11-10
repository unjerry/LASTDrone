/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include <learnopengl/filesystem.h>

// Game-related State data
SpriteRenderer *Renderer;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/sprite.vs").c_str(), FileSystem::getPath("resources/shaders/sprite.fs").c_str(), nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(this->Width) / static_cast<float>(this->Height), 0.1f, 100.0f);
    // glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/container.jpg").c_str(), false, "face");
}

void Game::Update(float dt)
{
}

void Game::ProcessInput(float dt)
{
}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}