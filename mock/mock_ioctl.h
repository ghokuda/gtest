#ifndef MOCK_IOCTL_H
#define MOCK_IOCTL_H

#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>

// ioctl のモック関数
int ioctl(int fd, unsigned long request, ...);

// 外部から ioctl の成功/失敗を制御するための関数
void set_ioctl_fail_on_call(int fail_on_call);
void set_ioctl_return_value(int return_value);

// デバイス名ごとにブロードキャストアドレスを設定するための関数
void set_broadcast_address(const char* ifname, const char* addr);

// デバイスごとのブロードキャストアドレスを取得
const char* get_broadcast_address(const char* ifname);

#endif // MOCK_FUNCTIONS_H
