cmake_minimum_required(VERSION 3.16)

project(GaugeQML VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Quick
        Qml
        SerialPort
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(gauge_cluster_app
        src/main.cpp
        src/ClusterModel.cpp
        src/ClusterModel.h
        src/SerialInput.cpp
        src/SerialInput.h
)

qt_add_qml_module(gauge_cluster_app
        URI GaugeQML
        VERSION 1.0
        QML_FILES
        qml/Main.qml
        qml/CompassGauge.qml
        qml/SpriteLayer.qml
)

target_link_libraries(gauge_cluster_app
        PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::Qml
        Qt6::SerialPort
)


add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:gauge_cluster_app>/assets
        COMMENT "Copying runtime assets"
        VERBATIM
)