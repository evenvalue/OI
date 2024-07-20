cmake_minimum_required(VERSION 3.17)
project(OI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-DLOCAL ${CMAKE_CXX_FLAGS_DEBUG} -Wshadow -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fno-sanitize-recover=all")

# BOI
add_executable(BOI17_f BOI/2017/Day-2/plusminus.cpp)

add_executable(BOI18_b BOI/2018/Day-1/dna.cpp)
add_executable(BOI18_c BOI/2018/Day-1/worm.cpp)
add_executable(BOI18_f BOI/2018/Day-2/paths.cpp)

# CEOI
add_executable(CEOI17_a CEOI/2017/Day-1/a.cpp)
add_executable(CEOI17_b CEOI/2017/Day-1/b.cpp)
add_executable(CEOI17_c CEOI/2017/Day-1/c.cpp)
add_executable(CEOI17_d CEOI/2017/Day-2/d.cpp)
add_executable(CEOI17_e CEOI/2017/Day-2/e.cpp)
add_executable(CEOI17_f CEOI/2017/Day-2/f.cpp)

add_executable(CEOI20_a CEOI/2020/Day-1/a.cpp)
add_executable(CEOI20_d CEOI/2020/Day-2/d.cpp)

add_executable(CEOI21_a CEOI/2021/Day-1/a.cpp)
add_executable(CEOI21_c CEOI/2021/Day-1/c.cpp)
add_executable(CEOI21_d CEOI/2021/Day-2/d.cpp)

# IOI
add_executable(IOI08_a IOI/2008/P1-Type_Printer/printer.cpp)

add_executable(IOI11_a IOI/2011/P2-Race/files/race.cpp IOI/2011/P2-Race/files/grader.cpp)

add_executable(IOI13_d IOI/2013/P4-Cave/files/cave.cpp IOI/2013/P4-Cave/files/grader.cpp)
add_executable(IOI13_e IOI/2013/P5-Robots/files/robots.cpp IOI/2013/P5-Robots/files/grader.cpp)

add_executable(IOI14_c IOI/2014/P3-Game/files/game.cpp IOI/2014/P3-Game/files/grader.cpp)

add_executable(IOI15_a IOI/2015/P1-Boxes/files/boxes.cpp IOI/2015/P1-Boxes/files/grader.cpp)

add_executable(IOI16_a IOI/2016/P1-Detecting_Molecules/files/molecules.cpp IOI/2016/P1-Detecting_Molecules/files/grader.cpp)

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

# JOIFR
add_executable(JOIFR18_a JOI/Final_Round/2018/stove.cpp)
add_executable(JOIFR18_b JOI/Final_Round/2018/art.cpp)
add_executable(JOIFR18_d JOI/Final_Round/2018/commuter_pass.cpp)

add_executable(JOIFR19_a JOI/Final_Round/2019/bitaro.cpp)

add_executable(JOIFR20_a JOI/Final_Round/2020/just_long_neckties.cpp)

add_executable(JOIFR23_a JOI/Final_Round/2023/stone.cpp)

#JOIOC
add_executable(JOIOC14_f JOI/Open_Contest/2014/P6-Secret/files/secret.cpp JOI/Open_Contest/2014/P6-Secret/files/grader.cpp)

#JOISC
add_executable(JOISC18_h JOI/Spring_Training_Camp/2018/Day-3/bitaro.cpp)

add_executable(JOISC19_a JOI/Spring_Training_Camp/2019/Day-1/examination.cpp)

#POI
add_executable(POI19_klu POI/2019/Stage-1/klu.cpp)

# USACO
add_executable(0282 USACO/2013/Open/Silver/p1.cpp)
add_executable(0574 USACO/2015/December/Gold/p2.cpp)
add_executable(0622 USACO/2016/February/Gold/p2.cpp)
add_executable(0647 USACO/2016/Open/Gold/p3.cpp)
add_executable(0815 USACO/2018/February/Gold/p3.cpp)
add_executable(1254 USACO/2022/December/Silver/p1.cpp)
add_executable(1255 USACO/2022/December/Silver/p2.cpp)
add_executable(1256 USACO/2022/December/Silver/p3.cpp)
add_executable(1259 USACO/2022/December/Gold/p3.cpp)
add_executable(1283 USACO/2023/January/Gold/p3.cpp)

# WEOI
add_executable(WEOI24_a WEOI/2024/A/grader.cpp WEOI/2024/A/equal.cpp)
add_executable(WEOI24_b WEOI/2024/B/grader.cpp WEOI/2024/B/mazes.cpp)
add_executable(WEOI24_c WEOI/2024/C/grader.cpp WEOI/2024/C/multihop.cpp)
add_executable(WEOI24_d WEOI/2024/D/grader.cpp WEOI/2024/D/trees.cpp)
