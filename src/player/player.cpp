#include "player.hpp"
#include <iostream>
#include <raymath.h>
#include <world/world.hpp>

Player::Player() {
    position = {0, 0};
    velocity = {0, 0};
}

Player::~Player() {}

/** Load the player */
void Player::Load() {
    texture = LoadTexture("assets/sprites/player.png");
    jump_sfx = LoadSound("assets/audio/jump.wav");
}

/** Unload the player */
void Player::Unload() {
    UnloadTexture(texture);
    UnloadSound(jump_sfx);
}

/** Handle player input */
void Player::HandleInput(World* world) {
    // Get the movement axis
    float xmove = -(float)IsKeyDown(KEY_A) + (float)IsKeyDown(KEY_D);
    float ymove = -(float)IsKeyDown(KEY_W);
    // Check if the player is running
    int is_running = IsKeyDown(KEY_LEFT_SHIFT);
    
    switch (state) {
        case PlayerState::Walking:
            // Handle player jumping
            if (world->player.can_jump && IsKeyPressed(KEY_SPACE)) {
                world->player.velocity.y -= PLAYER_JUMP_FORCE;
                world->player.can_jump = false;
                PlaySound(jump_sfx);
            }
            world->player.velocity.x += xmove * (is_running ? PLAYER_RUNNING_SPEED : PLAYER_WALKING_SPEED);
            break;
        case PlayerState::Climbing:
            if (world->player.velocity.y > -PLAYER_WALKING_SPEED) {
                world->player.velocity.y += ymove * PLAYER_WALKING_SPEED;
            }
            // Handle player jumping
            if (world->player.can_jump && IsKeyPressed(KEY_SPACE)) {
                world->player.velocity.y -= PLAYER_JUMP_FORCE;
                world->player.can_jump = false;
                PlaySound(jump_sfx);
            }
            world->player.velocity.x += xmove * (is_running ? PLAYER_RUNNING_SPEED : PLAYER_WALKING_SPEED);
            break;
    }
}

/** Handle player collision */
void Player::HandleCollision(World* world) {
    // Create the player collider
    auto player_next_x = (Rectangle) {world->player.position.x + world->player.velocity.x, world->player.position.y, 8, 8};
    auto player_next_y = (Rectangle) {world->player.position.x, world->player.position.y + world->player.velocity.y, 8, 8};
    // Check for collision with each collider
    auto is_on_floor = false;
    auto can_wall_jump = false;
    for (auto collider : world->colliders) {
        if (CheckCollisionRecs(player_next_x, collider)) {
            world->player.velocity.x = 0.0;
        }
        if (CheckCollisionRecs(player_next_y, collider)) {
            world->player.velocity.y = 0.0;
        }
        // Check if the player is on the floor
        auto player_down = (Rectangle) {world->player.position.x, world->player.position.y + PLAYER_JUMP_FOREGIVENESS, 8, 8};
        if (CheckCollisionRecs(player_down, collider)) {
            is_on_floor = true;
        }
    }
    world->player.can_jump = is_on_floor;

    // Check if the player is near a ladder
    auto player_collider = (Rectangle) {world->player.position.x, world->player.position.y, 8, 8};
    state = PlayerState::Walking;
    for (auto ladder : world->ladders) {
        if (CheckCollisionRecs(player_collider, ladder)) {
            state = PlayerState::Climbing;
        }
    }
}

/** Apply the players velocity */
void Player::HandleMovement(World* world) {
    // Apply the velocity
    world->player.position = Vector2Add(world->player.position, world->player.velocity);
    // Apply the friction
    world->player.velocity.x = Lerp(world->player.velocity.x, 0.0, PLAYER_FRICTION);
}

/** Update the player */
void Player::Update(World* world) {
    HandleInput(world);
    // Apply the gravity
    velocity.y += PLAYER_GRAVITY;
    HandleCollision(world);
    HandleMovement(world);
}

/** Handle the player animation */
void Player::HandleAnimation() {
    if (velocity.x > 0.0) {
        flipped = false;
    } 
    if (velocity.x < 0.0) {
        flipped = true;
    }
}

/** Draw the player */
void Player::Draw(World* world) {
    HandleAnimation();
    DrawTexturePro(texture, (Rectangle) {
            0.0,
            0.0,
            (float)8.0 * (flipped ? -1.0f : 1.0f),
            8.0,
        }, (Rectangle) {
            world->player.position.x, 
            world->player.position.y,
            8.0,
            8.0,
        }, {0.0},
        0.0,
        WHITE
    );
}