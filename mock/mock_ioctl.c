#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "mock_ioctl.h"

// ioctl の状態を管理するグローバル変数
static int ioctl_fail_on_call = -1;  // 何回目で失敗するか（-1 は失敗なし）
static int ioctl_current_call = 0;   // 現在の呼び出し回数
static int ioctl_return_value = 0;   // 成功（0）または失敗（-1）の戻り値

// デバイスごとのブロードキャストアドレスを保存するマップ
static struct {
    char ifname[IFNAMSIZ];
    struct sockaddr_in addr;
} broadcast_addresses[2]; // 2つのデバイスに対応する例

// モックされた ioctl 関数
int ioctl(int fd, unsigned long request, ...) {
    ioctl_current_call++;

    // 失敗する回数が指定されていれば、指定回数目で失敗を返す
    if (ioctl_current_call == ioctl_fail_on_call) {
        printf("Mocked ioctl failed on call %d\n", ioctl_current_call);
        return -1;  // 失敗
    }

    va_list args;
    va_start(args, request);

    if (request == SIOCGIFBRDADDR) {
        // ブロードキャストアドレスを返す処理
        struct ifreq* ifr = va_arg(args, struct ifreq*);
        const char* ifname = ifr->ifr_name;

        // デバイス名に基づいてブロードキャストアドレスを取得
        const char* broadcast_addr = get_broadcast_address(ifname);
        if (broadcast_addr) {
            inet_pton(AF_INET, broadcast_addr, &((struct sockaddr_in*)&ifr->ifr_ifru.ifru_addr)->sin_addr);
            printf("Mocked ioctl SIOCGIFBRDADDR called: ifname=%s, broadcast address=%s\n", ifname, broadcast_addr);
        } else {
            printf("No broadcast address set for interface %s\n", ifname);
            return -1; // エラーとして扱う
        }

        va_end(args);
        return ioctl_return_value;  // 成功または失敗を返す
    }

    va_end(args);

    // 他の ioctl 要求については適切に処理する必要があれば追加
    printf("Mocked ioctl called with unknown request: fd=%d, request=%lu\n", fd, request);
    return ioctl_return_value;  // デフォルトの戻り値
}

// ioctl の失敗回数を設定
void set_ioctl_fail_on_call(int fail_on_call) {
    ioctl_fail_on_call = fail_on_call;
    ioctl_current_call = 0;  // 呼び出し回数をリセット
}

// ioctl の戻り値（成功・失敗）を設定
void set_ioctl_return_value(int return_value) {
    ioctl_return_value = return_value;
}

// デバイス名ごとにブロードキャストアドレスを設定
void set_broadcast_address(const char* ifname, const char* addr) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(broadcast_addresses[i].ifname, ifname) == 0) {
            inet_pton(AF_INET, addr, &broadcast_addresses[i].addr.sin_addr);
            return;
        }
    }

    // 新しいデバイスが追加された場合に設定
    for (int i = 0; i < 2; i++) {
        if (broadcast_addresses[i].ifname[0] == '\0') {  // 空のスロットを探す
            strncpy(broadcast_addresses[i].ifname, ifname, IFNAMSIZ);
            inet_pton(AF_INET, addr, &broadcast_addresses[i].addr.sin_addr);
            return;
        }
    }
}

// デバイス名ごとのブロードキャストアドレスを取得
const char* get_broadcast_address(const char* ifname) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(broadcast_addresses[i].ifname, ifname) == 0) {
            static char addr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &broadcast_addresses[i].addr.sin_addr, addr, INET_ADDRSTRLEN);
            return addr;
        }
    }
    return NULL;  // アドレスが設定されていない場合
}
