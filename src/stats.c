#include <stdio.h>
#include <string.h>
#include "stats.h"
#include "utils.h"

void showLowStockBooks(Book *head) {
    Book *p = head;
    int count = 0;

    printf("\n库存预警（剩余库存 <= %d）\n", LOW_STOCK_LIMIT);
    while (p != NULL) {
        if (p->remain <= LOW_STOCK_LIMIT) {
            printf("%s | %s | 剩余:%d | 总数:%d\n", p->isbn, p->name, p->remain, p->total);
            count++;
        }
        p = p->next;
    }

    if (count == 0) {
        printf("暂无库存不足图书。\n");
    }
}

void showHotBooks(Book *head) {
    Book *p;
    int rank;

    printf("\n热门图书排行（按借阅次数）\n");
    for (rank = 1; rank <= 3; rank++) {
        Book *best = NULL;
        p = head;
        while (p != NULL) {
            if ((best == NULL || p->borrowCount > best->borrowCount) && p->borrowCount >= 0) {
                best = p;
            }
            p = p->next;
        }

        if (best != NULL) {
            printf("第%d名：%s | %s | 借阅%d次\n", rank, best->isbn, best->name, best->borrowCount);
            best->borrowCount = -best->borrowCount - 1;
        }
    }

    p = head;
    while (p != NULL) {
        if (p->borrowCount < 0) {
            p->borrowCount = -p->borrowCount - 1;
        }
        p = p->next;
    }
}

void showOverdueRecords(BorrowRecord *head) {
    char today[MAX_DATE_LEN];
    BorrowRecord *p = head;
    int count = 0;
    int days;

    readString("请输入当前日期（如2026-06-30）：", today, MAX_DATE_LEN);
    while (p != NULL) {
        if (p->returned == 0) {
            days = daysBetweenSimple(p->borrowDate, today);
            if (days > BORROW_DAYS_LIMIT) {
                printf("超期：%s | %s | ISBN:%s | 已借%d天\n",
                       p->studentId, p->studentName, p->isbn, days);
                count++;
            }
        }
        p = p->next;
    }

    if (count == 0) {
        printf("暂无超期未还记录。\n");
    }
}

void showSystemSummary(Book *bookHead, BorrowRecord *borrowHead) {
    int bookKinds = 0;
    int totalBooks = 0;
    int remainBooks = 0;
    int borrowRecords = 0;
    int unreturned = 0;
    Book *b = bookHead;
    BorrowRecord *r = borrowHead;

    while (b != NULL) {
        bookKinds++;
        totalBooks += b->total;
        remainBooks += b->remain;
        b = b->next;
    }

    while (r != NULL) {
        borrowRecords++;
        if (r->returned == 0) {
            unreturned++;
        }
        r = r->next;
    }

    printf("\n系统概览\n");
    printf("图书种类：%d\n", bookKinds);
    printf("馆藏总量：%d\n", totalBooks);
    printf("当前库存：%d\n", remainBooks);
    printf("借阅记录：%d\n", borrowRecords);
    printf("未归还数：%d\n", unreturned);
}

