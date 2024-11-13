# Makefile

# コンパイラ
CC = gcc

# コンパイルオプション
CFLAGS = -Wall -Werror -O2

# ライブラリ名とオブジェクトファイル
LIB_NAME = libmath
LIB_FILE = lib$(LIB_NAME).a
OBJ_FILE = lib_math.o

# 実行ファイル名
TARGET = main

# ルール: 全体ビルド
all: $(TARGET)

# ルール: mainプログラムのコンパイル
$(TARGET): main.o $(LIB_FILE)
	$(CC) main.o -L. -l$(LIB_NAME) -o $(TARGET)

# ルール: 静的ライブラリの作成
$(LIB_FILE): $(OBJ_FILE)
	ar rcs $(LIB_FILE) $(OBJ_FILE)

# ルール: オブジェクトファイルのコンパイル
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ルール: クリーンアップ
clean:
	rm -f *.o $(LIB_FILE) $(TARGET)

# フォースビルドのためのルール（make rebuild）
rebuild: clean all

.PHONY: all clean rebuild
