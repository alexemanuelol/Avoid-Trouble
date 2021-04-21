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
#define APP_WIDTH                       800
#define APP_HEIGHT                      600

/* General */
#define MAX_SPEED                       20
#define MIN_SPEED                       0
#define START_OBS_NBR                   1
#define UPD_FREQ_MS				        1

/* victory door */
#define VICTORY_DOOR_WIDTH              10
#define VICTORY_DOOR_HEIGHT             80

/* safezone */
#define SAFE_ZONE_WIDTH                 60
#define SAFE_ZONE_HEIGHT                APP_HEIGHT

/* obstacle */
#define OBS_WIDTH                       10
#define OBS_HEIGHT                      10
#define OBS_MAX_SPEED                   MAX_SPEED
#define OBS_MIN_SPEED                   MIN_SPEED
#define OBS_CHANGE_DIR_DELAY            15

/* player */
#define PLAYER_WIDTH                    20
#define PLAYER_HEIGHT                   20
#define PLAYER_SPEED                    18
#define PLAYER_STUCK                    1000
#define PLAYER_START_POS_X              ((SAFE_ZONE_WIDTH/2) - (PLAYER_WIDTH/2))
#define PLAYER_START_POS_Y              ((APP_HEIGHT/2) - (PLAYER_HEIGHT/2))

#endif /* DEFINES_H */
