#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

void readString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

int readInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("输入格式错误，请重新输入整数：");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

void pauseScreen(void) {
    printf("\n按回车键继续...");
    getchar();
}

void clearScreen(void) {
    system("cls");
}

int containsText(const char *text, const char *keyword) {
    if (keyword[0] == '\0') {
        return 0;
    }
    return strstr(text, keyword) != NULL;
}

int daysBetweenSimple(const char* startDate, const char* endDate) {
    int sy, sm, sd;
    int ey, em, ed;
    struct tm start = { 0 };
    struct tm end = { 0 };
    time_t startTime;
    time_t endTime;

    if (sscanf(startDate, "%d-%d-%d", &sy, &sm, &sd) != 3) {
        return 0;
    }
    if (sscanf(endDate, "%d-%d-%d", &ey, &em, &ed) != 3) {
        return 0;
    }

    start.tm_year = sy - 1900;
    start.tm_mon = sm - 1;
    start.tm_mday = sd;

    end.tm_year = ey - 1900;
    end.tm_mon = em - 1;
    end.tm_mday = ed;

    startTime = mktime(&start);
    endTime = mktime(&end);

    return (int)((endTime - startTime) / (24 * 60 * 60));
}

void getTodayString(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d", local);
}
