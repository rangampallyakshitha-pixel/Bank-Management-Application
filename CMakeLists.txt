cmake_minimum_required(VERSION 3.16)
project(bankapp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(bankapp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    bankaccount.cpp
    bankaccount.h
)

target_link_libraries(bankapp Qt6::Core Qt6::Gui Qt6::Widgets)
