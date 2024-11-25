#include "mock_bind.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

// モック用のグローバルデータ
static MockBindContext mock_bind_context;

// モックの `bind` 関数
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    // 呼び出し回数をインクリメント
    mock_bind_context.call_count++;

    // 指定された回数目で失敗を返す
    if (mock_bind_context.fail_after > 0 &&
        mock_bind_context.call_count >= mock_bind_context.fail_after) {
        return -1; // エラーを返す
    }

    // 通常の動作: 引数を記録
    mock_bind_context.socket_fd = sockfd;
    if (addrlen == sizeof(struct sockaddr_in)) {
        const struct sockaddr_in *addr_in = (const struct sockaddr_in *)addr;
        memcpy(&mock_bind_context.address, addr_in, sizeof(struct sockaddr_in));
    }

    // モックの返り値を返す
    return mock_bind_context.return_value;
}

// モック設定用関数
void setup_mock_bind(int return_value, const char *expected_ip, uint16_t expected_port, int fail_after) {
    mock_bind_context.return_value = return_value;
    mock_bind_context.fail_after = fail_after;
    mock_bind_context.call_count = 0;

    // IPとポートを設定
    if (expected_ip) {
        inet_pton(AF_INET, expected_ip, &mock_bind_context.address.sin_addr);
    }
    mock_bind_context.address.sin_port = htons(expected_port);
    mock_bind_context.address.sin_family = AF_INET;
}

// モックのクリア
void clear_mock_bind() {
    memset(&mock_bind_context, 0, sizeof(mock_bind_context));
}

// モックデータ取得関数（テスト用）
MockBindContext *get_mock_bind_context() {
    return &mock_bind_context;
}
