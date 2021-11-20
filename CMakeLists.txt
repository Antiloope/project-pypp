cmake_minimum_required(VERSION 3.10)

set(SourcePath "src/back/")
set(Version "0.1.0")

# set the project name
project(project-pypp VERSION ${Version})

# source list
list(APPEND SourcesList ${SourcePath}main.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(project-pypp ${SourcesList}
        src/back/utils/log.h
        src/back/utils/log.cpp
        src/back/utils/exception/exception.cpp
        src/back/utils/exception/exception.h
        src/back/player/jack_client.cpp
        src/back/player/jack_client.h
        src/back/player/player.cpp
        src/back/player/player.h src/back/player/effects_list.cpp src/back/player/effects_list.h src/back/player/jack_callbacks.h src/back/utils/exception/log_exception.cpp src/back/utils/exception/log_exception.h src/back/connector/audio_message_queue.cpp src/back/connector/audio_message_queue.h)

# configure version header file
configure_file(
    ${SourcePath}main.h.in
    ${SourcePath}main.h
    )


target_include_directories(
    project-pypp PUBLIC
    "${PROJECT_BINARY_DIR}"
    "/home/antiloope/Documents/projects/project-pypp/include"
    )
TARGET_LINK_LIBRARIES(project-pypp PUBLIC -ljack -g -lpthread)

install(TARGETS project-pypp DESTINATION bin)
install(DIRECTORY src/front DESTINATION src)
