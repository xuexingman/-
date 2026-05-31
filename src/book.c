#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "utils.h"

Book *createBookNode(const char *isbn, const char *name, const char *author,
                     const char *category, int total, int remain, int borrowCount) {
    Book *node = (Book *)malloc(sizeof(Book));
    if (node == NULL) {
        printf("内存分配失败。\n");
        return NULL;
    }

    strcpy(node->isbn, isbn);
    strcpy(node->name, name);
    strcpy(node->author, author);
    strcpy(node->category, category);
    node->total = total;
    node->remain = remain;
    node->borrowCount = borrowCount;
    node->next = NULL;
    return node;
}

void appendBook(Book **head, Book *node) {
    Book *p;

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

Book *findBookByISBN(Book *head, const char *isbn) {
    Book *p = head;
    while (p != NULL) {
        if (strcmp(p->isbn, isbn) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void addBook(Book **head) {
    char isbn[MAX_ISBN_LEN];
    char name[MAX_NAME_LEN];
    char author[MAX_AUTHOR_LEN];
    char category[MAX_CATEGORY_LEN];
    int total;
    Book *node;

    readString("请输入ISBN：", isbn, MAX_ISBN_LEN);
    if (findBookByISBN(*head, isbn) != NULL) {
        printf("该ISBN已存在，不能重复添加。\n");
        return;
    }

    readString("请输入书名：", name, MAX_NAME_LEN);
    readString("请输入作者：", author, MAX_AUTHOR_LEN);
    readString("请输入分类：", category, MAX_CATEGORY_LEN);
    total = readInt("请输入库存数量：");
    if (total < 0) {
        printf("库存数量不能为负数。\n");
        return;
    }

    node = createBookNode(isbn, name, author, category, total, total, 0);
    appendBook(head, node);
    printf("添加图书成功。\n");
}

void deleteBook(Book **head) {
    char isbn[MAX_ISBN_LEN];
    Book *p = *head;
    Book *prev = NULL;

    readString("请输入要删除的图书ISBN：", isbn, MAX_ISBN_LEN);
    while (p != NULL) {
        if (strcmp(p->isbn, isbn) == 0) {
            if (p->remain != p->total) {
                printf("该图书仍有未归还记录，暂不能删除。\n");
                return;
            }
            if (prev == NULL) {
                *head = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            printf("删除图书成功。\n");
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("未找到该图书。\n");
}

void modifyBook(Book *head) {
    char isbn[MAX_ISBN_LEN];
    Book *book;
    int newTotal;

    readString("请输入要修改的图书ISBN：", isbn, MAX_ISBN_LEN);
    book = findBookByISBN(head, isbn);
    if (book == NULL) {
        printf("未找到该图书。\n");
        return;
    }

    printf("当前信息：%s | %s | %s | 总库存:%d | 剩余:%d\n",
           book->isbn, book->name, book->author, book->total, book->remain);
    readString("请输入新书名：", book->name, MAX_NAME_LEN);
    readString("请输入新作者：", book->author, MAX_AUTHOR_LEN);
    readString("请输入新分类：", book->category, MAX_CATEGORY_LEN);
    newTotal = readInt("请输入新的总库存：");

    if (newTotal < book->total - book->remain) {
        printf("新库存不能小于当前已借出数量。\n");
        return;
    }

    book->remain = book->remain + (newTotal - book->total);
    book->total = newTotal;
    printf("修改图书成功。\n");
}

void showAllBooks(Book *head) {
    Book *p = head;

    printf("\n%-18s %-24s %-16s %-12s %-8s %-8s %-8s\n",
           "ISBN", "书名", "作者", "分类", "总数", "剩余", "借阅次数");
    printf("--------------------------------------------------------------------------------\n");
    while (p != NULL) {
        printf("%-18s %-24s %-16s %-12s %-8d %-8d %-8d\n",
               p->isbn, p->name, p->author, p->category, p->total, p->remain, p->borrowCount);
        p = p->next;
    }
}

void searchBookMenu(Book *head) {
    char isbn[MAX_ISBN_LEN];
    Book *book;

    readString("请输入ISBN：", isbn, MAX_ISBN_LEN);
    book = findBookByISBN(head, isbn);
    if (book == NULL) {
        printf("未找到该图书。\n");
        return;
    }

    printf("ISBN：%s\n书名：%s\n作者：%s\n分类：%s\n总库存：%d\n剩余库存：%d\n借阅次数：%d\n",
           book->isbn, book->name, book->author, book->category,
           book->total, book->remain, book->borrowCount);
}

void fuzzySearchBooks(Book *head) {
    char keyword[MAX_NAME_LEN];
    Book *p = head;
    int count = 0;

    readString("请输入关键词（书名/作者/分类）：", keyword, MAX_NAME_LEN);
    while (p != NULL) {
        if (containsText(p->name, keyword) || containsText(p->author, keyword)
            || containsText(p->category, keyword)) {
            printf("%s | %s | %s | %s | 剩余:%d\n",
                   p->isbn, p->name, p->author, p->category, p->remain);
            count++;
        }
        p = p->next;
    }

    if (count == 0) {
        printf("没有找到匹配图书。\n");
    }
}

void freeBooks(Book *head) {
    Book *p;
    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }
}

