#pragma once
#include <raylib.h>

#define PLAYER_WALKING_SPEED .5
#define PLAYER_RUNNING_SPEED .7
#define PLAYER_GRAVITY .06
#define PLAYER_FRICTION .32
#define PLAYER_JUMP_FORCE 1.5
#define PLAYER_JUMP_FOREGIVENESS 3

#define MAX_CAMERA_DISTANCE 128

/** Represents the player state */
enum PlayerState: int {
    Walking,
    Climbing,
};

// Avoid circular inclusion
class World;

/** Represetns the player */
class Player {
public:
    Player();
    ~Player();

    // The current player state
    PlayerState state;

    // The player transform
    Vector2 position;
    // The players velocity
    Vector2 velocity;

    // The flag for if the player can jump
    bool can_jump = false;
    // The flag for if the player is flipped
    bool flipped = false;

    // The player texture
    Texture2D texture;
    // The jump sfx
    Sound jump_sfx;
    // The death sfx
    Sound death_sfx;

    /** Load the player */
    void Load();
    /** Unload the player */
    void Unload();

    /** Update the player */
    void Update(World* world);
    /** Draw the player */
    void Draw(World* world);
private:
    /** Handle the player input */
    void HandleInput(World* world);
    /** Handle the player movement */
    void HandleMovement(World* world);
    /** Handle the player input */
    void HandleCollision(World* world);
    /** Handle the player animation */
    void HandleAnimation();
};