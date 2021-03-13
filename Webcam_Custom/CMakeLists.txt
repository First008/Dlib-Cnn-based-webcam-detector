
cmake_minimum_required(VERSION 2.8.12)
# Every project needs a name.  We call this the "examples" project.
project(examples)

add_subdirectory(../../dlib dlib_build)

SET("OpenCV_DIR" "wherewer:/your/opencv/build")

find_package(OpenCV QUIET)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Webcam_Custom webcam.cpp)

target_link_libraries(Webcam_Custom dlib::dlib ${OpenCV_LIBS} )



#add_executable(Webcam_Custom webcam.cpp)

target_link_libraries(Webcam_Custom dlib::dlib)

#D:/OpenCV/opencv/build/include