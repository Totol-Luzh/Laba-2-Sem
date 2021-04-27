#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct stroka {
	char str[30];
	int var;
};

void Vvod(stroka* p) {
	printf("Заполните строку: ");
	rewind(stdin);
	gets_s(p->str);
	strcat_s(p->str, "\n");
}

void Vivod(stroka* p, int i) {
	printf("\n  %s", p[i].str);
}

void PomVivod(stroka* number, int n) {
	int i;
	printf("\n");
	for (i = 0; i < n; i++) {
		Vivod(number, i); // Вызов функции для выводда каждой структуры
	}
}

int main() {
	FILE* f, *s;
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i, k, n, r=0, x, j, m;
	stroka* number;
	while (r != 9) {
		printf("\nВыберите один из вариантов:\n 1-Создать файл\n 2-Обработать\n Для завершения введите 9\n");
		x = scanf_s("%d", &r);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		switch (r) {
		case 1:
			fopen_s(&f, "Text.txt", "w");
			if (!f) {
				printf("Файл не был создан");
				return 1;
			}
			printf("Введите количество строк: ");
			x = scanf_s("%d", &n);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			number = (stroka*)calloc(n, sizeof(stroka));
			if (number == NULL) {
				printf("Память не выделена");
				return 1;
			}
			for (i = 0; i < n; i++) {
				Vvod(&number[i]); // Вызов функции для ввода массива структур
			}
			system("cls");
			PomVivod(number, n);
			/*printf("Введите строку (ввод пустой строки - завершение записи)\n");
			do{
			gets_s(str);
			if (*str = '\0') break;
			strcat(str, "\n");
			fputs(str, f);
			}while (*str != '\n');*/
			for(i=0; i<n; i++)
			if(fputs(number[i].str, f)== EOF) printf("Error");
			fclose(f);
			free(number);
			break;
		case 2:
			fopen_s(&f, "Text.txt", "a+");
			if (!f) {
				printf("Файл не был создан");
				return 1;
			}
			number = (stroka*)calloc(50, sizeof(stroka));
			if (number == NULL) {
				printf("Память не выделена");
				return 1;
			}
			for(i=0; number[i-1].str[0]!='\0'; i++)
			if(fgets(number[i].str, 35, f)==NULL) break;
			k = i;
			printf("\nИсходный файл:");
			PomVivod(number, k);
			for(i=0;i<k; i++)
				for(j=i+1; j<k; j++){
					m=strcmp(number[i].str, number[j].str);
					if (m == 0) {
						number[i].var = 2;
						number[j].var = 2;
					}
				}
			fopen_s(&s, "NewText.txt", "w");
			for (i = 0; i < k; i++)
				if(number[i].var!=2)
					if (fputs(number[i].str, s) == EOF) printf("Error");
			fclose(s);
			fopen_s(&s, "NewText.txt", "r");
			if (!s) {
				printf("Файл не был создан");
				return 1;
			}
			for (i = 0; number[i - 1].str[0] != '\0'; i++)
				if (fgets(number[i].str, 35, s) == NULL) break;
			k = i;
			printf("\nПолученный файл:");
			PomVivod(number, k);
			fclose(s);
			fclose(f);
			free(number);
			break;
		}
	}
	return 0;
}