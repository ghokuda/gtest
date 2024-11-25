// mock_trace.h
#ifndef MOCK_TRACE_H
#define MOCK_TRACE_H

#define MAX_DETAILS 10   // 最大詳細情報
#define MAX_CALLS 5      // 最大呼び出し回数

// 詳細情報の構造体
typedef struct {
    int id;
    char description[100];
} DetailInfo;

// 詳細情報を保存する構造体（最大5回分の保存）
typedef struct {
    DetailInfo details[MAX_CALLS][MAX_DETAILS];  // 最大5回の呼び出し、各回最大10個の詳細
    int mode[MAX_CALLS];                         // 各呼び出しのモード
    int counts[MAX_CALLS];                       // 各回の詳細情報数
    int current_call;                            // 現在の呼び出し回数（最大5回）
} MockData;

// モックされた関数の宣言
void mock_trace(DetailInfo details[], int count, int mode);

// 保存されたデータを取得する関数
MockData *get_saved_data();

// 保存されたデータをクリアする関数
void clear_saved_data();

#endif // MOCK_TRACE_H
