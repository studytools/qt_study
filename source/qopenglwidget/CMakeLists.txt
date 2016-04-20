###############################################################################
#qOpenGLWidget
set(QOPENGLWIDGET_NAME "qopenglwidget")
set(QOPENGLWIDGET_SOURCES
    "main.cpp"
    "qopenglwidget.hpp"
    "qopenglwidget.cpp"
    "mainwindow.hpp"
    "mainwindow.cpp"
    )
set(QOPENGLWIDGET_RESOURCES_FILES 
  "../../resource/qopenglwidget.qrc"
) 

set(QOPENGLWIDGET_QT_MODULES
"Widgets"
"Core"
"OpenGL"
"Gui"
)

find_package(Qt5Core)
get_target_property(QtCore_location Qt5::Core LOCATION)
qt5_add_resources(QOPENGLWIDGET_RESOURCES ${QOPENGLWIDGET_RESOURCES_FILES})

find_package(Qt5Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenGL)
if(NOT OPENGL_FOUND)
  message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)

add_executable(${QOPENGLWIDGET_NAME}
  ${QOPENGLWIDGET_RESOURCES}
  ${QOPENGLWIDGET_SOURCES}
  )
  
message(STATUS LIB: ${Qt5Widgets_LIBRARIES})

target_link_libraries(${QOPENGLWIDGET_NAME} ${Qt5Widgets_LIBRARIES} ${OPENGL_LIBRARIES})

