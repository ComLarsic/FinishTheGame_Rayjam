#pragma once
#include <vector>
#include <raylib.h>
#include <player/player.hpp>
#include <gamecamera/gamecamera.hpp>
#include <collectible/collectible.hpp>
#include "timer.hpp"

/** Represents the game state */
enum GameState: int {
    Titlescreen = 0,
    Gameplay,
    GameLost,
    GameOver,
    GameWon,
};

/** Represents the gameworld */
class World {
public:
    World();
    ~World();

    // The worlds camera
    GameCamera camera;
    // The game timer
    Timer timer;
    // The player in the world
    Player player;
    // The colliders in the world
    std::vector<Rectangle> colliders;
    // The ladders in the world
    std::vector<Rectangle> ladders;
    // The collectibles in the world
    std::vector<Collectible> collectibles;
    // The spot the player returns to to return the collectables
    Rectangle return_spot;
    
    // The texture in the world
    Texture2D texture;
    // The death sfx
    Sound death_sfx;
    // The win sfx
    Sound win_sfx;

    // The framecount
    int framecount = 0;

    /** Update the world */
    void Update(GameState& state);
    /** Draw the world */
    void Draw(const bool debug);
};