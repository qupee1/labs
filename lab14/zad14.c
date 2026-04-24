#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct room {
    char name[50];
    int level;
    int number;
    int resolution;
};

struct node {
    struct room data;
    struct node* next;
};

void add_to_end(struct node** head, struct room r) {
    struct node* new_node = malloc(sizeof(struct node));
    
    new_node->data = r;
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        struct node* last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
}

void print_list(struct node* head) {
    struct node* current = head;
    int i = 1;
    
    while (current != NULL) { 
        printf("Узел %d:\n", i);
        printf("  Имя: %s\n", current->data.name);
        printf("  Уровень: %d\n", current->data.level);
        printf("  Номер: %d\n", current->data.number);
        printf("  Размер: %d\n\n", current->data.resolution);
        current = current->next;
        i++;
    }
}

void free_list(struct node* head) {
    struct node* current = head;
    while (current != NULL) {
        struct node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    int n;
    
    printf("сколько комнат создать? ");
    scanf("%d", &n);
    
    srand(time(NULL));
    
    struct node* head = NULL;
    
    for (int i = 1; i <= n; i++) {
        struct room r;
        strcpy(r.name, "room");
        r.level = 1 + rand() % 10;
        r.number = i;
        r.resolution = 100 + rand() % 900;
        add_to_end(&head, r);
    }
    
    print_list(head);
    free_list(head);
    return 0;
}