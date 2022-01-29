#pragma once
#include <raylib.h>

#define COLLIDER_SIZE 10

/** Avoid circular inclusion */
class World;

/** The type of collectible */
enum CollectibleType: int {
    Audio,
    Sprites,
    Code,
};

/** Represents the collectible */
class Collectible {
public:
    Collectible(Vector2 position, CollectibleType type);
    ~Collectible();

    // The collectible type
    CollectibleType type;
    // The position of the collectible
    Vector2 position;
    // The flag for if the collectible is collected
    bool collected;
    // The size multiplier (for animation)
    float size = 1;

    // The collectables texture
    Texture2D texture;
    // The collect sfx
    Sound collect_sfx;

    /** Load the collectible */
    void Load();
    /** Unload the collectible */
    void Unload();

    /** Check if the player is near and collect the collectible */
    void CheckForPlayer(World* world);
    /** Draw the collectible */
    void Draw(int framecount);
};