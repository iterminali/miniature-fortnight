#include <kernel.h>
#include <file.h>
#include <libc.h>
#include <string.h>
#include <stdio.h>

#define CUSA07022_DIR "/user/download/CUSA07022"
#define CUSA07669_DIR "/user/download/CUSA07669"

static void send_notify(const char *msg)
{
    SceNotificationRequest req;

    memset(&req, 0, sizeof(req));
    strncpy(req.message, msg, sizeof(req.message) - 1);

    sceKernelSendNotificationRequest(0, &req, sizeof(req), 0);
}

static int check_pair(const char *dir)
{
    char dat[256];
    char info[256];

    snprintf(dat, sizeof(dat), "%s/download0.dat", dir);
    snprintf(info, sizeof(info),
             "%s/download0_infomation.dat", dir);

    int found = 0;

    if (file_exists(dat))
        found++;

    if (file_exists(info))
        found++;

    return found;
}

int main(void)
{
    send_notify("Sanity Check: starting...");

    int found = check_pair(CUSA07022_DIR);

    if (found == 0)
        found = check_pair(CUSA07669_DIR);

    if (found > 0)
        send_notify("Matching Fortnite files found.");
    else
        send_notify("No Fortnite download files found.");

    return 0;
}
