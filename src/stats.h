#ifndef STATS_H
#define STATS_H

#include "book.h"
#include "borrow.h"

void showLowStockBooks(Book *head);
void showHotBooks(Book *head);
void showOverdueRecords(BorrowRecord *head);
void showSystemSummary(Book *bookHead, BorrowRecord *borrowHead);

#endif

