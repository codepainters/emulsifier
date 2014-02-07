# GUI/CLI common functionality goes here

set(emulsifier-core-src
    core.cpp
    midiio.cpp
)

add_library(emulsifier-core STATIC ${emulsifier-core-src})
include_directories(${RTMIDI_INCLUDE_DIR})

find_path(RTMIDI_INCLUDE_DIR RtMidi.h HINTS ${RTMIDI_PATH})
find_library(RTMIDI_LIBRARY librtmidi.a HINTS ${RTMIDI_PATH})
target_link_libraries(emulsifier-core ${RTMIDI_LIBRARY})

if (APPLE)
    find_library(COREMIDI_LIBRARY CoreMIDI)
    find_library(COREAUDIO_LIBRARY CoreAudio)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    target_link_libraries(emulsifier-core ${COREMIDI_LIBRARY} ${COREAUDIO_LIBRARY} ${COREFOUNDATION_LIBRARY})
endif (APPLE)

