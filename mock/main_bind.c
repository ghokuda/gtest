#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h>
#include "mock_bind.h"

int main() {
    // モックを設定（3回目で失敗）
    setup_mock_bind(0, "192.168.1.100", 8080, 3);

    int sockfd = 123; // テスト用ソケットFD
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "192.168.1.100", &addr.sin_addr);

    // 1回目の呼び出し（成功）
    int result = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    assert(result == 0); // モックの返り値
    printf("1st bind: Success\n");

    // 2回目の呼び出し（成功）
    result = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    assert(result == 0); // モックの返り値
    printf("2nd bind: Success\n");

    // 3回目の呼び出し（失敗）
    result = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    assert(result == -1); // モックの失敗設定
    printf("3rd bind: Failed as expected\n");

    // モックのクリア
    clear_mock_bind();

    return 0;
}
