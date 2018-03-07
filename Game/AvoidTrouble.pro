###############################################################################
#                                                                             #
# Author: Alexander Emanuelsson                                               #
#                                                                             #
# Project: https://github.com/alexemanuelol/Avoid-Trouble-Game.git            #
#                                                                             #
###############################################################################

QT          +=  core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      =   AvoidTrouble
TEMPLATE    =   app

SOURCES     +=  main.cpp\
                player.cpp\
                obstacle.cpp\
                safezone.cpp \
                avoidtrouble.cpp

HEADERS     +=  defines.h\
                player.h\
                obstacle.h\
                safezone.h \
                avoidtrouble.h

FORMS       +=  avoidtrouble.ui

RESOURCES   +=  res.qrc

RC_ICONS    =   images/icon.ico
