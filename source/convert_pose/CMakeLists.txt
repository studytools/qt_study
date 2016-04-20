include_directories("include")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#boost
set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost 1.60.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)

qt5_wrap_ui(ui_FILES ui/widget.ui)

set(source_FILES
      source/main.cpp
      include/mainwindow.hpp
      source/mainwindow.cpp
      include/read_file.hpp
      source/read_file.cpp
    )

add_executable(conver_pose ${source_FILES} ${ui_FILES})

target_link_libraries(conver_pose ${Qt5Widgets_LIBRARIES})


