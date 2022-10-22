cmake_minimum_required(VERSION 3.17)
project(OI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-DOI ${CMAKE_CXX_FLAGS_DEBUG} -Wshadow -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fno-sanitize-recover=all")

# IOI
add_executable(IOI18_a IOI/2018/P1-Combo/files/combo.cpp IOI/2018/P1-Combo/files/grader.cpp)
add_executable(IOI18_b IOI/2018/P2-Seats/files/seats.cpp IOI/2018/P2-Seats/files/grader.cpp)
add_executable(IOI18_c IOI/2018/P3-Werewolf/files/werewolf.cpp IOI/2018/P3-Werewolf/files/grader.cpp)
add_executable(IOI18_d IOI/2018/P4-Mechanical_Doll/files/doll.cpp IOI/2018/P4-Mechanical_Doll/files/grader.cpp)
add_executable(IOI18_e IOI/2018/P5-Highway_Tolls/files/highway.cpp IOI/2018/P5-Highway_Tolls/files/grader.cpp)
add_executable(IOI18_f IOI/2018/P6-Meetings/files/meetings.cpp IOI/2018/P6-Meetings/files/grader.cpp)

add_executable(IOI19_a IOI/2019/P1-Arranging_Shoes/files/shoes.cpp IOI/2019/P1-Arranging_Shoes/files/grader.cpp)
add_executable(IOI19_b IOI/2019/P2-Split_the_Attractions/files/split.cpp IOI/2019/P2-Split_the_Attractions/files/grader.cpp)