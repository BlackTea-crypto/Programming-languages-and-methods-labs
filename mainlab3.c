#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

int main() {
        int choice;
        List items;
        items.n = 0;
        items.first = NULL;
        items.last = NULL;

        char filename[100];
        printf("Введите имя файла для хранения данных: ");
        scanf("%s", filename);
        FILE *file = fopen(filename, "r");
        if (!file) {
                printf("Данного файла не существует.\n");
                return 0;
        }
        fclose(file);

        loadFromFile(&items, filename);

	while (1) {
                printf("\nВыберите действие:\n");
                printf("1. Вывести содержимое базы данных\n");
                printf("2. Найти элемент\n");
                printf("3. Добавить новый элемент\n");
                printf("4. Удалить элемент\n");
                printf("5. Редактировать элемент\n");
                printf("0. Выход\n");
                scanf("%i", &choice);

                switch (choice) {
                        case 1:
                                print(items, filename);
                                break;
                        case 2:
                                search(items);
                                break;
                        case 3: {
                                int index = 0;
                                printf("Введите индекс для добавления: ");
                                scanf("%i", &index);
                                push(&items, index);
                                saveToFile(items, filename);
                                break;
                                }
                        case 4: {
                                int index;
                                if (items.n == 0) {
                                        printf("База данных пуста.\n");
                                        break;
                                }
                                printf("Введите индекс для удаления: ");
                                scanf("%i", &index);
                                erase(&items, index);
                                saveToFile(items, filename);
                                break;
                        }
			case 5: {
                                int index;
                                if (items.n == 0) {
                                        printf("База данных пуста.\n");
                                        break;
                                }
                                printf("Введите индекс для редактирования: ");
                                scanf("%i", &index);
                                edit(&items, index);
                                saveToFile(items, filename);
                                break;
                        }
                        case 0:
                                return 0;
                        default:
                                printf("Неверный выбор. Попробуйте снова.\n");
                                break;
                }
        }
}
