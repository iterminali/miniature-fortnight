#include <kernel.h>
#include <file.h>
#include <libc.h>
#include <stdarg.h>

#define CUSA07022_DIR "/user/download/CUSA07022"
#define CUSA07669_DIR "/user/download/CUSA07669"

/*
 * printf_notification() — ps4-hen style.
 * Variadic: formats `fmt` with vsnprintf, then sends it via
 * SceNotificationRequest through sceKernelSendNotificationRequest().
 * The whole struct is zeroed and the message is null-terminated.
 */
static int printf_notification(const char *fmt, ...) {
    char buffer[0x400];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    SceNotificationRequest req;
    memset(&req, 0, sizeof(req));
    strncpy(req.message, buffer, sizeof(req.message) - 1);
    req.message[sizeof(req.message) - 1] = '\0';

    return sceKernelSendNotificationRequest(0, &req, sizeof(req), 0);
}

static int delete_pair(const char *dir) {
    char dat[256];
    char info[256];
    int found = 0;
    int deleted = 0;

    strcpy(dat, dir);
    strcat(dat, "/download0.dat");

    strcpy(info, dir);
    strcat(info, "/download0_infomation.dat");

    if (file_exists(dat)) {
        found = 1;
        if (unlink(dat) == 0) deleted++;
    }

    if (file_exists(info)) {
        found = 1;
        if (unlink(info) == 0) deleted++;
    }

    if (!found)   return -1;
    if (!deleted) return  0;
    return 1;
}

int main(void) {
    printf_notification("Sanity Check: starting...");

    int res = delete_pair(CUSA07022_DIR);
    if (res == -1) res = delete_pair(CUSA07669_DIR);

    if (res == 1) {
        printf_notification("DONE. FILES GONE.");
    } else if (res == -1) {
        printf_notification("No Fortnite download files found.");
    } else {
        printf_notification("Error: files found but deletion failed.");
    }

    return 0;
}
