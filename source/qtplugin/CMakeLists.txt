###############################################################################
#qtplugin
set(QTPLUGIN_NAME "QtPlugin")
set(QTPLUGIN_SOURCES
    "main.cpp"
    )

find_package(Qt5Core)
find_package(Qt5Gui)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QTiffPlugin_location Qt5::QTiffPlugin LOCATION)
message("Qttiff: ${QTiffPlugin_location}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${QTPLUGIN_NAME}
  ${QTPLUGIN_RESOURCES}
  ${QTPLUGIN_SOURCES}
  )
#target_link_libraries(${QTPLUGIN_NAME} Qt5::QTiffPlugin)
qt5_use_modules(${QTPLUGIN_NAME} Widgets)  