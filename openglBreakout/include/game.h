/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

// Represents the current state of the game
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(0.73f, 0.125f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(1.0f);

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(0.5f, 0.5f);
// Radius of the ball object
const float BALL_RADIUS = 0.125f;
  

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState State;
    bool Keys[1024];
    unsigned int Width, Height;
    float aspect_ratio;
    std::vector<GameLevel> Levels;
    unsigned int Level;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void changeSize(unsigned int, unsigned int);
};

#endif