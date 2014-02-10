# GUI/CLI common functionality goes here

find_package(RtMidi REQUIRED)

set(emulsifier-core-src
    core.cpp
    midiio.cpp
)

add_library(emulsifier-core STATIC ${emulsifier-core-src})

target_link_libraries(emulsifier-core ${RTMIDI_LIBRARIES})
include_directories(${RTMIDI_INCLUDE_DIR})


