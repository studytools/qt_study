###############################################################################
#
set(QTPOPMENU_NAME "qtpopmenu")
set(QTPOPMENU_SOURCES
    "main.cpp"
    "qtpopmenu.hpp"
    "qtpopmenu.cpp"
    )

set(QTPOPMENU_QT_MODULES
"Widgets"
"Core"
"Gui"
)
find_package(Qt5Core)
get_target_property(QtCore_location Qt5::Core LOCATION)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(Qt5Widgets)
#find_package(Qt5Gui)

add_executable(${QTPOPMENU_NAME}
  ${QTPOPMENU_SOURCES}
  ${QTPOPMENU_RESOURCES_FILES}
  )

target_link_libraries(${QTPOPMENU_NAME} ${Qt5Widgets_LIBRARIES})