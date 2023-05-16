




message("compiling with gtest")
find_package(GTest CONFIG REQUIRED)

add_executable(TestMirrors "TestingReflections.cpp" "../src/BorderHit.cpp")


target_link_libraries(TestMirrors BorderHitter GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TestMirrors PROPERTY CXX_STANDARD 20)
endif()

add_test(TestMirrors TestMirrors)