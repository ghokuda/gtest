# Makefile

# コンパイラ設定
CC = gcc
CXX = g++
CXXFLAGS = -std=c++14

# Google Test のインクルードパス (必要に応じて変更)
GTEST_DIR = /usr/include/gtest
GTEST_LIBS = -lgtest -lgtest_main -pthread

# 一つ上の階層のインクルードパス
INCLUDE_DIRS = -I$(GTEST_DIR) -I..

# 静的ライブラリのパス (一つ上の階層)
LIBS = ../liblibmath.a -lm

# 出力先ディレクトリとテスト用ファイル
TARGET_DIR = test_build
TARGET = $(TARGET_DIR)/runTests
SOURCES = liblibmath_test.cpp

# XML レポートの出力ファイル
TEST_REPORT = $(TARGET_DIR)/test_results.xml

# 出力ディレクトリを作成
$(shell mkdir -p $(TARGET_DIR))

# デフォルトのビルドルール
all: $(TARGET)

# テスト実行ファイルのリンク
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $(SOURCES) -o $(TARGET) $(GTEST_LIBS) $(LIBS)

# テストの実行と XML レポートの生成
run_gtests: $(TARGET)
	./$(TARGET) --gtest_output=xml:$(TEST_REPORT)

# ビルド時にテストを自動的に実行
test: all run_gtests

# クリーンアップ
clean:
	rm -f $(TARGET) $(TEST_REPORT)

