#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct info {
	char surname[20];
	int count;
	int mass;
};

void Vvod(info* p)
{
	int x;
	printf("\nВведите фамилию: ");
	rewind(stdin);
	gets_s(p->surname);
	printf("\nВведите количество вещей: ");
	do {
		rewind(stdin);
		x = scanf_s("%d", &p->count);
	} while (!x);
	printf("\nВведите общий вес багажа: ");
	do {
		rewind(stdin);
		x = scanf_s("%d", &p->mass);
	} while (!x);
}

void Change(info* p, info* cp) {
	strcpy_s(p->surname, cp->surname);
	p->count = cp->count;
	p->mass = cp->mass;
}

void Vivod(info* p, int i) {
	printf("\n  %s, %d шт., %d кг \n", p[i].surname, p[i].count, p[i].mass);
}

void PomVivod(info* number, int n) {
	int i;
	printf("\n");
	for (i = 0; i < n; i++) {
		Vivod(number, i); // Вызов функции для выводда каждой структуры
	}
}

int main() {
	FILE* f;
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n, x, i, k, j, r=0;
	info* number, * number2;
	while (r!=9) {
		printf("\nВыберите один из вариантов:\n 1-Создать файл\n 2-Обработать\n Для завершения введите 9\n");
		x=scanf_s("%d", &r);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		switch (r) {
		case 1:
			fopen_s(&f, "Bagaje.txt", "wb");
			if (!f) {
				printf("Файл не был создан");
				return 1;
			}
			printf("Введите количество багажей: ");
			x = scanf_s("%d", &n);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			number = (info*)calloc(n, sizeof(info));
			if (number == NULL) {
				printf("Память не выделена");
				return 1;
			}
			for (i = 0; i < n; i++) {
				Vvod(&number[i]); // Вызов функции для ввода массива структур
			}
			system("cls");
			if (fwrite(&n, sizeof(int), 1, f) != 1)
				printf("Запись в файл не была произведена");
			if (fwrite(&number[0], sizeof(info), n, f) != n)
				printf("Запись в файл не была произведена, %d", n);
			fclose(f);
			free(number);
			break;
		case 2:
			fopen_s(&f, "Bagaje.txt", "a+b");
			if (!f) {
				printf("Файл не был создан");
				return 1;
			}
			rewind(f);
			if (fread(&k, sizeof(int), 1, f) != 1)
				printf("Error ");
			number2 = (info*)calloc(k, sizeof(info));
			number = (info*)calloc(k, sizeof(info));
			if (fread(&number2[0], sizeof(info), k, f) != k)
				printf("Error ");
			PomVivod(number2, k);
			fclose(f);										//Закрытие файла
			j = 0; n = 0;
			for (i = 0; i < k; i++) {
				if (number2[i].mass > 10) {
					Change(&number[j], &number2[i]);
					n++; j++;
				}
			}
			fopen_s(&f, "Bagaje.txt", "wb");				// Открытие файла
			if (!f) {
				printf("Файл не был создан");
				return 1;
			}
			if (fwrite(&n, sizeof(int), 1, f) != 1)
				printf("Запись в файл не была произведена");
			if (fwrite(&number[0], sizeof(info), n, f) != n)
				printf("Запись в файл не была произведена, %d", n);
			fclose(f);
			free(number);
			free(number2);
			break;
		}
	}
	return 0;
}