#ifndef BOOK_H
#define BOOK_H

#include "common.h"

typedef struct Book {
    char isbn[MAX_ISBN_LEN];
    char name[MAX_NAME_LEN];
    char author[MAX_AUTHOR_LEN];
    char category[MAX_CATEGORY_LEN];
    int total;
    int remain;
    int borrowCount;
    struct Book *next;
} Book;

Book *createBookNode(const char *isbn, const char *name, const char *author,
                     const char *category, int total, int remain, int borrowCount);
void appendBook(Book **head, Book *node);
void addBook(Book **head);
void deleteBook(Book **head);
void modifyBook(Book *head);
void showAllBooks(Book *head);
void searchBookMenu(Book *head);
Book *findBookByISBN(Book *head, const char *isbn);
void fuzzySearchBooks(Book *head);
void freeBooks(Book *head);

#endif

