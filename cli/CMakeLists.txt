# Command line binary

set(emulsifier-cli_HEADERS
    cmdlistdevices.h
)

set(emulsifier-cli_SOURCES
    main.cpp
    cmdlistdevices.cpp
)

qt4_wrap_cpp(emulsifier-cli_HEADERS_MOC ${emulsifier-cli_HEADERS})

include_directories(../core ${RTMIDI_INCLUDE_DIR})
add_executable(emulsifier-cli ${emulsifier-cli_SOURCES} ${emulsifier-cli_HEADERS_MOC})
target_link_libraries(emulsifier-cli emulsifier-core ${QT_QTCORE_LIBRARY})
