#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_ISBN 20
#define TABLE_SIZE 100

typedef struct Book {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char isbn[MAX_ISBN];
    int isIssued;
    char studentId[20];
    char dueDate[20];
    struct Book *next;
} Book;

Book *table[TABLE_SIZE];
int nextId = 1;

void inputString(char *str, int size) {
    scanf(" %[^\n]", str);
}

int hash(char *isbn) {
    int sum = 0;
    for (int i = 0; isbn[i] != '\0'; i++)
        sum += isbn[i];
    return sum % TABLE_SIZE;
}

Book* search(char *isbn, int *bucket, Book **prev) {
    int h = hash(isbn);
    *bucket = h;
    *prev = NULL;
    Book *cur = table[h];
    while (cur != NULL) {
        if (strcmp(cur->isbn, isbn) == 0)
            return cur;
        *prev = cur;
        cur = cur->next;
    }
    return NULL;
}

void addBook() {
    char title[MAX_TITLE], author[MAX_AUTHOR], isbn[MAX_ISBN];
    printf("Enter title: ");
    inputString(title, MAX_TITLE);
    printf("Enter author: ");
    inputString(author, MAX_AUTHOR);

    for (int i = 0; author[i] != '\0'; i++) {
        if (!((author[i] >= 'A' && author[i] <= 'Z') ||
              (author[i] >= 'a' && author[i] <= 'z') ||
              author[i] == ' ')) {
            printf("Invalid author name! Only alphabets allowed.\n");
            return;
        }
    }
    printf("Enter ISBN: ");
    scanf("%s", isbn);
    int bucket;
    Book *prev;
    if (search(isbn, &bucket, &prev) != NULL) {
        printf("Book with this ISBN already exists.\n");
        return;
    }
    Book *b = malloc(sizeof(Book));
    b->id = nextId++;
    strcpy(b->title, title);
    strcpy(b->author, author);
    strcpy(b->isbn, isbn);
    b->isIssued = 0;
    b->studentId[0] = '\0';
    b->dueDate[0] = '\0';
    b->next = table[bucket];
    table[bucket] = b;
    printf("Book added successfully.\n");
}

void updateBook() {
    char isbn[MAX_ISBN];
    printf("Enter ISBN to update: ");
    scanf("%s", isbn);
    int bucket;
    Book *prev;
    Book *b = search(isbn, &bucket, &prev);
    if (!b) {
        printf("Book not found.\n");
        return;
    }
    printf("Enter new title: ");
    inputString(b->title, MAX_TITLE);
    printf("Enter new author: ");
    inputString(b->author, MAX_AUTHOR);

    for (int i = 0; b->author[i] != '\0'; i++) {
        if (!((b->author[i] >= 'A' && b->author[i] <= 'Z') ||
              (b->author[i] >= 'a' && b->author[i] <= 'z') ||
              b->author[i] == ' ')) {
            printf("Invalid author name! Only alphabets allowed.\n");
            return;
        }
    }
    printf("Book updated successfully.\n");
}

void deleteBook() {
    char isbn[MAX_ISBN];
    printf("Enter ISBN to delete: ");
    scanf("%s", isbn);
    int bucket;
    Book *prev;
    Book *b = search(isbn, &bucket, &prev);
    if (!b) {
        printf("Book not found.\n");
        return;
    }
    if (prev == NULL)
        table[bucket] = b->next;
    else
        prev->next = b->next;
    printf("Deleting book: %s\n", b->title);
    free(b);
    printf("Book deleted successfully.\n");
}

void displayBooks() {
    printf("\n--- All Books ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Book *cur = table[i];
        while (cur != NULL) {
            printf("ID: %d | %s | %s | ISBN: %s | Status: %s",
                cur->id, cur->title, cur->author, cur->isbn,
                cur->isIssued ? "ISSUED" : "AVAILABLE");
            if (cur->isIssued)
                printf(" | Student: %s | Due: %s", cur->studentId, cur->dueDate);
            printf("\n");
            cur = cur->next;
        }
    }
}

Book* searchByTitle(char *title) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Book *cur = table[i];
        while (cur != NULL) {
            if (strcasecmp(cur->title, title) == 0)
                return cur;
            cur = cur->next;
        }
    }
    return NULL;
}

void searchByAuthor(char *author) {
    int found = 0;
    printf("\n--- Books by %s ---\n", author);
    for (int i = 0; i < TABLE_SIZE; i++) {
        Book *cur = table[i];
        while (cur != NULL) {
            if (strcasecmp(cur->author, author) == 0) {
                found = 1;
                printf("ID: %d | %s | ISBN: %s | Status: %s\n",
                    cur->id, cur->title, cur->isbn,
                    cur->isIssued ? "ISSUED" : "AVAILABLE");
            }
            cur = cur->next;
        }
    }
    if (!found)
        printf("No books found.\n");
}

