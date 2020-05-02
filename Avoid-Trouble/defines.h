#ifndef DEFINES_H
#define DEFINES_H

/* application */
#define APP_NAME						"Avoid Trouble"
#define WINDOW_WIDTH                    800
#define WINDOW_HEIGHT                   600
#define UPDATE_FREQUENCY_MS				16
#define INITIAL_OBSTACLES_AMOUNT        1

/* player */
#define PLAYER_WIDTH                    20
#define PLAYER_HEIGHT                   20
#define PLAYER_VELOCITY                 4 //765

/* victory door */
#define VICTORY_DOOR_WIDTH              10
#define VICTORY_DOOR_HEIGHT             80

/* safezone */
#define SAFE_ZONE_WIDTH                 60
#define SAFE_ZONE_HEIGHT                WINDOW_HEIGHT

/* obstacle */
#define OBSTACLE_WIDTH                  10
#define OBSTACLE_HEIGHT                 10
#define OBSTACLE_MAX_VEL                5
#define OBSTACLE_MIN_VEL                1
#define OBSTACLE_CHANGE_DIR_DELAY       15

#endif // DEFINES_H
