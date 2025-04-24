#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>

static int kq = -1;
static int fd = -1;
static int file_changed_flag = 0;
static pthread_t watcher_thread;

static char watch_path[1024] = {0};

void* watcher_func(void* arg) {
    struct kevent event;
    while (1) {
        int nev = kevent(kq, NULL, 0, &event, 1, NULL);
        if (nev < 0) {
            perror("kevent");
            break;
        } else if (nev > 0) {
            if (event.filter == EVFILT_VNODE) {
                if (event.fflags & (NOTE_WRITE | NOTE_EXTEND | NOTE_ATTRIB)) {
                    file_changed_flag = 1;
                }
            }
        }
    }
    return NULL;
}

void watch_file(const char* path) {
    if (fd >= 0) {
        close(fd);
        fd = -1;
    }
    if (kq >= 0) {
        close(kq);
        kq = -1;
    }
    file_changed_flag = 0;

    strncpy(watch_path, path, sizeof(watch_path)-1);
    watch_path[sizeof(watch_path)-1] = '\0';

    fd = open(watch_path, O_EVTONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    kq = kqueue();
    if (kq < 0) {
        perror("kqueue");
        close(fd);
        fd = -1;
        return;
    }

    struct kevent change;
    EV_SET(&change, fd, EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_WRITE | NOTE_EXTEND | NOTE_ATTRIB, 0, NULL);

    if (kevent(kq, &change, 1, NULL, 0, NULL) < 0) {
        perror("kevent register");
        close(fd);
        close(kq);
        fd = -1;
        kq = -1;
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
    if (fd >= 0) close(fd);
    if (kq >= 0) close(kq);
    fd = -1;
    kq = -1;
}
