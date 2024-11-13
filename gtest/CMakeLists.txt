# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(libmath_test)

set(CMAKE_CXX_STANDARD 11)

# C コンパイラとして gcc を指定
set(CMAKE_C_COMPILER gcc)

# C++ コンパイラとして g++ を指定
set(CMAKE_CXX_COMPILER g++)

# Google Testのパス
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# インクルードパスの追加(一つ上の階層)
include_directories(${CMAKE_SOURCE_DIR}/..)

# テスト用ファイルの追加
add_executable(runTests liblibmath_test.cpp)

# Google Testライブラリ、静的ライブラリのリンク、数学関数を使用するためにmオプションを追加
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ${CMAKE_SOURCE_DIR}/../liblibmath.a m)

# Google Test の XML レポート出力のための設定
# テスト結果を JUnit 形式の XML ファイルとして出力
add_custom_target(
    run_gtests
    COMMAND runTests --gtest_output=xml:test_results.xml
    DEPENDS runTests
    COMMENT "Running unit tests and generating XML report"
)

# ビルド時にテストを自動的に実行する（オプション）
add_custom_target(
    test ALL
    DEPENDS run_gtests
)