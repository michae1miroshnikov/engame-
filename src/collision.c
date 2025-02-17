#include "../inc/collision.h"
#include "../inc/bee.h"
#include "../inc/gameobject.h"
#include "../inc/sprint.h"
#include "../inc/task.h"
#include <math.h>

static bool checkCollisionBetween(t_gameobject *obj1, t_gameobject *obj2) {
    if (!obj1->is_active || !obj2->is_active) {
        return false;
    }
    // check with hitBOXES, not hitCIRCLES
    double radius1 = sqrt(pow(obj1->width, 2) + pow(obj1->height, 2)) / 2;
    double radius2 = sqrt(pow(obj2->width, 2) + pow(obj2->height, 2)) / 2;
    double dx = (obj1->x + obj1->width / 2) - (obj2->x + obj2->width / 2);
    double dy = (obj1->y + obj1->height / 2) - (obj2->y + obj2->height / 2);
    double distance = sqrt(pow(dx, 2) + pow(dy, 2));
    double minDistance = radius1 + radius2;
    return distance < minDistance;
}

// TODO: make loop over objects only one time:
//  void checkCollisions(void) {
//      t_gameobject *objects = objects_get();
//
//      for (int i = 0; i < objects_length(); i++) {
//          if (!objects[i].is_active) {
//              continue;
//          }
//          for (int j = 0; j <objects_length(); i++) {
//              if (!objects[j].is_active) {
//                  continue;
//              }
//              if (checkCollisionBetween(&objects[i], &objects[j])) {
//                  if (i == j || objects[i].type == objects[j].type) {
//                      continue;
//                  }
//                  //collided
//              }
//          }
//      }
//  }

bool checkCollision(t_missile *missiles) {

    t_bee *bee = get_bee();
    Uint32 current_time = SDL_GetTicks();

    for (int i = 0; i < MAX_MISSILES; i++) {
        if (missiles[i].object->is_active) {
            if (current_time - missiles[i].spawn_time < 100) {
                continue;
            }
            // FIXME: there was beeCenterX and beeCenterY
            double dx = missiles[i].object->x - bee->object->x;
            double dy = missiles[i].object->y - bee->object->y;
            double distance = sqrt(dx * dx + dy * dy);

            if (distance < RECT_SIZE / 2.0) {
                missiles[i].object->is_active = false;
                return true;
            }
        }
    }
    return false;
}

bool checkCollisions(void) {
    bool collisionDetected = false;
    t_bee *bee = get_bee();
    t_sprint *sprints = sprints_get();
    Uint32 current_time = SDL_GetTicks();

    for (int i = 0; i < MAX_SPRINTS; i++) {
        if (sprints[i].object->is_active) {
            for (int j = 0; j < MAX_MISSILES; j++) {
                if (bee->missiles[j].object->is_active) {
                    if (checkCollisionBetween(sprints[i].object,
                                              bee->missiles[j].object)) {
                        SDL_Log("Hit sprint %d\n", i);
                        bee->missiles[j].object->is_active = false;
                        sprint_on_hit(&sprints[i]);
                        collisionDetected = true;
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < MAX_TASKS; i++) {
        if (tasks_get()[i].object->is_active) {
            for (int j = 0; j < MAX_MISSILES; j++) {
                if (bee->missiles[j].object->is_active) {
                    if (checkCollisionBetween(tasks_get()[i].object,
                                              bee->missiles[j].object)) {
                        SDL_Log("Hit task %zu\n", i);
                        if ((rand() % 100) < 45) {
                            generate_coin(bee->missiles[j].object);
                            SDL_Log("Coin generated\n");
                        }
                        bee->missiles[j].object->is_active = false;
                        tasks_get()[i].object->is_active = false;
                        collisionDetected = true;
                    }
                }
            }
        }
    }

    for (int i = 0; i < MAX_MISSILES; i++) {
        if (bee->missiles[i].object->is_active) {
            if (current_time - bee->missiles[i].spawn_time < 100) {
                continue;
            }

            if (checkCollisionBetween(bee->object, bee->missiles[i].object)) {
                SDL_Log("Collision bee with missile detected\n");
                bee->missiles[i].object->is_active = false;
                collisionDetected = true;
            }
        }
    }

    for (int i = 0; i < MAX_SPRINTS; i++) {
        if (sprints[i].object->is_active) {
            if (checkCollisionBetween(bee->object, sprints[i].object)) {
                SDL_Log("Collision bee with sprint detected\n");
                if (DEBUG) {
                    continue;
                }

                bee->coins -= 5;
                if (bee->coins < 0) {
                    bee->coins = 0;
                    bee->object->is_active = false;
                    collisionDetected = true;
                    return true;
                }
                sprint_on_hit(&sprints[i]);
                collisionDetected = true;
            }
        }
    }

    for (size_t i = 0; i < MAX_TASKS; i++) {
        if (tasks_get()[i].object->is_active) {
            if (checkCollisionBetween(bee->object, tasks_get()[i].object)) {
                SDL_Log("Collision bee with task detected\n");
                if (DEBUG) {
                    continue;
                }

                bee->coins -= 3;

                if (bee->coins < 0) {
                    bee->coins = 0;
                    bee->object->is_active = false;
                    collisionDetected = true;
                    return true;
                }
                tasks_get()[i].object->is_active = false;
                collisionDetected = true;
            }
        }
    }

    for (size_t i = 0; i < MAX_COINS; i++) {
        if (coins_get()[i].object->is_active) {
            for (int j = 0; j < MAX_MISSILES; j++) {
                if (checkCollisionBetween(bee->object, coins_get()[i].object)) {
                    SDL_Log("Collision bee with coin detected\n");
                    bee->coins++;
                    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                                 "Coins: %d\n",
                                 bee->coins);
                    coins_get()[i].object->is_active = false;
                    collisionDetected = true;
                }
                else if (checkCollisionBetween(bee->missiles[j].object,
                                               coins_get()[i].object)) {
                    coins_get()[i].object->angle =
                        bee->missiles[j].object->angle;
                    coins_get()[i].object->speed =
                        bee->missiles[j].object->speed;
                    bee->missiles[j].object->is_active = false;
                    collisionDetected = true;
                }
            }
        }
    }

    return collisionDetected;
}
