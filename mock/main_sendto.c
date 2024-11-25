#include <stdio.h>
#include <string.h>
#include "mock_sendto.h"

int main() {
    // 失敗させる回数を 3 回目に設定
    set_sendto_fail_on_call(3);

    // sendto を呼び出す
    printf("Calling sendto for the first time:\n");
    sendto(1, "Data 1", 6, 0, NULL, 0);  // 正常

    printf("Calling sendto for the second time:\n");
    sendto(1, "Data 2", 6, 0, NULL, 0);  // 正常

    printf("Calling sendto for the third time (should fail):\n");
    ssize_t result = sendto(1, "Data 3", 6, 0, NULL, 0);  // 失敗

    if (result == -1) {
        printf("sendto failed as expected.\n");
    }

    printf("Calling sendto for the fourth time:\n");
    sendto(1, "Data 4", 6, 0, NULL, 0);  // 正常

    // 保存されたデータを読み出す
    printf("Retrieving first packet:\n");
    sendto_packet_t packet = get_sendto_packet(0);
    if (packet.buf != NULL) {
        printf("Packet 0: %.*s\n", (int)packet.len, (char *)packet.buf);
    }

    printf("Retrieving second packet:\n");
    packet = get_sendto_packet(1);
    if (packet.buf != NULL) {
        printf("Packet 1: %.*s\n", (int)packet.len, (char *)packet.buf);
    }

    // パケットのクリア
    printf("Clearing packets...\n");
    clear_sendto_packets();

    // クリア後にデータを読み出す
    printf("Retrieving first packet after clearing:\n");
    packet = get_sendto_packet(0);
    if (packet.buf == NULL) {
        printf("No packet found.\n");
    }

    return 0;
}
