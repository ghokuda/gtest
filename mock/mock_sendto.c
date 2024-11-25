#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mock_sendto.h"

// 失敗を返す条件を指定するグローバル変数
static int fail_on_call = -1;  // 何回目で失敗するかを指定 (-1 は失敗なし)
static int current_call = 0;   // 現在の呼び出し回数

// sendto モック関数
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) {
    current_call++;

    // 失敗を指定した回数目で失敗
    if (current_call == fail_on_call) {
        printf("Mocked sendto failed on call %d\n", current_call);
        return -1;  // 失敗を示す
    }

    // データが最大数を超えた場合、古いデータを削除
    if (sendto_count >= MAX_PACKETS) {
        // 古いデータを前方にシフト
        memmove(&sendto_packets[0], &sendto_packets[1], (MAX_PACKETS - 1) * sizeof(sendto_packet_t));
        sendto_count--;
    }

    // 保存するデータのメモリ位置を計算
    char *packet_data = &sendto_buffer[sendto_count * MAX_PACKET_SIZE];
    memcpy(packet_data, buf, len);

    // データを保存
    sendto_packets[sendto_count].buf = packet_data;
    sendto_packets[sendto_count].len = len;
    sendto_count++;

    printf("Mocked sendto called: sockfd=%d, len=%zu\n", sockfd, len);
    return len;  // 正常終了
}

// 外部からデータを取得する関数
sendto_packet_t get_sendto_packet(int index) {
    if (index < 0 || index >= sendto_count) {
        sendto_packet_t empty_packet = {NULL, 0};
        return empty_packet;
    }
    return sendto_packets[index];
}

// パケットデータをクリアする関数
void clear_sendto_packets() {
    sendto_count = 0; // パケット数をリセット
    memset(sendto_buffer, 0, sizeof(sendto_buffer)); // バッファをクリア
}

// 外部から失敗回数を設定する関数
void set_sendto_fail_on_call(int fail_count) {
    fail_on_call = fail_count;
    current_call = 0;  // 呼び出し回数をリセット
}
