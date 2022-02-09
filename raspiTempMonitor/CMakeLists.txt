cmake_minimum_required(VERSION 3.0.0)
project(TempMonitor VERSION 0.1.0)

include(CTest)
enable_testing()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS program_options) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(TempMonitor main.cpp arguments.cpp) 
    target_link_libraries(TempMonitor ${Boost_LIBRARIES})
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
