#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/inotify.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define EVENT_BUF_LEN     (1024 * (EVENT_SIZE + 16))

static int inotify_fd = -1;
static int watch_fd = -1;
static int file_changed_flag = 0;
static pthread_t watcher_thread;

static char watch_path[1024] = {0};

void* watcher_func(void* arg) {
    char buffer[EVENT_BUF_LEN];

    while (1) {
        int length = read(inotify_fd, buffer, EVENT_BUF_LEN);
        if (length < 0) {
            perror("read");
            break;
        }

        int i = 0;
        while (i < length) {
            struct inotify_event* event = (struct inotify_event*)&buffer[i];
            if (event->mask & (IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | IN_MOVED_TO | IN_DELETE_SELF)) {
                file_changed_flag = 1;
            }
            i += EVENT_SIZE + event->len;
        }
    }

    return NULL;
}

void watch_file(const char* path) {
    if (inotify_fd >= 0) {
        if (watch_fd >= 0) inotify_rm_watch(inotify_fd, watch_fd);
        close(inotify_fd);
    }

    file_changed_flag = 0;

    strncpy(watch_path, path, sizeof(watch_path) - 1);
    watch_path[sizeof(watch_path) - 1] = '\0';

    inotify_fd = inotify_init1(IN_NONBLOCK);
    if (inotify_fd < 0) {
        perror("inotify_init");
        return;
    }

    watch_fd = inotify_add_watch(inotify_fd, watch_path, IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | IN_MOVED_TO | IN_DELETE_SELF);
    if (watch_fd < 0) {
        perror("inotify_add_watch");
        close(inotify_fd);
        inotify_fd = -1;
        return;
    }

    pthread_create(&watcher_thread, NULL, watcher_func, NULL);
    pthread_detach(watcher_thread);
}

int file_changed() {
    if (file_changed_flag) {
        file_changed_flag = 0;
        return 1;
    }
    return 0;
}

void stop_watching() {
    if (watch_fd >= 0) inotify_rm_watch(inotify_fd, watch_fd);
    if (inotify_fd >= 0) close(inotify_fd);
    watch_fd = -1;
    inotify_fd = -1;
}
