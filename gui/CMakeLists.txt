
set(emulsifier-gui_FORMS mainwindow.ui)

set(emulsifier-gui_SOURCES
    main.cpp
    mainwindow.cpp)

set(emulsifier-gui_HEADERS
    mainwindow.h)

# moc/ui stuff
qt4_wrap_cpp(emulsifier-gui_HEADERS_MOC ${emulsifier-gui_HEADERS})
qt4_wrap_ui(emulsifier-gui_FORMS_HEADERS ${emulsifier-gui_FORMS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Target binary
add_executable(emulsifier-gui ${emulsifier-gui_SOURCES}
    ${emulsifier-gui_HEADERS_MOC}
    ${emulsifier-gui_FORMS_HEADERS}
    ${emulsifier-gui_RESOURCES_RCC})
target_link_libraries(emulsifier-gui ${QT_LIBRARIES})
