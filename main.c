#include <kernel.h>
#include <libc.h>
#include <string.h>

// The SceNotificationRequest struct must match the kernel's expected layout.
// Source: ps4-payload-sdk (Scene-Collective) – size 0xC30.
typedef struct {
    int  type;                  // 0x00
    int  req_id;                // 0x04
    int  priority;              // 0x08
    int  msg_id;                // 0x0C
    int  target_id;             // 0x10
    int  user_id;               // 0x14
    int  unk1;                  // 0x18
    int  unk2;                  // 0x1C
    int  app_id;                // 0x20
    int  error_num;             // 0x24
    int  unk3;                  // 0x28
    char use_icon_image_uri;    // 0x2C
    char message[1024];         // 0x2D
    char uri[1024];             // 0x42D
    char unkstr[1024];          // 0x82D
} SceNotificationRequest;        // Size = 0xC30

#define CUSA07022_DIR "/user/download/CUSA07022"
#define CUSA07669_DIR "/user/download/CUSA07669"

static void send_notify(const char *msg) {
    SceNotificationRequest req;
    memset(&req, 0, sizeof(req));

    // The kernel expects a null-terminated string in `message`.
    strncpy(req.message, msg, sizeof(req.message) - 1);
    req.message[sizeof(req.message) - 1] = '\0';

    // The first argument is typically 0 for user notifications.
    sceKernelSendNotificationRequest(0, &req, sizeof(req), 0);
}

/*
 * Deletes the Fortnite download cache files in the given directory.
 * Returns:
 *   1  -> at least one file deleted successfully.
 *   0  -> files existed but deletion failed.
 *  -1  -> neither file was found.
 */
static int delete_pair(const char *dir) {
    char dat[256];
    char info[256];
    int found = 0;
    int deleted = 0;

    // Safely build paths (the original used strcpy/strcat).
    snprintf(dat,  sizeof(dat),  "%s/download0.dat",             dir);
    snprintf(info, sizeof(info), "%s/download0_infomation.dat", dir);

    // Use standard C file I/O instead of SDK-specific file_exists/unlink.
    FILE *f = fopen(dat, "r");
    if (f) {
        found = 1;
        fclose(f);
        if (remove(dat) == 0) deleted++;
    }

    f = fopen(info, "r");
    if (f) {
        found = 1;
        fclose(f);
        if (remove(info) == 0) deleted++;
    }

    if (!found)  return -1;
    if (!deleted) return 0;
    return 1;
}

int main(void) {
    send_notify("Sanity Check: starting...");

    int res = delete_pair(CUSA07022_DIR);

    if (res == -1) {
        // Fallback to the other possible title ID.
        res = delete_pair(CUSA07669_DIR);
    }

    if (res == 1) {
        send_notify("DONE. FILES GONE.");
    } else if (res == -1) {
        send_notify("No Fortnite download files found.");
    } else {
        // Files existed but could not be deleted.
        send_notify("Error: files found but deletion failed.");
    }

    return 0;
}
