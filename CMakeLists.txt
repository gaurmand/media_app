cmake_minimum_required(VERSION 3.16)
project(media_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_AUTOMOC ON)

include_directories("include")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(media_app
    main.cpp
    ui/mainwindow.cpp
    ui/mediaview.cpp
    ui/medialistview.cpp
    vlcwrapper/instance.cpp
    vlcwrapper/mediaplayer.cpp
    vlcwrapper/medialist.cpp
)

target_link_libraries(media_app PRIVATE Qt6::Core Qt6::Widgets vlc)
