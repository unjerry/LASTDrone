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
#include "game_object.h"
#include <learnopengl/filesystem.h>

extern GladGLContext *gl;

// Game-related State data
SpriteRenderer *Renderer;
GameObject *Player;

glm::vec2 cameraPos(0.0f);

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
    aspect_ratio = static_cast<float>(Width) / static_cast<float>(Height);
}

Game::~Game()
{
    delete Renderer;
    delete Player;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/sprite.vs").c_str(), FileSystem::getPath("resources/shaders/sprite.fs").c_str(), nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspect_ratio, 0.1f, 100.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/background.jpg").c_str(), false, "background");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), true, "face");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/block.png").c_str(), false, "block");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/block_solid.png").c_str(), false, "block_solid");
    ResourceManager::LoadTexture(FileSystem::getPath("resources/textures/paddle.png").c_str(), true, "paddle");
    // load levels
    GameLevel one;
    one.Load(FileSystem::getPath("resources/levels/one.lvl").c_str(), 2.0f, 1.0f);
    GameLevel two;
    two.Load(FileSystem::getPath("resources/levels/two.lvl").c_str(), 2.0f, 1.0f);
    GameLevel three;
    three.Load(FileSystem::getPath("resources/levels/three.lvl").c_str(), 2.0f, 1.0f);
    GameLevel four;
    four.Load(FileSystem::getPath("resources/levels/four.lvl").c_str(), 2.0f, 1.0f);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;
    // configure game objects
    glm::vec3 playerPos = glm::vec3(0.0, -0.85, 0);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(float dt)
{
    glm::mat4 view = glm::lookAt(glm::vec3(cameraPos, 1.732f), glm::vec3(cameraPos, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    ResourceManager::GetShader("sprite").SetMatrix4("view", view);
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= -1.0f)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= 1.0f - Player->Size.x)
                Player->Position.x += velocity;
        }

        if (this->Keys[GLFW_KEY_LEFT])
        {
            cameraPos.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_RIGHT])
        {
            cameraPos.x += velocity;
        }
        if (this->Keys[GLFW_KEY_DOWN])
        {
            cameraPos.y -= velocity;
        }
        if (this->Keys[GLFW_KEY_UP])
        {
            cameraPos.y += velocity;
        }
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        gl->Disable(GL_DEPTH_TEST);
        // draw background
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec3(-aspect_ratio, -1.0f, 0.0f) + glm::vec3(cameraPos, 0.0f), glm::vec2(aspect_ratio * 2.0f, 2.0f), 0.0f);
        // draw level
        gl->Enable(GL_DEPTH_TEST);
        this->Levels[this->Level].Draw(*Renderer);
        // draw player
        Player->Draw(*Renderer);
    }
}
void Game::changeSize(unsigned int width, unsigned int height)
{
    Width = width;
    Height = height;
    aspect_ratio = static_cast<float>(Width) / static_cast<float>(Height);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspect_ratio, 0.1f, 100.0f);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
}