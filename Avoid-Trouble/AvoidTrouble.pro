#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

QT          +=  core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      =   AvoidTrouble
TEMPLATE    =   app

SOURCES     +=  main.cpp\
                player.cpp\
                obstacle.cpp\
                avoidtrouble.cpp

HEADERS     +=  defines.h\
                player.h\
                obstacle.h\
                avoidtrouble.h

FORMS       +=  avoidtrouble.ui

RESOURCES   +=  res.qrc

RC_ICONS    =   images/icon.ico
