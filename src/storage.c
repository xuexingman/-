#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

int loadBooks(Book **head, const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    char isbn[MAX_ISBN_LEN];
    char name[MAX_NAME_LEN];
    char author[MAX_AUTHOR_LEN];
    char category[MAX_CATEGORY_LEN];
    int total;
    int remain;
    int borrowCount;

    if (fp == NULL) {
        return 0;
    }

    while (fscanf(fp, "%29[^|]|%59[^|]|%39[^|]|%29[^|]|%d|%d|%d\n",
                  isbn, name, author, category, &total, &remain, &borrowCount) == 7) {
        appendBook(head, createBookNode(isbn, name, author, category, total, remain, borrowCount));
    }

    fclose(fp);
    return 1;
}

int saveBooks(Book *head, const char *fileName) {
    FILE *fp = fopen(fileName, "w");
    Book *p = head;

    if (fp == NULL) {
        printf("保存图书文件失败。\n");
        return 0;
    }

    while (p != NULL) {
        fprintf(fp, "%s|%s|%s|%s|%d|%d|%d\n",
                p->isbn, p->name, p->author, p->category,
                p->total, p->remain, p->borrowCount);
        p = p->next;
    }

    fclose(fp);
    return 1;
}

int loadBorrowRecords(BorrowRecord **head, const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    char recordId[MAX_ID_LEN];
    char studentId[MAX_ID_LEN];
    char studentName[MAX_NAME_LEN];
    char isbn[MAX_ISBN_LEN];
    char borrowDate[MAX_DATE_LEN];
    char returnDate[MAX_DATE_LEN];
    int returned;

    if (fp == NULL) {
        return 0;
    }

    while (fscanf(fp, "%29[^|]|%29[^|]|%59[^|]|%29[^|]|%19[^|]|%19[^|]|%d\n",
                  recordId, studentId, studentName, isbn, borrowDate, returnDate, &returned) == 7) {
        appendBorrowRecord(head, createBorrowNode(recordId, studentId, studentName,
                                                  isbn, borrowDate, returnDate, returned));
    }

    fclose(fp);
    return 1;
}

int saveBorrowRecords(BorrowRecord *head, const char *fileName) {
    FILE *fp = fopen(fileName, "w");
    BorrowRecord *p = head;

    if (fp == NULL) {
        printf("保存借阅文件失败。\n");
        return 0;
    }

    while (p != NULL) {
        fprintf(fp, "%s|%s|%s|%s|%s|%s|%d\n",
                p->recordId, p->studentId, p->studentName, p->isbn,
                p->borrowDate, p->returnDate, p->returned);
        p = p->next;
    }

    fclose(fp);
    return 1;
}

