#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct country {
	char title[25];
	char capital[25];
	int population;
	int square;
};

void Vvod(country* p)
{
	int x;
	printf("\nВведите название государства: ");
	rewind(stdin);
	gets_s(p->title);
	printf("\nВведите название столицы: ");
	rewind(stdin);
	gets_s(p->capital);
	printf("\nВведите численность населения: ");
	do {
		rewind(stdin);
		x=scanf_s("%d", &p->population);
	} while (!x);
	printf("\nВведите занимаемую площадь: ");
	do {
		rewind(stdin);
		x=scanf_s("%d", &p->square);
	}while(!x);
}

void Vivod(country* p, int i) {
	printf("\n%s, %s, %d, %d \n", p[i].title, p[i].capital, p[i].population, p[i].square);
}

int gg(char* str, char* h) {
	int m, i, j, k, l;
	m = strlen(h);
	l = strlen(str);
	l++;
	for (i=0; i<l-m; i++) {
		if (str[i] != h[0]) {
			continue;
		}
		k=i;j=0;
		while(k<k+m+1){
			if (str[k] != h[j]) break;
			j++; k++;
		}
		return 0;
	}
	return 1;
}

void Poisk(country* p, int n, char* h, int c) {
	int i, k;
	switch (c){
	case 1: 
		for (i=0; i<n; i++){
		k=gg(p[i].title, h);
		if(k==0)
			Vivod(p, i);
		}
		break;
	case 2:
		for (i=0; i<n; i++){
			k = gg(p[i].capital, h);
			if (k==0)
				Vivod(p, i);
		}
		break;
	}
}

int Izmen(country* p) {
	int k, x;
	do{
		printf("Введите номер поля, которое хотите изменить \n1- название государства 2-название столицы 3-численность населения 4-занимаемая площадь\n Если ничего не хотите изменить, введите 0\n");
		x=scanf_s("%d", &k);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		if(k!=0) printf("Заполните поле: ");
		switch (k) {
		case 1:
			rewind(stdin);
			gets_s(p->title);
			break;
		case 2:
			rewind(stdin);
			gets_s(p->capital);
			break;
		case 3:
			x = scanf_s("%d", &p->population);
			if (!x) {
				printf("Данные введены не верно ");  //  Посмотреть указатели на структуру   [i]
				return 1;
			}
			break;
		case 4:
			x=scanf_s("%d", &p->population);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			break;
		}
	} while(k!=0);
	return 0;
}

void Change(country* p, country* cp, int x) {
	char str[25], ptr[25];
	int i, k;
	if (x!=0) {
		strcpy_s(str, p->title);
		strcpy_s(ptr, p->capital);
		i = p->population;
		k = p->square;
	}
	strcpy_s(p->title, cp->title);
	strcpy_s(p->capital, cp->capital);
	p->population = cp->population;
	p->square = cp->square;
	if (x!=0) {
		strcpy_s(cp->title, str);
		strcpy_s(cp->capital, ptr);
		cp->population = i;
		cp->square = k;
	}
}

int Str(country* p, country* cp, int k) {
	int c;
	switch (k) {
	case 1:
		c = strcmp(p->title, cp->title);
		return c;
	case 2:
		c = strcmp(p->capital, cp->capital);
		return c;
	case 3:
		c = p->population - cp->population;
		return c;
	case 4:
		c = p->square - cp->square;
		return c;
	}
}

void Delete(country* p, int n, int k) {
	int i, x=0;
	for (i = k; i < n - 1; i++) {
		Change(&p[i], &p[i + 1], x);
	}
}

void PomVivod(country* number, int n){
	int i;
	printf("\n");
	for (i = 0; i < n; i++) {
		Vivod(number, i); // Вызов функции для выводда каждой структуры
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i, j, n, x, t, num;
	char* tp;
	char st[25];
	printf("Введите количество государств: ");
	x = scanf_s("%d", &n);
	if (!x) {
		printf("Данные введены не верно ");
		return 1;
	}
	country* number;
	number = (country*)calloc(n, sizeof(country));
	if (number == NULL) {
		printf("Память не выделена");
		return 1;
	}
	for (i = 0; i < n; i++) {
		Vvod(&number[i]); // Вызов функции для ввода массива структур
	}
	system("cls");
	PomVivod(number, n);

	printf("\nВведите параметр поиска: \n1-Государство, \n2-Столица\n "); // Частичный поиск (Предоставление выбора поиска)
	x=scanf_s("%d", &t);
	if (!x) {
		printf("Данные введены не верно ");
		return 1;
	}
	tp=(char*)calloc(15, sizeof(char));
	if (tp == NULL) {
		printf("Память не выделена");
		return 1;
	}
	printf("Введите искомую информацию: ");
	rewind(stdin);
	gets_s(tp, 15); // Ввод частичной информации
	printf("\n");
	Poisk(number, n, tp, t); // Вызов функции частичного поиска			// Частичный поиск окончен
	PomVivod(number, n);

	printf("\nВведите номер структуры, которую хотите изменить: ");	// Изменение структуры
	x=scanf_s("%d", &num);
	if (!x) {
		printf("Данные введены не верно ");
		return 1;
	}
	if(num<n)
		Izmen(&number[num]);
	else
		printf("Структура не найдена ");								// Изменение завершено
	PomVivod(number, n);

	printf("Введите номер структуры, которую хотите удалить: ");			// Удаление
		x=scanf_s("%d", &num);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		Delete(number, n, num);
		n--;																// Удаление завершено
	PomVivod(number, n);

	printf("\nВыберите параметр сортировки: \n1- название государства 2-название столицы 3-численность населения 4-занимаемая площадь\n"); // Сортировка
		x=scanf_s("%d", &num);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		} 
		for (i=0; i<n; ++i)
			for (j=n-1; j>i; --j) {
				t=Str(&number[j-1], &number[j], num);
					if (t>0) {
						Change(&number[j - 1], &number[j], num);
					}
			}																			// Сортировка закончилась
	PomVivod(number, n);

	printf("\nВведите параметр поиска: \n1-Государство, \n2-Столица, \n3-Численность населения, \n4-Занимаемая площадь\n "); // Поиск по параметру
	x=scanf_s("%d", &num);
	if (!x) {
		printf("Данные введены не верно ");
		return 1;
	} 
	printf("Введите искомую информацию: ");
	if (num == 1 || num == 2) {
		rewind(stdin);
		gets_s(st);
	}
	else
		x=scanf_s("%d", &t);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		} 
	for(i=0; i<n; i++)
	switch (num) {
	case 1:
		j = strcmp(number[i].title, st);
		if(j==0) 
			Vivod(number, i);
		break;
	case 2:
		j = strcmp(number[i].capital, st);
		if (j==0)
			Vivod(number, i);
		break;
	case 3:
		if(t==number[i].population)
			Vivod(number, i);
		break;
	case 4:
		if (t==number[i].square)
			Vivod(number, i);
		break;
	}										// Конец поиска
	PomVivod(number, n);
	free (tp);
	free (number);
	return 0;
}