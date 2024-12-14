#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

opticItem *get(int index, List items) {
        if (index < 0 || index >= items.n) return NULL;
        opticItem *temp = items.first;
        for (int i = 0; i < index; i++) temp = temp->next;
        return temp;
}

void push(List *items, int index) {
        char name[100], type[100], manufacturer[100], brand[100];
        float price;

        printf("Введите название товара: ");
        scanf("%s", name);
        printf("Введите цену: ");
        scanf("%f", &price);
        printf("Введите тип товара (например, медицинские очки): ");
        scanf("%s", type);
        printf("Введите производителя товара: ");
        scanf("%s", manufacturer);
        printf("Введите бренд товара: ");
        scanf("%s", brand);

        opticItem *newItem = (opticItem *)malloc(sizeof(opticItem));
        strcpy(newItem->name, name);
        newItem->price = price;
        strcpy(newItem->type, type);
        strcpy(newItem->manufacturer, manufacturer);
        strcpy(newItem->brand, brand);
        newItem->next = NULL;

        if (index < 0 || index > items->n) {
                printf("Неверный индекс. Элемент добавлен в конец.\n");
                index = items->n;
        }

        if (items->n == 0) {
                items->first = newItem;
                items->last = newItem;
        }
        else if (index == 0) {
                newItem->next = items->first;
                items->first = newItem;
        }
	else if (index == items->n) {
                items->last->next = newItem;
                items->last = newItem;
        }
        else {
                opticItem *prev = get(index - 1, *items);
                newItem->next = prev->next;
                prev->next = newItem;
        }

        items->n++;
}

void erase(List *items, int index) {
        if (items->n == 0) return;
        if (index < 0 || index >= items->n) {
                printf("Неверный индекс для удаления.\n");
                return;
        }

        opticItem *temp;

        if (index == 0) {
                temp = items->first;
                items->first = temp->next;
                if (items->n == 1) items->last = NULL;
        }
        else {
                opticItem *prev = get(index - 1, *items);
                temp = prev->next;
                prev->next = temp->next;
                if (index == items->n - 1) items->last = prev;
        }

        free(temp);
        items->n--;
}

void search(List items) {
        if (items.n == 0) {
                printf("База данных пуста.\n");
                return;
        }
        int choice;
        printf("Выберите параметр для поиска:\n");
        printf("1. Название\n");
        printf("2. Цена\n");
        printf("3. Тип\n");
        printf("4. Производитель\n");
        printf("5. Бренд\n");
        scanf("%i", &choice);

        char keyword[100];
        float priceKeyword;
        if (choice == 1) {
                printf("Введите название товара: ");
                scanf("%s", keyword);
        }
        else if (choice == 2) {
                printf("Введите цену товара: ");
                scanf("%f", &priceKeyword);
        }
        else if(choice == 3) {
                printf("Введите тип товара: ");
                scanf("%s", keyword);
        }
        else if(choice == 4) {
                printf("Введите производителя товара: ");
                scanf("%s", keyword);
        }
        else if(choice == 5) {
                printf("Введите бренд: ");
                scanf("%s", keyword);
        }
	else {
                printf("Неверный выбор.\n");
                return;
        }

        opticItem *temp = items.first;
        int found = 0;

	while (temp) {
                if ((choice == 1 && strcmp(temp->name, keyword) == 0) || (choice == 2 && temp->price == priceKeyword) || (choice == 3 && strcmp(temp->type, keyword) == 0) ||
                    (choice == 4 && strcmp(temp->manufacturer, keyword) == 0) || (choice == 5 && strcmp(temp->brand, keyword) == 0)) {
                    printf("\nНазвание: %s, Цена: %.2f, Тип: %s, Производитель: %s, Бренд: %s\n", temp->name, temp->price, temp->type, temp->manufacturer, temp->brand);
                    found = 1;
                }
                temp = temp->next;
        }

        if (!found) printf("Товар с указанным параметром не найден.\n");
}

void edit(List *items, int index) {
        if (index < 0 || index >= items->n) {
                printf("Неверный индекс для редактирования.");
                return;
        }

        opticItem *item = get(index, *items);

        printf("Редактирование элемента с индексом %d:\n", index);
        printf("Введите новое название (текущее: %s): ", item->name);
        scanf("%s", item->name);
        printf("Введите новую цену (текущая: %f): ", item->price);
        scanf("%f", &item->price);
        printf("Введите новый тип (текущий: %s): ", item->type);
        scanf("%s", item->type);
        printf("Введите нового производителя (текущий: %s): ", item->manufacturer);
        scanf("%s", item->manufacturer);
        printf("Введите новый бренд (текущий: %s): ", item->brand);
        scanf("%s", item->brand);
}

void loadFromFile(List *items, const char *filename) {
        FILE *file = fopen(filename, "r");

        char name[100], type[100], manufacturer[100], brand[100];
        float price;

        while (fscanf(file, "%s %f %s %s %s", name, &price, type, manufacturer, brand) == 5) {
                opticItem *newItem = (opticItem *)malloc(sizeof(opticItem));
                strcpy(newItem->name, name);
                newItem->price = price;
                strcpy(newItem->type, type);
                strcpy(newItem->manufacturer, manufacturer);
                strcpy(newItem->brand, brand);
                newItem->next = NULL;

                if (items->n == 0) {
                        items->first = newItem;
                        items->last = newItem;
                }
                else {
                        items->last->next = newItem;
                        items->last = newItem;
                }

                items->n++;
        }

        fclose(file);
}

void saveToFile(List items, const char *filename) {
        FILE *file = fopen(filename, "w");

        opticItem *temp = items.first;
        while (temp) {
                fprintf(file, "%s %f %s %s %s\n",
                        temp->name, temp->price, temp->type, temp->manufacturer, temp->brand);
                temp = temp->next;
        }

        fclose(file);
}

void print(List items, const char *filename) {
        items.first = NULL;
        items.last = NULL;
        items.n = 0;

        loadFromFile(&items, filename);

        if (items.n == 0) {
                printf("База данных пуста.\n");
                return;
        }

        puts("\nБаза данных 'Оптика':");
        opticItem *temp = items.first;
        int index = 0;

        while (temp) {
                printf("[%d] Название: %s, Цена: %f, Тип: %s, Производитель: %s, Бренд: %s\n", index, temp->name, temp->price, temp->type, temp->manufacturer, temp->brand);
                temp = temp->next;
                index++;
        }
}
