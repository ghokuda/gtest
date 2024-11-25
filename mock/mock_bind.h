#ifndef MOCK_BIND_H
#define MOCK_BIND_H

#include <netinet/in.h>
#include <sys/socket.h>

// モックで使用するデータ構造
typedef struct {
    int socket_fd;
    struct sockaddr_in address;
    int return_value;
    int fail_after; // この回数目で失敗
    int call_count; // 呼び出し回数を記録
} MockBindContext;

// モックの設定・管理関数
void setup_mock_bind(int return_value, const char *expected_ip, uint16_t expected_port, int fail_after);
void clear_mock_bind();
MockBindContext *get_mock_bind_context();

#endif // MOCK_BIND_H
