#include <stdio.h>
#include <stdlib.h>

struct books {
    int id;
    char bookName[50];
    char authorName[50];
} b;

struct student {
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
} s;

FILE *fp;

void clr() {
    system("cls");
}

void addBook() {
    fp = fopen("books1.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("Book Added Successfully\n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

void booksList() {
    clr();
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s\n\n", "Book id", "Book Name", "Author");

    fp = fopen("books1.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("%-10d %-30s %-20s\n", b.id, b.bookName, b.authorName);
    }

    fclose(fp);
}

void del() {
    int id, f = 0;
    clr();
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books1.txt", "rb");
    ft = fopen("temp1.txt", "wb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (id == b.id) {
            f = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nDeleted Successfully.\n");
    } else {
        printf("\n\nRecord Not Found !\n");
    }

    fclose(fp);
    fclose(ft);

    remove("books1.txt");
    rename("temp1.txt", "books1.txt");
}

void issueBook() {
    int f = 0;
    clr();
    printf("<== Issue Books ==>\n\n");
    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    // Check if we have a book with the given id
    fp = fopen("books1.txt", "rb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id == s.id) {
            strcpy(s.bookName, b.bookName);
            f = 1;
            break;
        }
    }

    if (f == 0) {
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue1.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList() {
    clr();
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s\n\n", "S.id", "Name", "Class", "Roll", "Book Name");

    fp = fopen("issue1.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %-10d %-30s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName);
    }

    fclose(fp);
}
void game(){
    clr();
    int userChoice, computerChoice, result;
    char playAgain;
    do {
        // Get user's choice
        printf("Enter your choice (0 for Rock, 1 for Paper, 2 for Scissors): ");
        scanf("%d", &userChoice);

        // Generate computer's choice
        computerChoice = rand() % 3;

        // Print choices
        printf("You chose: ");
        if (userChoice == 0)
            printf("Rock\n");
        else if (userChoice == 1)
            printf("Paper\n");
        else
            printf("Scissors\n");

        printf("Computer chose: ");
        if (computerChoice == 0)
            printf("Rock\n");
        else if (computerChoice == 1)
            printf("Paper\n");
        else
            printf("Scissors\n");

        // Determine the winner
        if (userChoice == computerChoice)
            printf("It's a tie!\n");
        else if ((userChoice == 0 && computerChoice == 2) ||
                 (userChoice == 1 && computerChoice == 0) ||
                 (userChoice == 2 && computerChoice == 1))
            printf("You win!\n");
        else
            printf("Computer wins!\n");

        // Ask if the user wants to play again
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'Y' || playAgain == 'y');

    return 0;
}

int main() {
    int ch;

    while (1) {
        clr();
        printf("<== Library Management System ==>\n");
        printf("1.Add Book\n");
        printf("2.Books List\n");
        printf("3.Remove Book\n");
        printf("4.Issue Book\n");
        printf("5.Issued Book List\n");
        printf("6.Entertainment \n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 0:
                exit(0);

            case 1:
                addBook();
                break;

            case 2:
                booksList();
                break;

            case 3:
                del();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                issueList();
                break;
            case 6:
                game();
                break;
            default:
                printf("Invalid Choice...\n\n");
        }
        printf("Press Any Key To Continue...");
        getch();
    }

    return 0;
}


