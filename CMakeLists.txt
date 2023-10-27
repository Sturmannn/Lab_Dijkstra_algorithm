cmake_minimum_required(VERSION 3.25.0)

set(PROJECT_NAME Lab_Dijkstra_algorithm)
project(${PROJECT_NAME} LANGUAGES CXX C)

set(testLib GTestLib)
set(test Tests)
set(include Dijkstra_algorithms)
set(perf Perfomance_Tests)
# Путь к заголовочным файлам Boost
set(BOOST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/boost_1_82_0)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GTestLib)


# Путь к библиотекам Boost
#set(BOOST_LIBRARY_DIR /path/to/boost/lib)

# Добавление пути к заголовочным файлам Boost
include_directories(${BOOST_INCLUDE_DIR})

# Добавление пути к библиотекам Boost
#link_directories(${BOOST_LIBRARY_DIR})

# Добавление нужных библиотек Boost
#target_link_libraries(my_target boost_thread boost_system)

add_subdirectory(GTestLib)
add_subdirectory(include)
add_subdirectory(tests)
add_subdirectory(${perf})
#add_subdirectory(perf)