cmake_minimum_required(VERSION 3.8)
project(bmk_hackerrank)

set(CMAKE_CXX_STANDARD 14)


add_library(hackerrank_lib lib/hackerrank_lib.cpp)

################################################################################

add_executable(jenny_subtree jenny_subtree/solution.cpp)

################################################################################

add_executable(pair_sums pair_sums/solution.cc)

################################################################################

add_executable(matrix_layer_rotation matrix_layer_rotation/solution.cpp)

################################################################################

add_executable(sorted_subsegments sorted_subsegments/solution.cc)

################################################################################

add_executable(max_subarray_sum max_subarray_sum/solution.cc)

################################################################################

add_executable(max_palindromes max_palindromes/solution.cc)

################################################################################

add_executable(sherlock_anagrams sherlock_anagrams/solution.cc)

################################################################################

add_executable(min_max_riddle min_max_riddle/solution.cc)

################################################################################

add_executable(computer_game computer_game/solution.cc)

################################################################################

add_executable(mission_points mission_points/solution.cc)

################################################################################

add_executable(king_richard_knights king_richard_knights/solution.cc)

################################################################################

add_executable(task_scheduling task_scheduling/solution.cpp)

################################################################################

add_executable(cut_tree cut_tree/solution.cc)

################################################################################

add_executable(synchronous_shopping synchronous_shopping/solution.cc)

################################################################################

add_executable(minimum_penalty minimum_penalty/solution.cc)

################################################################################

add_executable(maximum_index_product maximum_index_product/solution.cc)

################################################################################

add_executable(abbreviation abbreviation/solution.cc)