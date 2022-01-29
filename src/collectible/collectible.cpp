#include "collectible.hpp"
#include <world/world.hpp>
#include <iostream>
#include <cmath>

Collectible::Collectible(Vector2 position, CollectibleType type) : position(position), type(type), collected(false) {}

Collectible::~Collectible() {}

/** Load the collectible */
void Collectible::Load() {
    switch (type) {
        case CollectibleType::Audio:
            texture = LoadTexture("assets/sprites/audio.png");
            break;
        case CollectibleType::Code:
            texture = LoadTexture("assets/sprites/code.png");
            break;
        case CollectibleType::Sprites:
            texture = LoadTexture("assets/sprites/sprites.png");
            break;
        default:
            break;
    }

    collect_sfx = LoadSound("assets/audio/pickup.wav");
}

/** Unload the collectible */
void Collectible::Unload() {
    UnloadTexture(texture);
    UnloadSound(collect_sfx);
}

/** Check if the player is near and collect the collectible */
void Collectible::CheckForPlayer(World* world) {
    if (collected) 
        return;

    auto collider = (Rectangle) {position.x, position.y, COLLIDER_SIZE, COLLIDER_SIZE};
    auto player_collider = (Rectangle) {world->player.position.x, world->player.position.y, 12, 11};
    // Check for collision
    if (CheckCollisionRecs(collider, player_collider)) {
        collected = true;
        PlaySound(collect_sfx);
    }
}

/** Draw the collectible */
void Collectible::Draw(int framecount) {
    if (collected)
        return;

    DrawTexture(texture, (int)position.x, (int)position.y + sin(framecount/10), WHITE);
}
