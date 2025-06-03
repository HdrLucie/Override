#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void log_wrapper(FILE *logFile, char *message, char *filename) {
    char buffer[264];
    strcpy(buffer, message);
    size_t messageLen = strlen(buffer);
    snprintf(buffer + messageLen, 0xfe - messageLen, "%s", filename);
    size_t newlinePos = strcspn(buffer, "\n");
    buffer[newlinePos] = '\0';
    fprintf(logFile, "LOG: %s\n", buffer);
}

int main(int argc, char **argv) {
    FILE *logFile;
    FILE *inputFile;
    int outputFd;
    char outputPath[104];
    char ch;
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }
    logFile = fopen("./backups/.log", "w");
    if (logFile == NULL) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }
    log_wrapper(logFile, "Starting back up: ", argv[1]);
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }
    strncpy(outputPath, "./backups/", 11);
    size_t prefixLen = strlen(outputPath);
    strncat(outputPath, argv[1], 99 - prefixLen);
    outputFd = open(outputPath, O_CREAT | O_WRONLY | O_TRUNC, 0660);
    if (outputFd < 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
    }
    int c;
    while ((c = fgetc(inputFile)) != EOF) {
        ch = (char)c;
        write(outputFd, &ch, 1);
    }
    log_wrapper(logFile, "Finished back up ", argv[1]);
    
    fclose(inputFile);
    close(outputFd);
    fclose(logFile);
    return 0;
}
