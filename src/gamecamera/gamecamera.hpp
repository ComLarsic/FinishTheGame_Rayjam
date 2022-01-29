#pragma once
#include <raylib.h>

/** Avoid circular inclusion */
class World;

/** Represents the gamecamera */
class GameCamera {
public:
    GameCamera();
    GameCamera(Camera2D camera, float speed);
    ~GameCamera();

    // The game target
    Vector2 target;
    // The lerping speed
    float speed = 0.0;

    // The raylib camera
    Camera2D internal;

    /** Update the camera */
    void Update(World* world);
};