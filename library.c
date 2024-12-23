/*
 * writelog.h
 * Header file for writelog library
 */

#ifndef WRITELOG_H
#define WRITELOG_H

#include <stdio.h>
#include <time.h>

// Function to initialize the log file
void init_log(const char *filename);

// Function to write message to the log file
void write_log(const char *message);

// Function to close the log file
void close_log();

#endif // WRITELOG_H


/*
 * writelog.c
 * Implementation of writelog library
 */

#include "writelog.h"

static FILE *log_file = NULL;

void init_log(const char *filename) {
    log_file = fopen(filename, "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
    }
}

void write_log(const char *message) {
    if (log_file == NULL) {
        fprintf(stderr, "Log file not initialized. Call init_log() first.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    fprintf(log_file, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
            local_time->tm_year + 1900,
            local_time->tm_mon + 1,
            local_time->tm_mday,
            local_time->tm_hour,
            local_time->tm_min,
            local_time->tm_sec,
            message);
    fflush(log_file);
}

void close_log() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}
