cmake_minimum_required(VERSION 3.16)
project(WeatherReport VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets Network)

# Автоматическая генерация moc/uic/rcc (удобно для Qt Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(WeatherReport
    src/main.cpp
    src/MainWindow.cpp
    src/AuthDialog.cpp
    src/LampIndicator.cpp
    src/Requester.cpp
    src/WeatherRequester.cpp
    src/MainWindow.h
    src/AuthDialog.h
    src/LampIndicator.h
    src/Requester.h
    src/WeatherRequester.h
    src/utils.h
    resources/themes.qrc
)



target_link_libraries(WeatherReport PRIVATE Qt5::Widgets Qt5::Network)
