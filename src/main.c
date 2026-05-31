#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "borrow.h"
#include "storage.h"
#include "stats.h"
#include "utils.h"

static void showMainMenu(void) {
    printf("\n========== 图书借阅管理系统 ==========\n");
    printf("1. 图书信息管理\n");
    printf("2. 借阅归还管理\n");
    printf("3. 查询与统计分析\n");
    printf("4. 保存数据\n");
    printf("0. 退出系统\n");
    printf("======================================\n");
}

static void showBookMenu(void) {
    printf("\n---------- 图书信息管理 ----------\n");
    printf("1. 添加图书\n");
    printf("2. 删除图书\n");
    printf("3. 修改图书\n");
    printf("4. 按ISBN查询\n");
    printf("5. 关键词模糊查询\n");
    printf("6. 显示全部图书\n");
    printf("0. 返回上级菜单\n");
}

static void showBorrowMenu(void) {
    printf("\n---------- 借阅归还管理 ----------\n");
    printf("1. 借书\n");
    printf("2. 还书\n");
    printf("3. 显示全部借阅记录\n");
    printf("4. 按学生查询借阅记录\n");
    printf("0. 返回上级菜单\n");
}

static void showStatsMenu(void) {
    printf("\n---------- 查询与统计分析 ----------\n");
    printf("1. 系统概览\n");
    printf("2. 库存不足预警\n");
    printf("3. 热门图书排行\n");
    printf("4. 超期未还提醒\n");
    printf("0. 返回上级菜单\n");
}

static void handleBookMenu(Book **bookHead) {
    int choice;
    do {
        showBookMenu();
        choice = readInt("请选择：");
        switch (choice) {
        case 1:
            addBook(bookHead);
            break;
        case 2:
            deleteBook(bookHead);
            break;
        case 3:
            modifyBook(*bookHead);
            break;
        case 4:
            searchBookMenu(*bookHead);
            break;
        case 5:
            fuzzySearchBooks(*bookHead);
            break;
        case 6:
            showAllBooks(*bookHead);
            break;
        case 0:
            break;
        default:
            printf("选择无效，请重新输入。\n");
        }
        if (choice != 0) {
            pauseScreen();
        }
    } while (choice != 0);
}

static void handleBorrowMenu(Book *bookHead, BorrowRecord **borrowHead) {
    int choice;
    do {
        showBorrowMenu();
        choice = readInt("请选择：");
        switch (choice) {
        case 1:
            borrowBook(bookHead, borrowHead);
            break;
        case 2:
            returnBook(bookHead, *borrowHead);
            break;
        case 3:
            showAllBorrowRecords(*borrowHead);
            break;
        case 4:
            searchBorrowByStudent(*borrowHead);
            break;
        case 0:
            break;
        default:
            printf("选择无效，请重新输入。\n");
        }
        if (choice != 0) {
            pauseScreen();
        }
    } while (choice != 0);
}

static void handleStatsMenu(Book *bookHead, BorrowRecord *borrowHead) {
    int choice;
    do {
        showStatsMenu();
        choice = readInt("请选择：");
        switch (choice) {
        case 1:
            showSystemSummary(bookHead, borrowHead);
            break;
        case 2:
            showLowStockBooks(bookHead);
            break;
        case 3:
            showHotBooks(bookHead);
            break;
        case 4:
            showOverdueRecords(borrowHead);
            break;
        case 0:
            break;
        default:
            printf("选择无效，请重新输入。\n");
        }
        if (choice != 0) {
            pauseScreen();
        }
    } while (choice != 0);
}

int main(void) {
    Book *bookHead = NULL;
    BorrowRecord *borrowHead = NULL;
    int choice;

    system("chcp 65001 > nul");

    loadBooks(&bookHead, BOOK_FILE);
    loadBorrowRecords(&borrowHead, BORROW_FILE);

    do {
        showMainMenu();
        choice = readInt("请选择：");
        switch (choice) {
        case 1:
            handleBookMenu(&bookHead);
            break;
        case 2:
            handleBorrowMenu(bookHead, &borrowHead);
            break;
        case 3:
            handleStatsMenu(bookHead, borrowHead);
            break;
        case 4:
            saveBooks(bookHead, BOOK_FILE);
            saveBorrowRecords(borrowHead, BORROW_FILE);
            printf("数据保存成功。\n");
            pauseScreen();
            break;
        case 0:
            saveBooks(bookHead, BOOK_FILE);
            saveBorrowRecords(borrowHead, BORROW_FILE);
            printf("数据已保存，欢迎下次使用。\n");
            break;
        default:
            printf("选择无效，请重新输入。\n");
            pauseScreen();
        }
    } while (choice != 0);

    freeBooks(bookHead);
    freeBorrowRecords(borrowHead);
    return 0;
}
