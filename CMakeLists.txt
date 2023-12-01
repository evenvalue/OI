cmake_minimum_required(VERSION 3.17)
project(OI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-Devenvalue ${CMAKE_CXX_FLAGS_DEBUG} -Wshadow -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fno-sanitize-recover=all")

#CEOI
add_executable(CEOI20_a CEOI/2020/Day-1/a.cpp)
add_executable(CEOI20_d CEOI/2020/Day-2/d.cpp)

add_executable(CEOI21_a CEOI/2021/Day-1/a.cpp)
add_executable(CEOI21_c CEOI/2021/Day-1/c.cpp)
add_executable(CEOI21_d CEOI/2021/Day-2/d.cpp)

# IOI
add_executable(IOI11_a IOI/2011/P2-Race/files/race.cpp IOI/2011/P2-Race/files/grader.cpp)

add_executable(IOI18_a IOI/2018/P1-Combo/files/combo.cpp IOI/2018/P1-Combo/files/grader.cpp)
add_executable(IOI18_b IOI/2018/P2-Seats/files/seats.cpp IOI/2018/P2-Seats/files/grader.cpp)
add_executable(IOI18_c IOI/2018/P3-Werewolf/files/werewolf.cpp IOI/2018/P3-Werewolf/files/grader.cpp)
add_executable(IOI18_d IOI/2018/P4-Mechanical_Doll/files/doll.cpp IOI/2018/P4-Mechanical_Doll/files/grader.cpp)
add_executable(IOI18_e IOI/2018/P5-Highway_Tolls/files/highway.cpp IOI/2018/P5-Highway_Tolls/files/grader.cpp)
add_executable(IOI18_f IOI/2018/P6-Meetings/files/meetings.cpp IOI/2018/P6-Meetings/files/grader.cpp)

add_executable(IOI19_a IOI/2019/P1-Arranging_Shoes/files/shoes.cpp IOI/2019/P1-Arranging_Shoes/files/grader.cpp)
add_executable(IOI19_b IOI/2019/P2-Split_the_Attractions/files/split.cpp IOI/2019/P2-Split_the_Attractions/files/grader.cpp)
add_executable(IOI19_d IOI/2019/P4-Broken_Line/files/line.cpp)
add_executable(IOI19_e IOI/2019/P5-Vision_Program/files/vision.cpp IOI/2019/P5-Vision_Program/files/grader.cpp)
add_executable(IOI19_f IOI/2019/P6-Sky_Walking/files/walk.cpp IOI/2019/P6-Sky_Walking/files/grader.cpp)

add_executable(IOI20_a IOI/2020/P1-Comparing_Plants/files/plants.cpp IOI/2020/P1-Comparing_Plants/files/grader.cpp)
add_executable(IOI20_b IOI/2020/P2-Connecting_Supertrees/files/supertrees.cpp IOI/2020/P2-Connecting_Supertrees/files/grader.cpp)
add_executable(IOI20_c IOI/2020/P3-Carnival_Tickets/files/tickets.cpp IOI/2020/P3-Carnival_Tickets/files/grader.cpp)
add_executable(IOI20_d IOI/2020/P4-Packing_Biscuits/files/biscuits.cpp IOI/2020/P4-Packing_Biscuits/files/grader.cpp)
add_executable(IOI20_e IOI/2020/P5-Counting_Mushrooms/files/mushrooms.cpp IOI/2020/P5-Counting_Mushrooms/files/grader.cpp)
add_executable(IOI20_f IOI/2020/P6-Stations/files/stations.cpp IOI/2020/P6-Stations/files/grader.cpp)

add_executable(IOI23_a IOI/2023/P1-Closing-Time/files/closing.cpp IOI/2023/P1-Closing-Time/files/grader.cpp)
add_executable(IOI23_b IOI/2023/P2-Longest-Trip/files/longesttrip.cpp IOI/2023/P2-Longest-Trip/files/grader.cpp)
add_executable(IOI23_e IOI/2023/P5-Overtaking/files/overtaking.cpp IOI/2023/P5-Overtaking/files/grader.cpp)