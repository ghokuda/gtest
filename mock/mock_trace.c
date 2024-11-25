#include <stdio.h>
#include <string.h>
#include "mock_trace.h"

// 詳細情報を保存する構造体（最大5回分の保存）
static MockData mock_data = {0};  // staticに変更してファイルスコープにする

// モックされた関数
void mock_trace(DetailInfo details[], int count, int mode) {
    if (mock_data.current_call >= MAX_CALLS) {
        printf("Error: Maximum number of calls reached.\n");
        return;
    }

    // 呼び出し情報を保存
    mock_data.mode[mock_data.current_call] = mode;
    mock_data.counts[mock_data.current_call] = count;

    for (int i = 0; i < count; i++) {
        mock_data.details[mock_data.current_call][i] = details[i];
    }

    // 現在の呼び出し回数をインクリメント
    mock_data.current_call++;

    // データをプリント表示（確認用）
    printf("Mocked mock_trace called with mode %d\n", mode);
    for (int i = 0; i < count; i++) {
        printf("Detail %d: id=%d, description=%s\n", i, mock_data.details[mock_data.current_call - 1][i].id, mock_data.details[mock_data.current_call - 1][i].description);
    }
}

// 保存されたデータを取得する関数
MockData *get_saved_data() {
    return &mock_data;  // 保存されたデータを返す
}

// 保存されたデータをクリアする関数
void clear_saved_data() {
    memset(&mock_data, 0, sizeof(mock_data));  // mock_dataをゼロクリア
    printf("Saved data has been cleared.\n");
}
