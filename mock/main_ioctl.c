#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "mock_ioctl.h"

int main() {
    // 成功する場合
    set_ioctl_return_value(0);  // 成功を設定
    set_ioctl_fail_on_call(-1);  // 失敗しない設定

    // デバイスごとに異なるブロードキャストアドレスを設定
    set_broadcast_address("eth3", "192.168.1.255");
    set_broadcast_address("eth4", "192.168.2.255");

    struct ifreq ifr;
    int fd = 0;  // 仮のファイルディスクリプタ

    // eth3 のブロードキャストアドレスを取得
    printf("Calling ioctl to get eth3 broadcast address:\n");
    strncpy(ifr.ifr_name, "eth3", IFNAMSIZ);
    int result = ioctl(fd, SIOCGIFBRDADDR, &ifr);  // SIOCGIFBRDADDR を使用
    if (result == 0) {
        char addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &((struct sockaddr_in*)&ifr.ifr_ifru.ifru_addr)->sin_addr, addr, INET_ADDRSTRLEN);
        printf("Broadcast address for eth3: %s\n", addr);  // eth3 のブロードキャストアドレスを表示
    } else {
        printf("ioctl failed for eth3\n");
    }

    // eth4 のブロードキャストアドレスを取得
    printf("Calling ioctl to get eth4 broadcast address:\n");
    strncpy(ifr.ifr_name, "eth4", IFNAMSIZ);
    result = ioctl(fd, SIOCGIFBRDADDR, &ifr);  // SIOCGIFBRDADDR を使用
    if (result == 0) {
        char addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &((struct sockaddr_in*)&ifr.ifr_ifru.ifru_addr)->sin_addr, addr, INET_ADDRSTRLEN);
        printf("Broadcast address for eth4: %s\n", addr);  // eth4 のブロードキャストアドレスを表示
    } else {
        printf("ioctl failed for eth4\n");
    }

    return 0;
}
