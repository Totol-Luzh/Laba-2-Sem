#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct ocher {
	char c;
	ocher* nx, * pr;
};

int Fun(ocher** t, ocher** h, char sym) {
	ocher* n;
	n = (ocher*)calloc(1, sizeof(ocher));
	if (!n) {
		printf("Ошибка выделения памяти ");
		return 1;
	}
	n->c = sym;
	if(!*h) *h=*t=n;
	else {
		n->pr = *t;
		(*t)->nx = n;
		*t = n;
	}
	return 0;
}

void Del(ocher** t, ocher** h) {
	ocher* n = *h;
	*h = n->nx;
	free(n);
}

int Prov(ocher** t, ocher** h) {
	ocher* huk=*h, * tuk=*t, *pk;
	while (huk != *t) {
		if (huk->c == tuk->c) {
			pk = huk;
			huk = pk->nx;
			pk = tuk;
			tuk = pk->pr;
		}
		else
			return 1;
	}
	return 0;
}

void Reading(ocher** t, ocher** h) {
	ocher* uk= *h, *pk=*h;
	while (uk) {
		printf("%c", pk->c);
		uk = pk->nx;
		pk = uk;
	}
	printf("\n");
}

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* s;
	int i, j, k,x, r=0;
	char str[100];
	ocher* t=0, * h=0;
	fopen_s(&s, "Stroka.txt", "a+");
	if (!s) {
		printf("Файл не был создан");
		return 1;
	}
	do {
		printf("\nМеню:\n1-Поиск симметричных строк\n2-Запись и чтение очереди\nДля выходы наберите 9 \n");
		x = scanf_s("%d", &r);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		switch (r) {
		case 1:
			rewind(s);
			for (i = 0;; i++) {
				if (fgets(str, 100, s) == NULL) break;
				for (j = 0; str[j] != '\0' && str[j] != '\n'; j++)
					Fun(&t, &h, str[j]);
				k = Prov(&t, &h);
				if (k == 0) {
					printf("Строка [%d] симметрична:\n", i);
					//printf("[%d] %s", i, str);
					Reading(&t, &h);
				}
				for (j; j != 0; j--)
					Del(&t, &h);
			}
			break;
		case 2:
			rewind(s);
			printf("\nВывод содержимого стека:\n");
			for (i = 0;; i++) {
				if (fgets(str, 100, s) == NULL) break;
				for (j = 0; str[j] != '\0' && str[j] != '\n'; j++)
					Fun(&t, &h, str[j]);
				Reading(&t, &h);
				for (j; j != 0; j--)
					Del(&t, &h);
			}
			if (i == 0)
				printf("Файл пуст");
			break;
		}
	}while (r != 9);
	fclose(s);
	return 0;
}