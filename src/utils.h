#ifndef UTILS_H
#define UTILS_H

#include "common.h"

void clearInputBuffer(void);
void readString(const char *prompt, char *buffer, int size);
int readInt(const char *prompt);
void pauseScreen(void);
void clearScreen(void);
int containsText(const char *text, const char *keyword);
int daysBetweenSimple(const char *startDate, const char *endDate);
void getTodayString(char *buffer, int size);

#endif

