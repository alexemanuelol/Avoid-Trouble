cmake_minimum_required(VERSION 3.20.1)

add_executable(avoid-trouble
    res/res.qrc
    avoidtrouble.cpp
    avoidtrouble.h
    defines.h
    main.cpp
    obstacle.cpp
    obstacle.h
    player.cpp
    player.h
)

set_target_properties(avoid-trouble PROPERTIES
    AUTOMOC TRUE
    AUTORCC TRUE
    AUTOUIC TRUE
    CXX_STANDARD 17
    OUTPUT_NAME "${EXECUTABLE_NAME}"
)

target_link_libraries(avoid-trouble
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

install(TARGETS avoid-trouble DESTINATION "${CMAKE_INSTALL_BINDIR}")
