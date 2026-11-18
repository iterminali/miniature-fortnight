#include "ps4.h"
#include "sysutil.h"

int main(void)
{
    initSysUtil();

    // Method 1: SDK notification
    printf_notification("FORTNITE 67 - METHOD 1");

    // Method 2: Direct PS4 notification API
    char message[] = "FORTNITE 67 - METHOD 2";

    sceSysUtilSendSystemNotificationWithText(
        0,
        message
    );

    return 0;
}
