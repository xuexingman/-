#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "borrow.h"
#include "utils.h"

BorrowRecord *createBorrowNode(const char *recordId, const char *studentId,
                               const char *studentName, const char *isbn,
                               const char *borrowDate, const char *returnDate,
                               int returned) {
    BorrowRecord *node = (BorrowRecord *)malloc(sizeof(BorrowRecord));
    if (node == NULL) {
        printf("内存分配失败。\n");
        return NULL;
    }

    strcpy(node->recordId, recordId);
    strcpy(node->studentId, studentId);
    strcpy(node->studentName, studentName);
    strcpy(node->isbn, isbn);
    strcpy(node->borrowDate, borrowDate);
    strcpy(node->returnDate, returnDate);
    node->returned = returned;
    node->next = NULL;
    return node;
}

void appendBorrowRecord(BorrowRecord **head, BorrowRecord *node) {
    BorrowRecord *p;

    if (node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = node;
        return;
    }

    p = *head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = node;
}

BorrowRecord *findUnreturnedRecord(BorrowRecord *head, const char *studentId, const char *isbn) {
    BorrowRecord *p = head;
    while (p != NULL) {
        if (strcmp(p->studentId, studentId) == 0 && strcmp(p->isbn, isbn) == 0 && p->returned == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void borrowBook(Book *bookHead, BorrowRecord **borrowHead) {
    char isbn[MAX_ISBN_LEN];
    char studentId[MAX_ID_LEN];
    char studentName[MAX_NAME_LEN];
    char date[MAX_DATE_LEN];
    char recordId[MAX_ID_LEN];
    Book *book;
    BorrowRecord *record;
    static int idSeed = 1000;

    readString("请输入借阅图书ISBN：", isbn, MAX_ISBN_LEN);
    book = findBookByISBN(bookHead, isbn);
    if (book == NULL) {
        printf("图书不存在。\n");
        return;
    }
    if (book->remain <= 0) {
        printf("该图书库存不足，无法借阅。\n");
        return;
    }

    readString("请输入学号：", studentId, MAX_ID_LEN);
    if (findUnreturnedRecord(*borrowHead, studentId, isbn) != NULL) {
        printf("该学生已借阅此书且尚未归还，不能重复借阅。\n");
        return;
    }

    readString("请输入姓名：", studentName, MAX_NAME_LEN);
    readString("请输入借阅日期（如2026-05-28）：", date, MAX_DATE_LEN);
    sprintf(recordId, "R%d", idSeed++);

    record = createBorrowNode(recordId, studentId, studentName, isbn, date, "-", 0);
    appendBorrowRecord(borrowHead, record);
    book->remain--;
    book->borrowCount++;
    printf("借书成功，借阅编号：%s\n", recordId);
}

void returnBook(Book *bookHead, BorrowRecord *borrowHead) {
    char isbn[MAX_ISBN_LEN];
    char studentId[MAX_ID_LEN];
    char returnDate[MAX_DATE_LEN];
    Book *book;
    BorrowRecord *record;

    readString("请输入归还图书ISBN：", isbn, MAX_ISBN_LEN);
    readString("请输入学号：", studentId, MAX_ID_LEN);

    record = findUnreturnedRecord(borrowHead, studentId, isbn);
    if (record == NULL) {
        printf("未找到未归还的借阅记录。\n");
        return;
    }

    book = findBookByISBN(bookHead, isbn);
    if (book != NULL) {
        book->remain++;
    }

    readString("请输入归还日期（如2026-06-01）：", returnDate, MAX_DATE_LEN);
    strcpy(record->returnDate, returnDate);
    record->returned = 1;
    printf("还书成功。\n");
}

void showAllBorrowRecords(BorrowRecord *head) {
    BorrowRecord *p = head;

    printf("\n%-10s %-14s %-12s %-18s %-14s %-14s %-8s\n",
           "编号", "学号", "姓名", "ISBN", "借阅日期", "归还日期", "状态");
    printf("--------------------------------------------------------------------------------\n");
    while (p != NULL) {
        printf("%-10s %-14s %-12s %-18s %-14s %-14s %-8s\n",
               p->recordId, p->studentId, p->studentName, p->isbn,
               p->borrowDate, p->returnDate, p->returned ? "已归还" : "未归还");
        p = p->next;
    }
}

void searchBorrowByStudent(BorrowRecord *head) {
    char studentId[MAX_ID_LEN];
    BorrowRecord *p = head;
    int count = 0;

    readString("请输入学号：", studentId, MAX_ID_LEN);
    while (p != NULL) {
        if (strcmp(p->studentId, studentId) == 0) {
            printf("%s | %s | ISBN:%s | 借:%s | 还:%s | %s\n",
                   p->recordId, p->studentName, p->isbn, p->borrowDate,
                   p->returnDate, p->returned ? "已归还" : "未归还");
            count++;
        }
        p = p->next;
    }

    if (count == 0) {
        printf("没有找到该学生的借阅记录。\n");
    }
}

void freeBorrowRecords(BorrowRecord *head) {
    BorrowRecord *p;
    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }
}

