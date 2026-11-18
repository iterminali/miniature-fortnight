#include <kernel.h>
#include <file.h>
#include <libc.h>

#define CUSA07022_DIR "/user/download/CUSA07022"
#define CUSA07669_DIR "/user/download/CUSA07669"

static void send_notify(const char *msg) {
    SceNotificationRequest req;
    memset(&req, 0, sizeof(req));

    req.type = 0;
    req.req_id = 0;
    req.priority = 0;
    req.msg_id = 0;
    req.target_id = 0;
    req.user_id = 0;
    req.unk1 = 0;
    req.unk2 = 0;
    req.app_id = 0;
    req.error_num = 0;
    req.unk3 = 0;
    req.use_icon_image_uri = 0;

    strncpy(req.message, msg, sizeof(req.message) - 1);
    req.message[sizeof(req.message) - 1] = '\0';

    sceKernelSendNotificationRequest(0, &req, sizeof(req), 0);
}

/*
 * returns:
 *   1  -> at least one file deleted
 *   0  -> files found but unlink failed
 *  -1  -> neither file found
 */
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

    if (!found)  return -1;
    if (!deleted) return 0;
    return 1;
}

int main(void) {
    send_notify("Sanity Check: starting...");

    int res = delete_pair(CUSA07022_DIR);

    if (res == -1) {
        res = delete_pair(CUSA07669_DIR);
    }

    if (res == 1) {
        send_notify("DONE. FILES GONE.");
    } else if (res == -1) {
        send_notify("NIGGA DO YOU EVEN HAVE A FILES OR FORTNITE.");
    } else {
        send_notify("FUCK U DID SOMETHING BECAUSE IT WENT FUCKING NIGGER BITCH WRONG");
    }

    return 0;
}
