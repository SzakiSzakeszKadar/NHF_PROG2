cmake_minimum_required(VERSION 3.10)
project(Another_Try)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-DMEMTRACE)
include_directories(include)

add_executable(Another_Try
        main.cpp
        StockItem.cpp
        Worker.cpp
        Machine.cpp
        Tool.cpp
        StockManager.cpp
        OrderManager.cpp
        Order.h
        Order.cpp
        Vector.h
        Pair.hpp
        ConcreteStockItem.cpp
        ConcreteStockItem.h
        memtrace.cpp
        gtest_lite.h
        Inputs.h
)
