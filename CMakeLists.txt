cmake_minimum_required(VERSION 3.16)

project(QMLBoilerplate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Quick
        Qml
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(QMLBoilerplate
        src/main.cpp
)

qt_add_qml_module(QMLBoilerplate
        URI QMLBoilerplate
        VERSION 1.0
        QML_FILES
        qml/Main.qml
        qml/Sample.qml
)

target_link_libraries(gauge-cluster
        PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::Qml
)