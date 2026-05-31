#ifndef COMMON_H
#define COMMON_H

#define MAX_ISBN_LEN 30
#define MAX_NAME_LEN 60
#define MAX_AUTHOR_LEN 40
#define MAX_CATEGORY_LEN 30
#define MAX_ID_LEN 30
#define MAX_DATE_LEN 20
#define MAX_LINE_LEN 256

#define BOOK_FILE "books.txt"
#define BORROW_FILE "borrows.txt"

#define LOW_STOCK_LIMIT 2
#define BORROW_DAYS_LIMIT 30

typedef enum {
    BOOL_FALSE = 0,
    BOOL_TRUE = 1
} Bool;

#endif
