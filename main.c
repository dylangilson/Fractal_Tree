/*
 * Dylan Gilson
 * dylan.gilson@outlook.com
 * May 27, 2026
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600
#define MAX_DEPTH 15
#define LENGTH 160.0f
#define ANGLE 20.0f * PI / 180.0f
#define THICKNESS 20.0f
#define SCALE 0.7f

bool paused = false;

void fractal_tree(Vector2 start,  float length, float angle, float thickness, size_t current_depth, size_t render_depth) {
    if (length <= 1) {
        return;
    }

    float x_end = start.x + sinf(angle) * length;
    float y_end = start.y - cosf(angle) * length;
    Vector2 end = { x_end, y_end };

    DrawLineEx(start, end, thickness, WHITE);

    float new_length = length * SCALE;
    float new_left_angle = angle - ANGLE;
    float new_right_angle = angle + ANGLE;
    float new_thickness = thickness * SCALE;

    current_depth++;

    if (current_depth < render_depth) {
        fractal_tree(end, new_length, new_left_angle, new_thickness, current_depth, render_depth);
        fractal_tree(end, new_length, new_right_angle, new_thickness, current_depth, render_depth);
    }
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Fractal Tree");
    SetTargetFPS(60);

    size_t render_depth = 0;
    float animation_interval = 0.0f;

    while (!WindowShouldClose()) {
        // reset simulation
        if (IsKeyPressed(KEY_R)) {
            render_depth = 0;
        }

        // pause / resume simulation
        if (IsKeyPressed(KEY_SPACE)) {
            paused = !paused;
        }

        animation_interval += GetFrameTime();

        // ensure depth is incremented once per quarter second
        if (animation_interval > 0.5f) {
            animation_interval = 0.0f;

            if (render_depth < MAX_DEPTH && !paused) {
                render_depth++;
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        Vector2 start = { WIDTH / 2, HEIGHT - 50 };

        fractal_tree(start,  LENGTH, 0, THICKNESS, 0, render_depth ); // initial recursive fractal tree call

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
