#pragma once

typedef struct s_movement_state {
    double speedX;
    double speedY;
    double rotationSpeed;
    double acceleration;
    double maxSpeed;
    double deceleration;
    double boostFactor;
} t_movement_state;
