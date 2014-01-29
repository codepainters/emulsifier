# Command line binary

set(emulsifier-cli-src
    main.cpp
)

add_executable(emulsifier-cli ${emulsifier-cli-src})
target_link_libraries(emulsifier-cli emulsifier-core ${QT_QTCORE_LIBRARY})
