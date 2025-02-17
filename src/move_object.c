#include "../inc/gamelib.h"
#include "../inc/bee.h"
#include "../inc/coin.h"
#include "../inc/gameobject.h"
#include "../inc/handle_events.h"

static void move_bee(const Uint8 *state) {
    t_bee *bee = get_bee();
    double radians = bee->object->angle * M_PI / 180.0;

    static Uint32 staminaTimer = 0;

    if (!state[SDL_SCANCODE_N] && bee->stamina < 100) {
        bee->stamina += 0.05;
    }

    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        bee->object->angle -= bee->movement.rotationSpeed;
    }
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        bee->object->angle += bee->movement.rotationSpeed;
    }

    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
        double currentAcceleration = bee->movement.acceleration;
        if (state[SDL_SCANCODE_N] && bee->stamina > 0) {
            if (!bee->is_boosting) {
                bee->is_boosting = true;
                staminaTimer = SDL_GetTicks();
            }

            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - staminaTimer >= 3000) {
                bee->stamina = 0;
                bee->is_boosting = false;
            }
            else {
                bee->stamina -= 0.6;
            }
            currentAcceleration *= bee->movement.boostFactor;
        }
        else {
            bee->is_boosting = false;
        }
        double thrustX = currentAcceleration * sin(radians);
        double thrustY = -currentAcceleration * cos(radians);

        bee->movement.speedX += thrustX;
        bee->movement.speedY += thrustY;
    }
    else {
        bee->is_boosting = false;
    }
    double currentSpeed = sqrt(bee->movement.speedX * bee->movement.speedX +
                               bee->movement.speedY * bee->movement.speedY);
    double speedLimit = (state[SDL_SCANCODE_N] && bee->stamina > 0)
                            ? bee->movement.maxSpeed * bee->movement.boostFactor
                            : bee->movement.maxSpeed;

    if (currentSpeed > speedLimit) {
        bee->movement.speedX =
            (bee->movement.speedX / currentSpeed) * speedLimit;
        bee->movement.speedY =
            (bee->movement.speedY / currentSpeed) * speedLimit;
    }

    if (currentSpeed > 0.01) {
        bee->movement.speedX *= 0.995;
        bee->movement.speedY *= 0.995;
    }
    else {
        bee->movement.speedX = 0;
        bee->movement.speedY = 0;
    }

    bee->object->x += bee->movement.speedX;
    bee->object->y += bee->movement.speedY;
}

void moveObjects(const Uint8 *state) {
    t_gameobject *objects = objects_get();

    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (!objects[i].is_active) {
            continue;
        }
        else if (objects[i].type == GAMEOBJECT_BEE) {
            move_bee(state);
        }
        else if (objects[i].type == GAMEOBJECT_SPRINT ||
                 objects[i].type == GAMEOBJECT_TASK ||
                 objects[i].type == GAMEOBJECT_STAR) {
            double radians = objects[i].angle * M_PI / 180.0;
            objects[i].x += objects[i].speed * sin(radians) *
                            get_event_state()->enemy_speed_multiplier;
            objects[i].y -= objects[i].speed * cos(radians) *
                            get_event_state()->enemy_speed_multiplier;
        }
        else {
            double radians = objects[i].angle * M_PI / 180.0;
            objects[i].x += objects[i].speed * sin(radians);
            objects[i].y -= objects[i].speed * cos(radians);
        }
        wrapCoordinates(&objects[i]);
    }
}
