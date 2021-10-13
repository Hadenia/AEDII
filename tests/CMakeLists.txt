cmake_minimum_required(VERSION 3.10.2)
project(Testes-EDI)

set(CMAKE_CXX_STANDARD 11)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Link runTests with what we want to test and the GTest and pthread library
# add_executable(runTestsListAdj testGrafoListaAdj.cpp)
# add_executable(runTestsMatrizAdj testGrafoMatrizAdj.cpp)
# add_executable(runTestsGrafoNavegacao testGrafoNavegacao.cpp)
# add_executable(runtestMenorCaminho testMenorCaminho.cpp)
# add_executable(runTestGrafomst testMST.cpp)
add_executable(runTestMaps testTabelaHash.cpp) 

# target_link_libraries(runTestsListAdj ${GTEST_LIBRARIES} pthread)
# target_link_libraries(runTestsMatrizAdj ${GTEST_LIBRARIES} pthread)
# target_link_libraries(runTestsGrafoNavegacao ${GTEST_LIBRARIES} pthread)
# target_link_libraries(runtestMenorCaminho ${GTEST_LIBRARIES} pthread)
# target_link_libraries(runTestGrafomst ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTestMaps ${GTEST_LIBRARIES} pthread)