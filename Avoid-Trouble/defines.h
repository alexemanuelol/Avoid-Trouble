/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DEFINES_H
#define DEFINES_H

/* application */
#define APP_NAME						"Avoid Trouble"
#define WINDOW_WIDTH                    800
#define WINDOW_HEIGHT                   600
#define UPDATE_FREQUENCY_MS				16//2
#define INITIAL_OBSTACLES_AMOUNT        1
#define MAX_VELOCITY                    10
#define MIN_VELOCITY                    1

/* player */
#define PLAYER_WIDTH                    20
#define PLAYER_HEIGHT                   20
#define PLAYER_VELOCITY                 4//765

/* victory door */
#define VICTORY_DOOR_WIDTH              10
#define VICTORY_DOOR_HEIGHT             80

/* safezone */
#define SAFE_ZONE_WIDTH                 60
#define SAFE_ZONE_HEIGHT                WINDOW_HEIGHT

/* obstacle */
#define OBSTACLE_WIDTH                  10
#define OBSTACLE_HEIGHT                 10
#define OBSTACLE_MAX_VEL                MAX_VELOCITY
#define OBSTACLE_MIN_VEL                MIN_VELOCITY
#define OBSTACLE_CHANGE_DIR_DELAY       15

#endif // DEFINES_H
