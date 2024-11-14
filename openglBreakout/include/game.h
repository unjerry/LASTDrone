/*******************************************************************
** This code is part of LASTDrone.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "game_level.h"
namespace Game
{
    // Represents the current state of the game
    enum GameState
    {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN
    };
    // Represents the four possible (collision) directions
    enum Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    // Defines a Collision typedef that represents collision data
    typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>
    // Initial size of the player paddle
    const glm::vec2 PLAYER_SIZE(0.73f, 0.125f);
    // Initial velocity of the player paddle
    const float PLAYER_VELOCITY(1.0f);
    // Initial velocity of the Ball
    const glm::vec2 INITIAL_BALL_VELOCITY(0.5f, 0.5f);
    // Radius of the ball object
    const float BALL_RADIUS = 0.125f / 2;
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
        void DoCollisions();
        // reset
        void ResetLevel();
        void ResetPlayer();
    };
}
#endif
