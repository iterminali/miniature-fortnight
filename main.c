#include <kernel.h>
#include <file.h>
#include <libc.h>

#define CUSA07022_DIR "/user/download/CUSA07022"
#define CUSA07669_DIR "/user/download/CUSA07669"

static void send_notify(const char *msg) {
    SceNotificationRequest req;

    memset(&req, 0, sizeof(req));

    strncpy(req.message, msg, sizeof(req.message) - 1);
    req.message[sizeof(req.message) - 1] = '\0';

    sceKernelSendNotificationRequest(0, &req, sizeof(req), 0);
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
    send_notify("Sanity Check: starting...");

    int res = delete_pair(CUSA07022_DIR);
    if (res == -1) res = delete_pair(CUSA07669_DIR);

    if (res == 1) {
        send_notify("DONE. FILES GONE.");
    } else if (res == -1) {
        send_notify("No Fortnite download files found.");
    } else {
        send_notify("Error: files found but deletion failed.");
    }

    return 0;
}
