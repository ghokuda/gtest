#ifndef MOCK_SENDTO_H
#define MOCK_SENDTO_H

#include <stddef.h>
#include <sys/socket.h>

// 1パケットの最大サイズと最大パケット数
#define MAX_PACKET_SIZE 1500
#define MAX_PACKETS 1000

// 送信データを格納する構造体
typedef struct {
    void *buf;
    size_t len;
} sendto_packet_t;

// 送信データを格納するためのバッファ
static char sendto_buffer[MAX_PACKET_SIZE * MAX_PACKETS];

// 送信されたデータを保持する構造体
static sendto_packet_t sendto_packets[MAX_PACKETS];
static int sendto_count = 0; // 現在のパケット数

// モックされた sendto 関数
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

// 外部からデータを取得する関数
sendto_packet_t get_sendto_packet(int index);

// パケットのデータをクリアする関数
void clear_sendto_packets();

// 失敗する回数を指定する関数
void set_sendto_fail_on_call(int fail_count);

#endif
