#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct spisok {
	int number;
	spisok* next;
};

int New_el(spisok** p, int k) {
	spisok* n, * h, * j;
	n = (spisok*)calloc(1, sizeof(spisok));
	if (!n) {
		printf("Ошибка выделения памяти ");
		return 1;
	}
	n->number = k;
	n->next = NULL;
	if (*p == NULL) *p = n;
	else {
		h = *p;
		while (h->next != NULL) {
			j = h->next;
			h = j;
		}
		h->next = n;
	}
	return 0;
}

void Reading(char* str, spisok** p) {
	int i = 0, ns, ks, v, x;
	char strk[10];
	while (str[i] != '\0' && str[i] != '\n') {
		while (str[i++] == ' ');
		ns = i - 1;
		while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
			i++;
		ks = i;
		v = 0;
		for (ns; ns < ks; ns++) {
			strk[v] = str[ns];
			v++;
		}
		strk[v] = '\0';
		//printf("\n%s", strk);
		x = atoi(strk);
		New_el(p, x);
	}

}

void Read(spisok** p) {
	spisok* k = *p, * l;
	printf("\n");
	if (*p == NULL)
		printf("Список пуст");
	while (k != NULL) {
		printf("%d ", k->number);
		l = k->next;
		k = l;
	}
	printf("\n"); 
}

void Fun(spisok* M1, spisok* M2, spisok** M) {//Функция обЪединения списков
	spisok* uk = NULL, * ukM, * n;
	int k;
	ukM = *M;
	while (M1 != NULL && M2 != NULL) {
		if (M1->number < M2->number)
			k = 1;
		else
			k = 2;
		n = (spisok*)calloc(1, sizeof(spisok));
		if (!n) {
			printf("Ошибка выделения памяти ");
			return;
		}
		switch (k) {
		case 1:
			n->number = M1->number;
			uk = M1->next;
			M1 = uk;
			break;
		case 2:
			n->number = M2->number;
			uk = M2->next;
			M2 = uk;
			break;
		}
		n->next = NULL;
		if (*M == NULL) *M = n;
		else {
			ukM = *M;
			while (ukM->next != NULL) {
				uk = ukM->next;
				ukM = uk;
			}
			ukM->next = n;

		}// Копирует пока не закончится какой-либо из двух списков
	}
	if (M1 == NULL)
		while (M2 != NULL) {
			n = (spisok*)calloc(1, sizeof(spisok));
			if (!n) {
				printf("Ошибка выделения памяти ");
				return;
			}
			n->number = M2->number;
			uk = M2->next;
			M2 = uk;
			ukM = *M;
			while (ukM->next != NULL) {
				uk = ukM->next;
				ukM = uk;
			}
			ukM->next = n;
		}
	if (M2 == NULL)
		while (M1 != NULL) {
			n = (spisok*)calloc(1, sizeof(spisok));
			if (!n) {
				printf("Ошибка выделения памяти ");
				return;
			}
			n->number = M1->number;
			uk = M1->next;
			M1 = uk;
			ukM = *M;
			while (ukM->next != NULL) {
				uk = ukM->next;
				ukM = uk;
			}
			ukM->next = n;
		}
}

void Del_el(spisok** p) {
	spisok* uk = *p, * k, * last = *p;
	while (*p != NULL) {
	if ((*p)->next == NULL)
		*p = NULL;
	else {
		uk = *p;
		while (uk->next != NULL) {
			last = uk;
			k = uk->next;
			uk = k;
		}
		last->next = NULL;
		free(uk);
	}
}
}

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i, k, x;
	char str[100];
	spisok* M1 = NULL, * M2 = NULL, * M = NULL;
	FILE* s;
	fopen_s(&s, "Stroka.txt", "r");
	if (!s) {
		printf("Файл не был создан");
		return 1;
	}
	for (i = 0; i < 2; i++) {
		if (fgets(str, 100, s) == NULL) { puts("no line"); break; }
		//printf("\n[%d] %s", i, str);
		if (i == 0) 
			Reading(str, &M1);
		else 
			Reading(str, &M2);
	}
	do {
		printf("\nМеню:\n1-Вывод списка M1\n2-Вывод списка M2\n3-Вывод результирующего списка M\n4-Выполнить обЪединение списков M1 и M2\n5-Удаление списка M1\n6-Удаление списка M2\n7-Удаление списка M\nДля выходы наберите 9 \n");
		x = scanf_s("%d", &k);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		switch (k) {
		case 1:
			printf("\nСписок M1: ");
			Read(&M1);
			break;
		case 2:
			printf("\nСписок M2: ");
			Read(&M2);
			break;
		case 3:
			printf("\nРезультирующий список M: ");
			Read(&M);
			break;
		case 4:
			Fun(M1, M2, &M);
			break;
		case 5:
			//while(M1!=NULL)
				Del_el(&M1);
			break;
		case 6:
			Del_el(&M2);
			break;
		case 7:
			Del_el(&M);
			break;		
		}

	} while(k!=9);
	fclose(s);
	free(M);
	free(M1);
	free(M2);
	return 0;
}