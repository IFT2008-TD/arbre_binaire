set(TEST_SOURCES tests_arbre_binaire.cpp ${PROJECT_SOURCE_DIR}/arbre_binaire.h)

add_executable(
        tests_arbre_binaire
        ${TEST_SOURCES}
)

target_include_directories(tests_arbre_binaire PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        tests_arbre_binaire
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(tests_arbre_binaire)