cmake_minimum_required(VERSION 3.16)

project (antidebug)

add_executable(attach)
target_sources(attach PRIVATE antidebug-attach.cpp)

