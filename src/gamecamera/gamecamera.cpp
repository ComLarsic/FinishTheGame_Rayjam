#include "gamecamera.hpp"
#include <raymath.h>
#include <world/world.hpp>

GameCamera::GameCamera() {}
GameCamera::GameCamera(Camera2D camera, float speed): internal(camera), speed(speed), target({0.0, 0.0}) {}

GameCamera::~GameCamera() {}

/** Update the camera */
void GameCamera::Update(World* world) {
    internal.target.x = Lerp(internal.target.x, target.x, speed);
    internal.target.y = Lerp(internal.target.y, target.y, speed);

    if (world->player.position.x - 8 > internal.target.x + GetScreenWidth() / internal.zoom) {
        target.x += GetScreenWidth() / internal.zoom;
    }
    if (world->player.position.x + 8 < internal.target.x) {
        target.x -= GetScreenWidth() / internal.zoom;
    }

    if (world->player.can_jump || world->player.state == PlayerState::Climbing) {
        if (world->player.position.y > internal.target.y + GetScreenHeight() / internal.zoom) {
            target.y += GetScreenHeight() / internal.zoom;
        }
        if (world->player.position.y + 16 < internal.target.y) {
            target.y -= GetScreenHeight() / internal.zoom;
        }
    }
}