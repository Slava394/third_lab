cmake_minimum_required(VERSION 3.28.3)

project(LastChance VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/collection)
include_directories(${CMAKE_SOURCE_DIR}/include/generator)
include_directories(${CMAKE_SOURCE_DIR}/include/gui)
include_directories(${CMAKE_SOURCE_DIR}/include/target)
include_directories(${CMAKE_SOURCE_DIR}/include/test)
include_directories(${CMAKE_SOURCE_DIR}/include/type)


set(BASE_SOURCES 
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

set(TEST_SOURCES
    ${BASE_SOURCES}
    include/test/Test.h
    src/test/Test.cpp
)

add_executable(TestSet testSet.cpp ${TEST_SOURCES})
add_executable(TestDictionary testDictionary.cpp ${TEST_SOURCES})
add_executable(TestHistogram testHistogram.cpp ${TEST_SOURCES})

enable_testing()

add_test(NAME TestSet COMMAND TestSet)
add_test(NAME TestDictionary COMMAND TestDictionary)
add_test(NAME TestHistogram COMMAND TestHistogram)