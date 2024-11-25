#include <stdio.h>
#include "mock_trace.h"

int main() {
    // テストデータ
    DetailInfo details1[] = {
        {1, "First detail"},
        {2, "Second detail"}
    };

    DetailInfo details2[] = {
        {3, "Third detail"},
        {4, "Fourth detail"}
    };

    // モック関数の呼び出し
    mock_trace(details1, 2, 100);  // 2つの詳細情報、モード100
    mock_trace(details2, 2, 200);  // 2つの詳細情報、モード200

    // 保存されたデータを取得して表示
    MockData *data = get_saved_data();
    if (data != NULL) {
        printf("\nRetrieved saved data:\n");
        for (int i = 0; i < data->current_call; i++) {
            printf("Call %d, Mode: %d, Count: %d\n", i, data->mode[i], data->counts[i]);
            for (int j = 0; j < data->counts[i]; j++) {
                printf("Detail %d: id=%d, description=%s\n", j, data->details[i][j].id, data->details[i][j].description);
            }
        }
    }

    // 保存されたデータをクリア
    clear_saved_data();

    // データクリア後の確認
    data = get_saved_data();
    if (data != NULL) {
        printf("\nRetrieved saved data after clearing:\n");
        if (data->current_call == 0) {
            printf("No data found.\n");
        }
    }

    return 0;
}
