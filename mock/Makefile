# 静的ライブラリ名
LIBRARY_NAME = libmock.a

# ソースファイル
SRC_FILES = mock_sendto.c mock_ioctl.c mock_functions.c mock_trace.c

# オブジェクトファイル
OBJ_FILES = $(SRC_FILES:.c=.o)

# コンパイラとフラグ
CC = gcc
CFLAGS = -Wall -g -std=c99

# アーカイブコマンド（静的ライブラリ作成）
AR = ar
ARFLAGS = rcs

# デフォルトターゲット
all: $(LIBRARY_NAME)

# 静的ライブラリを作成
$(LIBRARY_NAME): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

# ソースファイルをコンパイルしてオブジェクトファイルを生成
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンターゲット（中間ファイルとライブラリを削除）
clean:
	rm -f $(OBJ_FILES) $(LIBRARY_NAME)

