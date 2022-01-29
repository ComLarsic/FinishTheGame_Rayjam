#include "world.hpp"
#include <iostream>
#include <raymath.h>
#include <player/player.hpp>

/** Create the gameworld */
World::World() {
    // Create the player
    player = Player();
    player.Load();
    player.position = {8.0, 16.0};

    // Create the camera
    camera = GameCamera({
        {0.0, 0.0},
        {0.0, 0.0},
        0.0,
        6.0,
    }, 0.2);

    // Create the level
    colliders = std::vector<Rectangle> {
        {8.0, 56.0, 64, 24},
        {120.0, 56.0, 56, 16},
        {208.0, 56.0, 40, 8},

        {72.0, -16.0, 56, 16},
        {0.0, -32.0, 56, 16},
        {8.0, -64.0, 40, 8},
        {80.0, -72.0, 56, 8},

        {-72.0, 56.0, 72, 16},
        {-144.0, 48.0, 32, 16},
        {-112.0, 16.0, 40, 16}, 
        {-40.0, 16.0, 40, 16},  
    };

    ladders = std::vector<Rectangle> {
        {128, -18, 8, 74},
        {0.0, -64.0, 8, 32},
        {-120.0, 16.0, 8, 32},    
    };

    // Add the collectibles
    collectibles = std::vector<Collectible> {
        Collectible({120, -82}, CollectibleType::Audio),  
        Collectible({-16, 8}, CollectibleType::Code),  
        Collectible({212, 48}, CollectibleType::Sprites),  
    };

    for (auto& collectible: collectibles) {
        collectible.Load();
    }

    // Set the return spot
    return_spot = {24.0, 46, 12, 12};

    // Set the timer
    timer = Timer();
    timer.Set(0, 30);

    texture = LoadTexture("assets/sprites/world.png");
    death_sfx = LoadSound("assets/audio/death.wav");
    win_sfx = LoadSound("assets/audio/win.wav");
}

World::~World() {
    player.Unload();

    for (auto& collectible: collectibles) {
        collectible.Unload();
    }

    UnloadTexture(texture);
    UnloadSound(death_sfx);
    UnloadSound(win_sfx);
}

/** Update the gameworld */
void World::Update(GameState& state) {
    // Update the player
    player.Update(this);
    camera.Update(this);

    // Update the camera
    //camera.target.x = Lerp(camera.target.x, player.position.x, .07);
    //camera.target.y = Lerp(camera.target.y, player.position.y, .07);
    //camera.target = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};

    // Update the collectibles
    auto all_collected = true;
    for (auto& collectible: collectibles) {
        collectible.CheckForPlayer(this);
        if (!collectible.collected) {
            all_collected = false;
        }
    }

    // CHeck if the player has won
    if (all_collected) {
        // Check if the player is in the return sport
        auto player_collider = (Rectangle) {player.position.x, player.position.y, 8, 8};
        if (CheckCollisionRecs(player_collider, return_spot) && player.can_jump) {
            state = GameState::GameWon;
            PlaySound(win_sfx);
        }
    }

    // Set to gameover if the player fell in the void
    if (player.position.y > GetScreenHeight() / camera.internal.zoom) {
        state = GameState::GameOver;
        PlaySound(death_sfx);
    }

    // Tick the timer
    timer.Tick();
    // Set to gameover if the timer runs out
    if (timer.IsOver()) {
        state = GameState::GameLost;
        PlaySound(death_sfx);
    }


    framecount++;
}

/** Render the gameworld */
void World::Draw(const bool debug) {
    DrawTexture(texture, -160, -80, WHITE);
    
    // Draw the player
    player.Draw(this);

    // Draw the collectibles
    for (auto& collectible: collectibles) {
        collectible.Draw(framecount);
    }

    // Handle debug drawing
    if (debug) {
        // Draw the colliders
        for (auto collider : colliders) {
            DrawRectangleRec(collider, (Color) {255, 0, 0, 64});
        }
        // Draw the ladders
        for (auto ladder : ladders) {
            DrawRectangleRec(ladder, (Color) {0, 0, 255, 64});
        }
        DrawRectangleRec(return_spot, (Color) {0, 255, 0, 64});
    }
}