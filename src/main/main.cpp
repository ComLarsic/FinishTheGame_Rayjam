//! A small game written in raylib for the raylib 5k gamejam.
//! Written by ComLarsic.
#include <iostream>
#include <memory>
#include <cmath>
#include <raylib.h>

#include <player/player.hpp>
#include <world/world.hpp>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// Bad form i know, but it was a quick fix.
static World* world;
static GameState state;

/** The game loop */
void GameLoop() {
    // Match the gamestate
    switch (state) {
        case GameState::Titlescreen:
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Finish the game!", 450 - 375, 130 - 32, 96, WHITE);
                DrawText("-- Press space --", 450 - 150, 130 + 96, 32, WHITE);
                DrawText("You are trying to finish your jam game in time for the deadline, \nbut you dropped the assets! \nYou have 30 seconds to search the area and find the assets in ime for submissions! \nGoal: collect the sprites, audio and code. Then return to the house.", 450 - 425, 300, 20, WHITE);
                if (IsKeyPressed(KEY_SPACE)) {
                    state = GameState::Gameplay;
                }
            EndDrawing();
            break;
        case GameState::Gameplay:
            // Update the world
            world->Update(state);
            // Draw usiong the camera
            BeginMode2D(world->camera.internal);
                ClearBackground((Color) {0, 0, 0, 255});
                world->Draw(false);
            EndMode2D();
            // Draw to the screen
            BeginDrawing();
                world->timer.Draw();
            EndDrawing();
            break;
        case GameState::GameLost:
            // Restart the game if enter is pressed
            if (IsKeyPressed(KEY_ENTER)) {
                delete world;
                world = new World();
                state = GameState::Gameplay;
            }
        
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Times up", 450 - 220, 130 - 32, 96, WHITE);
                DrawText("The submissions have ended and you are unable to upload your game. \nBetter start messaging the jam organizers!", 450 - 400, 250, 24, WHITE);
                DrawText("Press return to restart", 450 - 205, 130 + 64, 32, WHITE);
            EndDrawing();
            break;
        case GameState::GameOver:
            // Restart the game if enter is pressed
            if (IsKeyPressed(KEY_ENTER)) {
                delete world;
                world = new World();
                state = GameState::Gameplay;
            }
        
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("You died", 450 - 200, 130 - 32, 96, WHITE);
                DrawText("You fell into the endless abyss that resides outside of your house, \nyou die and are never able to finish your game. :(", 450 - 400, 250, 24, WHITE);
                DrawText("Press return to restart", 450 - 205, 130 + 64, 32, WHITE);
            EndDrawing();
            break;
        case GameState::GameWon:
            // Restart the game if enter is pressed
            if (IsKeyPressed(KEY_ENTER)) {
                delete world;
                world = new World();
                state = GameState::Gameplay;
            }
        
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("You won!", 450 - 200, 130 - 32, 96, WHITE);
                DrawText("Press return to restart", 450 - 205, 130 + 64, 32, WHITE);
                DrawText("Well done! You finished the game in time! \nNow sit back and pat yourself on the back for a job well done.", 450 - 400, 250, 24, WHITE);
            EndDrawing();
            break;
    }
}

int main() {
    // Greet the rayjammers looking in the console
    std::cout << "Hello, RayJammers!" << std::endl;

    // Initialize the window
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(900, 500, "Finish your game!");
    InitAudioDevice();

    // Set the game state
    state = GameState::Titlescreen; 
    // Create the gameworld
    world = new World();

    // Setup gameloop for specific platforms
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(GameLoop, 60, 1);
    #else
        SetTargetFPS(60);
    
        // The main gameloop
        while (!WindowShouldClose()) {
            GameLoop();
        }
    #endif

    delete world;
    CloseAudioDevice();
    CloseWindow();
    return 0;
}