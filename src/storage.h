#ifndef STORAGE_H
#define STORAGE_H

#include "book.h"
#include "borrow.h"

int loadBooks(Book **head, const char *fileName);
int saveBooks(Book *head, const char *fileName);
int loadBorrowRecords(BorrowRecord **head, const char *fileName);
int saveBorrowRecords(BorrowRecord *head, const char *fileName);

#endif

