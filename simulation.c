#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_SIZE 100


typedef struct Node {
    char url[URL_SIZE];
    struct Node *prev;
    struct Node *next;
} Node;


typedef struct Browser {
    Node *current;   
} Browser;


Node* createNode(const char *url) {
    Node *n = (Node*)malloc(sizeof(Node));
    strcpy(n->url, url);
    n->prev = n->next = NULL;
    return n;
}


void initBrowser(Browser *b) {
    b->current = NULL;
}


void visitPage(Browser *b, const char *url) {
    Node *newPage = createNode(url);

  
    if (b->current != NULL) {
        b->current->next = newPage;
        newPage->prev = b->current;
    }

    b->current = newPage;
    printf("Visited: %s\n", url);
}


void goBack(Browser *b) {
    if (b->current == NULL || b->current->prev == NULL) {
        printf("No previous page!\n");
        return;
    }
    b->current = b->current->prev;
    printf("Back to: %s\n", b->current->url);
}


void goForward(Browser *b) {
    if (b->current == NULL || b->current->next == NULL) {
        printf("No forward page!\n");
        return;
    }
    b->current = b->current->next;
    printf("Forward to: %s\n", b->current->url);
}


void showHistory(Browser *b) {
    if (b->current == NULL) {
        printf("No browsing history!\n");
        return;
    }

  
    Node *temp = b->current;
    while (temp->prev != NULL)
        temp = temp->prev;

    printf("\n--- FULL BROWSING HISTORY ---\n");
    while (temp != NULL) {
        printf("%s\n", temp->url);
        temp = temp->next;
    }
    printf("------------------------------\n");
}


void clearHistory(Browser *b) {
    Node *temp = b->current;

    
    while (temp && temp->prev)
        temp = temp->prev;

    
    while (temp) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }

    b->current = NULL;
    printf("History cleared!\n");
}


int main() {
    Browser b;
    initBrowser(&b);

    int choice;
    char url[URL_SIZE];

    while (1) {
        printf("\n=== BROWSER NAVIGATION SYSTEM (Linked List) ===\n");
        printf("1. Visit New Page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show History\n");
        printf("5. Clear All History\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                fgets(url, URL_SIZE, stdin);
                url[strcspn(url, "\n")] = 0;
                visitPage(&b, url);
                break;

            case 2:
                goBack(&b);
                break;

            case 3:
                goForward(&b);
                break;

            case 4:
                showHistory(&b);
                break;

            case 5:
                clearHistory(&b);
                break;

            case 6:
                clearHistory(&b);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}



