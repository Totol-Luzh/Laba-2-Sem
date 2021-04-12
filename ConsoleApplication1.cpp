#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct izdanie {
	char izd_name[100];
	int  count;
	float price;
} def;

void add_to_File(FILE* in_which_add);


int main(void) {
	setlocale(LC_ALL, "Russian");
	FILE* ffile = NULL;

	//
	if ((ffile = fopen("file.bat", "w + b")) == NULL) exit(EXIT_FAILURE);
	//

	while (true) {
		printf("Просмотр информации всех изданий: 1\n");
		printf("Добавление издания в список: 2\n");
		printf("Просмотр издания с максимальной ценой за журнал: 3\n");
		printf("Просмотр издания с минимальной ценой за журнал: 4\n");
		printf("Просмотр издания с максимальным количеством экземпляров в год: 5\n");
		printf("Выход: 6\n");

		//Проверка на ввод....
		int choice = 0;
		int check_on_choice = scanf("%d", &choice);
		while (check_on_choice != 1) {
			printf("Введен неверный параметр, повторите ввод.\n");
			rewind(stdin);
			int check_on_choice = scanf("%d", &choice);
		}
		//.......

		if (choice == 1);
		if (choice == 2) add_to_File(ffile);
		if (choice == 3);
		if (choice == 4);
		if (choice == 5);
		if (choice == 6) {
			fclose(ffile);
			break;
		}
	}
}

void add_to_File(FILE* in_which_add) {
	struct izdanie* for_add = (izdanie *)malloc(sizeof(struct izdanie) * 1);
	printf("Введите название газеты/журнала:\n");
	rewind(stdin);
	fgets(for_add -> izd_name, 100, stdin);
	printf("Введите стоимость за один экземляр:\n");
	while (true) {
		int choice_check = scanf("%f", &(for_add -> price));
		if (for_add -> price > 0 && choice_check == 1) break;
		else {
			printf("Введен неверный параметр. Повторите ввод.\n");
			rewind(stdin);
			choice_check = scanf("%d", &(for_add -> price));
		}
	}
	printf("Введите количество экземпляров в год:\n");
	while (true) {
		int choice_check = scanf("%d", &(for_add -> count));
		if (for_add -> count > 0 && choice_check == 1) break;
		else {
			printf("Введен неверный параметр. Повторите ввод.\n");
			rewind(stdin);
			choice_check = scanf("%d", &(for_add -> count));
		}
	}
	//fprintf(in_which_add, "%s %d %f\n", for_add.izd_name, for_add.count, for_add.price);
	fwrite(&for_add, sizeof(struct izdanie), 1, in_which_add);
}