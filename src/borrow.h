#ifndef BORROW_H
#define BORROW_H

#include "book.h"
#include "common.h"

typedef struct BorrowRecord {
    char recordId[MAX_ID_LEN];
    char studentId[MAX_ID_LEN];
    char studentName[MAX_NAME_LEN];
    char isbn[MAX_ISBN_LEN];
    char borrowDate[MAX_DATE_LEN];
    char returnDate[MAX_DATE_LEN];
    int returned;
    struct BorrowRecord *next;
} BorrowRecord;

BorrowRecord *createBorrowNode(const char *recordId, const char *studentId,
                               const char *studentName, const char *isbn,
                               const char *borrowDate, const char *returnDate,
                               int returned);
void appendBorrowRecord(BorrowRecord **head, BorrowRecord *node);
void borrowBook(Book *bookHead, BorrowRecord **borrowHead);
void returnBook(Book *bookHead, BorrowRecord *borrowHead);
void showAllBorrowRecords(BorrowRecord *head);
void searchBorrowByStudent(BorrowRecord *head);
BorrowRecord *findUnreturnedRecord(BorrowRecord *head, const char *studentId, const char *isbn);
void freeBorrowRecords(BorrowRecord *head);

#endif

