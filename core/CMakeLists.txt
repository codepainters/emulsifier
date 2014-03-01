# GUI/CLI common functionality goes here

find_package(RtMidi REQUIRED)

set(emulsifier-core_HEADERS
    midiio.h
    midideviceinquiry.h
)

set(emulsifier-core_SOURCES
    midiio.cpp
    midideviceinquiry.cpp
)

# moc/ui stuff
qt4_wrap_cpp(emulsifier-core_HEADERS_MOC ${emulsifier-core_HEADERS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(emulsifier-core STATIC ${emulsifier-core_SOURCES}  ${emulsifier-core_HEADERS_MOC})

target_link_libraries(emulsifier-core ${RTMIDI_LIBRARIES})
include_directories(${RTMIDI_INCLUDE_DIR})


