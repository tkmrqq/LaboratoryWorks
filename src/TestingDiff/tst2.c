#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void add_node(DblLinkedList* list, const char* newText)
{
    if (list == NULL)
    {
        return; // если список не был создан, выходим из функции
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return; // если не удалось выделить память, выходим из функции
    }

    newNode->text = (char*)malloc((strlen(newText) + 1) * sizeof(char));
    if (newNode->text == NULL)
    {
        free(newNode); // если не удалось выделить память, освобождаем узел и выходим из функции
        return;
    }

    strcpy(newNode->text, newText);
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail != NULL)
    {
        list->tail->next = newNode;
    }

    list->tail = newNode;

    if (list->head == NULL)
    {
        list->head = newNode;
    }

    list->size++;
}