void searchBook() {
    int choice;
    printf("\nSearch by:\n1. ISBN\n2. Title\n3. Author\nChoose: ");
    scanf("%d", &choice);
    if (choice == 1) {
        char isbn[MAX_ISBN];
        printf("Enter ISBN: ");
        scanf("%s", isbn);
        int bucket; Book *prev;
        Book *b = search(isbn, &bucket, &prev);
        if (!b) printf("Book not found.\n");
        else
            printf("Found: %s | %s | %s\n", b->title, b->author, b->isbn);
    } else if (choice == 2) {
        char title[MAX_TITLE];
        printf("Enter title: ");
        inputString(title, MAX_TITLE);
        Book *b = searchByTitle(title);
        if (!b) printf("Book not found.\n");
        else printf("Found: %s | %s | %s\n", b->title, b->author, b->isbn);
    } else if (choice == 3) {
        char author[MAX_AUTHOR];
        printf("Enter author: ");
        inputString(author, MAX_AUTHOR);
        searchByAuthor(author);
    }
}

void issueBook() {
    char isbn[MAX_ISBN];
    printf("Enter ISBN to issue: ");
    scanf("%s", isbn);
    int bucket; Book *prev;
    Book *b = search(isbn, &bucket, &prev);
    if (!b) {
        printf("Book not found.\n");
        return;
    }
    if (b->isIssued) {
        printf("Book already issued.\n");
        return;
    }
    printf("Enter student ID: ");
    scanf("%s", b->studentId);
    printf("Enter due date (DD/MM/YYYY): ");
    scanf("%s", b->dueDate);
    b->isIssued = 1;
    printf("Book issued successfully.\n");
}

void returnBook() {
    char isbn[MAX_ISBN];
    printf("Enter ISBN to return: ");
    scanf("%s", isbn);
    int bucket; Book *prev;
    Book *b = search(isbn, &bucket, &prev);
    if (!b) {
        printf("Book not found.\n");
        return;
    }
    if (!b->isIssued) {
        printf("Book is not issued.\n");
        return;
    }
    b->isIssued = 0;
    b->studentId[0] = '\0';
    b->dueDate[0] = '\0';
    printf("Book returned successfully.\n");
}

int dateToDays(int d, int m, int y) {
    return y * 365 + m * 30 + d;
}

void checkOverdueBooks() {
    char currentDate[20];
    float baseFee;
    printf("Enter today's date (DD/MM/YYYY): ");
    scanf("%s", currentDate);
    printf("Enter base fee per day: ");
    scanf("%f", &baseFee);
    int cd, cm, cy;
    if (sscanf(currentDate, "%d/%d/%d", &cd, &cm, &cy) != 3) {
        printf("Invalid date format.\n");
        return;
    }
    int today = dateToDays(cd, cm, cy);
    printf("\n--- Overdue Books ---\n");
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Book *cur = table[i];
        while (cur != NULL) {
            if (cur->isIssued) {
                int dd, mm, yy;
                if (sscanf(cur->dueDate, "%d/%d/%d", &dd, &mm, &yy) != 3) {
                    cur = cur->next;
                    continue;
                }
                int due = dateToDays(dd, mm, yy);
                if (today > due) {
                    found = 1;
                    int daysLate = today - due;
                    float fine = daysLate * baseFee;
                    printf("Book: %s | Student: %s | Late: %d days | Fine: %.2f\n",
                        cur->title, cur->studentId, daysLate, fine);
                }
            }
            cur = cur->next;
        }
    }
    if (!found)
        printf("No overdue books.\n");
}

int main() {
    int choice;
    do {
        printf("\n===== LIBRARY SYSTEM =====\n");
        printf("1. Add Book\n");
        printf("2. Update Book\n");
        printf("3. Delete Book\n");
        printf("4. Display Books\n");
        printf("5. Search Book\n");
        printf("6. Issue Book\n");
        printf("7. Return Book\n");
        printf("8. Check Overdue\n");
        printf("0. Exit\nChoose: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addBook(); break;
            case 2: updateBook(); break;
            case 3: deleteBook(); break;
            case 4: displayBooks(); break;
            case 5: searchBook(); break;
            case 6: issueBook(); break;
            case 7: returnBook(); break;
            case 8: checkOverdueBooks(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}