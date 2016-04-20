###############################################################################
#
set(TREEVIEW_NAME "qtreeview")
set(TREEVIEW_SOURCES
    "main.cpp"
    "TreeView.hpp"
    "TreeView.cpp"
    )
set(TREEVIEW_RESOURCES_FILES 
) 

set(TREEVIEW_QT_MODULES
"Widgets"
"Core"
"Gui"
)

find_package(Qt5Core)
get_target_property(QtCore_location Qt5::Core LOCATION)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(Qt5Widgets)

add_executable(${TREEVIEW_NAME}
   ${TREEVIEW_SOURCES}
  )
  
target_link_libraries(${TREEVIEW_NAME} ${Qt5Widgets_LIBRARIES})
