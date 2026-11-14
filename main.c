#include <string.h>
#include <sys/stat.h>
#include <ps4/kernel.h>
#include <ps4/notify.h>

#define CUSA07022_DIR "/user/download/CUSA07022"
#define CUSA07669_DIR "/user/download/CUSA07669"

static int file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}

/*
 * returns:
 *   1  -> at least one file deleted
 *   0  -> files found but unlink failed
 *  -1  -> neither file found (directory empty/missing)
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
    notify("Starting...");

    int res = delete_pair(CUSA07022_DIR);

    if (res == -1) {
        /* fallback title ID */
        res = delete_pair(CUSA07669_DIR);
    }

    if (res == 1) {
        notify("Spoofed");
    } else if (res == -1) {
        notify("Am I gay or are you already spoofed");
    } else {
        notify("Fuck you did shometing with the fortnite negro");
    }

    return 0;
}
