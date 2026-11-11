
#include <stdio.h>
#include <string.h>

typedef struct {
    char reserved[45];
    char message[3075];
} notify_request_t;

extern int sceKernelSendNotificationRequest(
    int device,
    notify_request_t *request,
    size_t size,
    int blocking
);

int main(void)
{
    notify_request_t request;

    memset(&request, 0, sizeof(request));
    snprintf(request.message, sizeof(request.message),
             "%s", "Hello From Webkit!");

    return sceKernelSendNotificationRequest(
        0,
        &request,
        sizeof(request),
        0
    );
}
