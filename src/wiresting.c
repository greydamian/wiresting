/*
 * Copyright (c) 2014 Damian Jason Lapidge
 *
 * The contents of this file are subject to the terms and conditions defined 
 * within the file LICENSE.txt, located within this project's root directory.
 */

/*
 * stdio.h : stderr, fprintf()
 * unistd.h: geteuid(), close()
 * fcntl.h : O_RDONLY, open()
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * pcap.h: PCAP_ERRBUF_SIZE, pcap_t, pcap_create(), pcap_activate(), 
 *         pcap_inject(), pcap_close(), pcap_perror()
 */
#include <pcap/pcap.h>

/*
 * stdlib.h: free()
 * greyio.h: readall()
 */
#include <stdlib.h>
#include "greyio.h"

static const char *version = "v1.0.0";
static const char *authors = "Damian Jason Lapidge <grey@greydamian.org>";

void print_usage() {
    fprintf(stderr, "usage: wiresting <file> <interface>\n");
}

int main(int argc, char *argv[]) {
    if (geteuid() > 0) {
        fprintf(stderr, "error: this program requires superuser privilages\n");
        return 1; /* exit failure */
    }

    if (argc < 3) {
        print_usage();
        return 1; /* exit failure */
    }

    char *fpath = argv[argc - 2];
    char *iface = argv[argc - 1];

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "error: failure to open file (%s)\n", fpath);
        return 1; /* exit failure */
    }

    char *buf = NULL;
    ssize_t rbytes = readall(fd, (void **)&buf);
    if (rbytes == -1) {
        fprintf(stderr, "error: failure reading from file\n");
        return 1; /* exit failure */
    }
    close(fd); /* no further use for file descriptor */

    pcap_t *pcap_handle = NULL;
    char    pcap_errbuf[PCAP_ERRBUF_SIZE];

    pcap_handle = pcap_create(iface, pcap_errbuf);
    if (pcap_handle == NULL) {
        fprintf(stderr, "error: failure to create network connection\n");
        return 1; /* exit failure */
    }

    if (pcap_activate(pcap_handle) != 0) {
        fprintf(stderr, "error: failure to create network connection\n");
        return 1; /* exit failure */
    }

    int wbytes = 0, wtotal = 0;
    while (wtotal < rbytes) {
        wbytes = pcap_inject(pcap_handle, buf + wtotal, rbytes - wtotal);
        if (wbytes == -1) {
            fprintf(stderr, "error: failure writing bytes to network\n");
            return 1; /* exit failure */
        }
        wtotal += wbytes;
    }

    pcap_close(pcap_handle);

    free(buf);

    return 0; /* exit success */
}

