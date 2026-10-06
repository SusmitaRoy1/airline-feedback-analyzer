cmake_minimum_required(VERSION 3.16)
project(airline_feedback_analyzer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---------------------------------------------------------------- library ----
add_library(afa
    src/tokenizer.cpp
    src/csv_reader.cpp
    src/lexicon.cpp
    src/scorer.cpp
    src/evaluator.cpp
)
target_include_directories(afa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# -------------------------------------------------------------------- app ----
add_executable(afa_cli apps/main.cpp)
target_link_libraries(afa_cli PRIVATE afa)
set_target_properties(afa_cli PROPERTIES OUTPUT_NAME afa)

# ------------------------------------------------------------------ tests ----
enable_testing()

# Each suite is its own executable so one crash cannot hide the others.
set(AFA_TEST_SUITES
    test_tokenizer
    test_csv
    test_lexicon
    test_scorer
    test_evaluator
)

foreach(suite ${AFA_TEST_SUITES})
    add_executable(${suite} tests/${suite}.cpp)
    target_link_libraries(${suite} PRIVATE afa)
    target_include_directories(${suite} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_test(NAME ${suite} COMMAND ${suite})
endforeach()
