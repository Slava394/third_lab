cmake_minimum_required(VERSION 3.28.3)

project(LastChance VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/collection)
include_directories(${CMAKE_SOURCE_DIR}/include/concept)
include_directories(${CMAKE_SOURCE_DIR}/include/generator)
include_directories(${CMAKE_SOURCE_DIR}/include/gui)
include_directories(${CMAKE_SOURCE_DIR}/include/target)
include_directories(${CMAKE_SOURCE_DIR}/include/test)
include_directories(${CMAKE_SOURCE_DIR}/include/type)

set(BASE_SOURCES 
    include/concept/Concept.h

    include/collection/AVLTree.h

    include/collection/ISet.h
    include/collection/Set.h

    include/collection/IDictionary.h
    include/collection/Dictionary.h

    include/collection/Vector.h
    include/collection/ISequence.h
    include/collection/Sequence.h

    include/target/Interval.h
    include/target/HistogramBin.h
    include/target/Histogram.h

    include/type/Point.h
    include/type/Person.h

    include/generator/Generator.h
    src/generator/Generator.cpp
)

set(GUI_SOURCES 
    include/gui/GenerateDialog.h
    src/gui/GenerateDialog.cpp

    include/gui/HistogramWidget.h
    src/gui/HistogramWidget.cpp

    include/gui/IntervalsDialog.h
    src/gui/IntervalsDialog.cpp

    include/gui/MainWindow.h
    src/gui/MainWindow.cpp

    include/gui/OpenDialog.h
    src/gui/OpenDialog.cpp
)

set(MAIN_SOURCE main.cpp)

add_executable(Histogram
    ${BASE_SOURCES}
    ${GUI_SOURCES}
    ${MAIN_SOURCE}
)

target_link_libraries(Histogram Qt6::Widgets)

set(LOAD_TEST_SOURCES
    ${BASE_SOURCES}
    include/test/LoadTest.h
    src/test/LoadTest.cpp
)

add_executable(LoadTestSet loadTestSet.cpp ${LOAD_TEST_SOURCES})
add_executable(LoadTestDictionary loadTestDictionary.cpp ${LOAD_TEST_SOURCES})

set(UNIT_TEST_SOURCES
    ${BASE_SOURCES}
    include/test/UnitTest.h
    src/test/UnitTest.cpp
)

add_executable(UnitTestSet unitTestSet.cpp ${UNIT_TEST_SOURCES})
add_executable(UnitTestDictionary unitTestDictionary.cpp ${UNIT_TEST_SOURCES})
add_executable(UnitTestHistogram unitTestHistogram.cpp ${UNIT_TEST_SOURCES})

enable_testing()

add_test(NAME UnitTestSet COMMAND UnitTestSet)
add_test(NAME UnitTestDictionary COMMAND UnitTestDictionary)
add_test(NAME UnitTestHistogram COMMAND UnitTestHistogram)