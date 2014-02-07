# Command line binary

set(emulsifier-cli-src
    main.cpp
)

include_directories(../core ${RTMIDI_INCLUDE_DIR})
add_executable(emulsifier-cli ${emulsifier-cli-src})
target_link_libraries(emulsifier-cli emulsifier-core ${QT_QTCORE_LIBRARY})
