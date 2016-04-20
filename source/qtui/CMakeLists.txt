include_directories("include")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)

qt5_wrap_ui(ui_FILES ui/mainwindow.ui)

set(source_FILES
      source/main.cpp
      include/mainwindow.hpp
      source/mainwindow.cpp
    )

add_executable(qtui ${source_FILES} ${ui_FILES})

target_link_libraries(qtui ${Qt5Widgets_LIBRARIES})


