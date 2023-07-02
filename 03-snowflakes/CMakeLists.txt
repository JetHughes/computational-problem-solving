cmake_minimum_required(VERSION 3.10)

project(snowflakes)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(snowflakes 
  main.cpp
  Segment.h
  Segment.cpp)

# add_executable(runtests
#   runtests.cpp
#   snowflake.h
#   snowflake.cpp
#   doctest.h)

target_include_directories(snowflakes PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
# target_include_directories(runtests PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(snowflakes ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${OpenCV_LIBS})
# target_link_libraries(runtests ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${OpenCV_LIBS})