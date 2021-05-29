#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct spisok {
	char name[20];
	char surname[20];
	int hometype;
	union {
		struct a {
			char street[20];
			int home;
			int flat;
		} aa;
		struct b {
			char region[20];
			char city[20];
			char street[20];
			int home;
			int flat;
		} bb;
		struct c {
			char region[20];
			char district[20];
			char city[20];
			char street[20];
			int home;
			int flat;
		} cc;
		struct d {
			char region[20];
			char district[20];
			char village[20];
			int home;
		} dd;
	} hom;
};

void Vivod(spisok* p, int i) {
	printf("\n%d %s %s ", i, p[i].name, p[i].surname);
	switch (p[i].hometype) {
	case 1:	printf("Минск, ул. %s, д. %d, %d \n", p[i].hom.aa.street, p[i].hom.aa.home, p[i].hom.aa.flat);
		break;
	case 2: printf("%s область, город %s, ул. %s, д. %d, %d \n", p[i].hom.bb.region, p[i].hom.bb.city, p[i].hom.bb.street, p[i].hom.bb.home, p[i].hom.bb.flat);
		break;
	case 3: printf("%s область, %s район, город %s, ул. %s, д. %d, %d \n", p[i].hom.cc.region, p[i].hom.cc.district, p[i].hom.cc.city, p[i].hom.cc.street, p[i].hom.cc.home, p[i].hom.cc.flat);
		break;
	case 4: printf("%s область, %s район, деревня %s, д. %d \n", p[i].hom.dd.region, p[i].hom.dd.district, p[i].hom.dd.village, p[i].hom.dd.home);
		break;
	}
}

void Perenos(spisok* p, char* str, int k, int j) {
	if(k<4)
		switch (k) {
		case 1:	strcpy_s(p[j].name, str);
			break;
		case 2: strcpy_s(p[j].surname, str);
			break;
		case 3: p[j].hometype = atoi(str);
			break;
		}
	else
		switch (p[j].hometype) {
		case 1: 
			if(k==4)
				strcpy_s(p[j].hom.aa.street, str);
			if (k == 5)
				p[j].hom.aa.home = atoi(str);
			if(k==6)
				p[j].hom.aa.flat = atoi(str);
			break;
		case 2: 
			if(k==4)
				strcpy_s(p[j].hom.bb.region, str);
			if(k==5)
				strcpy_s(p[j].hom.bb.city, str);
			if(k==6)
				strcpy_s(p[j].hom.bb.street, str);
			if(k==7)
				p[j].hom.bb.home = atoi(str);
			if(k==8)
				p[j].hom.bb.flat = atoi(str);
			break;
		case 3:
			if(k==4)
				strcpy_s(p[j].hom.cc.region, str);
			if(k==5)
				strcpy_s(p[j].hom.cc.district, str);
			if(k==6)
				strcpy_s(p[j].hom.cc.city, str);
			if(k==7)
				strcpy_s(p[j].hom.cc.street, str);
			if(k==8)
				p[j].hom.cc.home = atoi(str);
			if(k==9)
				p[j].hom.cc.flat = atoi(str);
			break;
		case 4:
			if(k==4)
				strcpy_s(p[j].hom.dd.region, str);
			if(k==5)
				strcpy_s(p[j].hom.dd.district, str);
			if(k==6)
				strcpy_s(p[j].hom.dd.village, str);
			if(k==7)
				p[j].hom.dd.home = atoi(str);
		}
}

void Convert(spisok* p, char** argv, int argc) {
	int i=0, j=1, ns, ks, k, v;
	char str[20];
	for (j=1; j < argc; j++) {
		k = 1;
		i = 0;
		while (argv[j][i] != '\0') {
			while (argv[j][i++] == ' ');
			ns = i - 1;
			while (argv[j][i] != ' ' && argv[j][i] != '\0')
				i++;
			ks = i;
			v = 0;
			for (ns; ns < ks; ns++) {
				str[v] = argv[j][ns];
				v++;
			}
			str[v] = '\0';
			printf("\n%s", str);
			Perenos(p, str, k, j-1);
			k++;
		}
	}
}

void Pomoch(spisok* number, int j, int i) {
	if (j == 0)
		Vivod(number, i);
}

int gg(char* str, char* h) {
	int m, i, j, k, l;
	m = strlen(h);
	l = strlen(str);
	l++;
	for (i = 0; i < l - m; i++) {
		if (str[i] != h[0]) {
			continue;
		}
		k = i; j = 0;
		while (k < k + m + 1) {
			if (str[k] != h[j]) break;
			j++; k++;
		}
		return 0;
	}
	return 1;
}

void Poisk(spisok* p, int n, char* h, int c) {
	int i, k;
	char st[25]{ "Минск" };
	switch (c) {
	case 1:
		for (i = 0; i < n; i++) {
			k = 2;
			k = gg(p[i].name, h);
			if (k == 0)
				Vivod(p, i);
		}
		break;
	case 2:
		for (i = 0; i < n; i++) {
			k = 2;
			k = gg(p[i].surname, h);
			if (k == 0)
				Vivod(p, i);
		}
		break;
	case 3:
		for (i = 0; i < n; i++) {
			k = 2;
			switch (p[i].hometype) {
			case 2: k = gg(p[i].hom.bb.region, h);
				break;
			case 3: k = gg(p[i].hom.cc.region, h);
				break;
			case 4: k = gg(p[i].hom.dd.region, h);
				break;
			}
			if (k == 0)
				Vivod(p, i);
		}
		break;
	case 4:
		for (i = 0; i < n; i++) {
			k = 2;
			switch (p[i].hometype) {
			case 3: k = gg(p[i].hom.cc.district, h);
				break;
			case 4: k = gg(p[i].hom.dd.district, h);
				break;
			}
			if (k == 0)
				Vivod(p, i);
		}
		break;
	case 5:
		for (i = 0; i < n; i++) {
			k = 2;
			switch (p[i].hometype) {
			case 1: k = gg(st, h);
				break;
			case 2: k = gg(p[i].hom.bb.city, h);
				break;
			case 3: k = gg(p[i].hom.cc.city, h);
				break;
			}
			if (k == 0)
				Vivod(p, i);
		}
		break;
	case 6:
		for (i = 0; i < n; i++) {
			k = 2;
			switch (p[i].hometype) {
			case 1: k = gg(p[i].hom.aa.street, h);
				break;
			case 2: k = gg(p[i].hom.bb.street, h);
				break;
			case 3: k = gg(p[i].hom.cc.street, h);
				break;
			}
			if (k == 0)
				Vivod(p, i);
		}
		break;
	case 7:
			for (i = 0; i < n; i++) {
				k = 2;
				if (p[i].hometype == 4)
				k = gg(p[i].hom.dd.village, h);
				if (k == 0)
					Vivod(p, i);
			}
		break;
	}
}

int Izmen(spisok* p) {
	int k, x, h;
	do {
		printf("Введите номер поля, которое хотите изменить \n1- Фамилия 2-Имя 3-вариант места жительства 4-место жительства\n Если ничего не хотите изменить, введите 0\n");
		x = scanf_s("%d", &k);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		//if (k != 0) printf("Заполните поле: ");
		switch (k) {
		case 1:
			rewind(stdin);
			gets_s(p->name);
			break;
		case 2:
			rewind(stdin);
			gets_s(p->surname);
			break;
		case 3:
			printf("Выберите тип места жительства: ");
			x = scanf_s("%d", &p->hometype);
			if (!x) {
				printf("Данные введены не верно ");  
				return 1;
			}
			switch (p->hometype) {
			case 1:
				printf("Введите название улицы: ");
				rewind(stdin);
				gets_s(p->hom.aa.street);
				printf("Введите номер дома: ");
				x = scanf_s("%d", &p->hom.aa.home);
				if (!x) return 1;
				printf("Введите номер квартиры: ");
				x = scanf_s("%d", &p->hom.aa.flat);
				if (!x) return 1;
				break;
			case 2:
				printf("Введите название области: ");
				rewind(stdin);
				gets_s(p->hom.bb.region);
				printf("Введите название города: ");
				rewind(stdin);
				gets_s(p->hom.bb.city);
				printf("Введите название улицы: ");
				rewind(stdin);
				gets_s(p->hom.bb.street);
				printf("Введите номер дома: ");
				x = scanf_s("%d", &p->hom.bb.home);
				if (!x) return 1;
				printf("Введите номер квартиры: ");
				x = scanf_s("%d", &p->hom.bb.flat);
				if (!x) return 1;
				break;
			case 3:
				printf("Введите название области: ");
				rewind(stdin);
				gets_s(p->hom.cc.region);
				printf("Введите название района: ");
				rewind(stdin);
				gets_s(p->hom.cc.district);
				printf("Введите название города: ");
				rewind(stdin);
				gets_s(p->hom.cc.city);
				printf("Введите название улицы: ");
				rewind(stdin);
				gets_s(p->hom.cc.street);
				printf("Введите номер дома: ");
				x = scanf_s("%d", &p->hom.cc.home);
				if (!x) return 1;
				printf("Введите номер квартиры: ");
				x = scanf_s("%d", &p->hom.cc.flat);
				if (!x) return 1;
				break;
			case 4:
				printf("Введите название области: ");
				rewind(stdin);
				gets_s(p->hom.dd.region);
				printf("Введите название района: ");
				rewind(stdin);
				gets_s(p->hom.dd.district);
				printf("Введите название деревни: ");
				rewind(stdin);
				gets_s(p->hom.dd.village);
				printf("Введите номер дома: ");
				x = scanf_s("%d", &p->hom.cc.home);
				if (!x) return 1;

			}
			break;
		case 4:
			switch (p->hometype) {
			case 1:
				printf("Выберите, что хотите изменить: 1-улица, 2-дом, 3-квартира ");
				x = scanf_s("%d", &h);
				if (!x) return 1;
				if (h == 1) {
					rewind(stdin);
					gets_s(p->hom.aa.street);
				}
				if (h == 2) {
					x = scanf_s("%d", &p->hom.aa.home);
					if (!x) return 1;
				}
				if (h == 3) {
					x = scanf_s("%d", &p->hom.aa.flat);
					if (!x) return 1;
				}
				break;
			case 2:
				printf("Выберите, что хотите изменить: 1-область, 2-город, 3-улица, 4-дом, 5-квартира ");
				x = scanf_s("%d", &h);
				if (!x) return 1;
				if (h == 1) {
					rewind(stdin);
					gets_s(p->hom.bb.region);
				}
				if (h == 2) {
					rewind(stdin);
					gets_s(p->hom.bb.city);
				}
				if (h == 3) {
					rewind(stdin);
					gets_s(p->hom.bb.street);
				}
				if (h == 4) {
					x = scanf_s("%d", &p->hom.bb.home);
					if (!x) return 1;
				}
				if (h == 5) {
					x = scanf_s("%d", &p->hom.bb.flat);
					if (!x) return 1;
				}
				break;
			case 3:
				printf("Выберите, что хотите изменить: 1-область, 2-район, 3-город, 4-улица, 5-дом, 6-квартира ");
				x = scanf_s("%d", &h);
				if (!x) return 1;
				if (h == 1) {
					rewind(stdin);
					gets_s(p->hom.cc.region);
				}
				if (h == 2) {
					rewind(stdin);
					gets_s(p->hom.cc.district);
				}
				if (h == 3) {
					rewind(stdin);
					gets_s(p->hom.cc.city);
				}
				if (h == 4) {
					rewind(stdin);
					gets_s(p->hom.cc.street);
				}
				if (h == 5) {
					x = scanf_s("%d", &p->hom.cc.home);
					if (!x) return 1;
				}
				if (h == 6) {
					x = scanf_s("%d", &p->hom.cc.flat);
					if (!x) return 1;
				}
				break;
			case 4:
				printf("Выберите, что хотите изменить: 1-область, 2-район, 3-деревня, 4-дом ");
				x = scanf_s("%d", &h);
				if (!x) return 1;
				if (h == 1) {
					rewind(stdin);
					gets_s(p->hom.dd.region);
				}
				if (h == 2) {
					rewind(stdin);
					gets_s(p->hom.dd.district);
				}
				if (h == 3) {
					rewind(stdin);
					gets_s(p->hom.dd.village);
				}
				if (h == 4) {
					x = scanf_s("%d", &p->hom.dd.home);
					if (!x) return 1;
				}
				break;
			}
		break;
		}
	} while (k != 0);
	return 0;
}

void Change(spisok* p, spisok* cp, int x) {
	char str[25], ptr[25], ytr[25], utr[25], itr[25], otr[25], vtr[25];
	int i=0, k=0, l=0;
	ytr[0] = '\0'; utr[0] = '\0'; itr[0] = '\0'; otr[0] = '\0'; vtr[0] = '\0';
	if (x != 0) {
		strcpy_s(str, p->name);
		strcpy_s(ptr, p->surname);
		i = p->hometype;
		switch (p->hometype) {
		case 1:
			strcpy_s(otr, p->hom.aa.street);
			k = p->hom.aa.home;
			l = p->hom.aa.flat;
			break;
		case 2:
			strcpy_s(ytr, p->hom.bb.region);
			strcpy_s(itr, p->hom.bb.city);
			strcpy_s(otr, p->hom.bb.street);
			k = p->hom.bb.home;
			l = p->hom.bb.flat;
			break;
		case 3:
			strcpy_s(ytr, p->hom.cc.region);
			strcpy_s(utr, p->hom.cc.district);
			strcpy_s(itr, p->hom.cc.city);
			strcpy_s(otr, p->hom.cc.street);
			k = p->hom.cc.home;
			l = p->hom.cc.flat;
			break;
		case 4:
			strcpy_s(ytr, p->hom.dd.region);
			strcpy_s(utr, p->hom.dd.district);
			strcpy_s(vtr, p->hom.dd.village);
			k = p->hom.dd.home;
			break;
		}
	}
	strcpy_s(p->name, cp->name);
	strcpy_s(p->surname, cp->surname);
	p->hometype = cp->hometype;
	switch (cp->hometype) {
		case 1:
			strcpy_s(p->hom.aa.street, cp->hom.aa.street);
			p->hom.aa.home = cp->hom.aa.home;
			p->hom.aa.flat = cp->hom.aa.flat;
			break;
		case 2:
			strcpy_s(p->hom.bb.region, cp->hom.bb.region);
			strcpy_s(p->hom.bb.city, cp->hom.bb.city);
			strcpy_s(p->hom.bb.street, cp->hom.bb.street);
			p->hom.bb.home = cp->hom.bb.home;
			p->hom.bb.flat = cp->hom.bb.flat;
			break;
		case 3:
			strcpy_s(p->hom.cc.region, cp->hom.cc.region);
			strcpy_s(p->hom.cc.district, cp->hom.cc.district);
			strcpy_s(p->hom.cc.city, cp->hom.cc.city);
			strcpy_s(p->hom.cc.street, cp->hom.cc.street);
			p->hom.cc.home = cp->hom.cc.home;
			p->hom.cc.flat = cp->hom.cc.flat;
			break;
		case 4: 
			strcpy_s(p->hom.dd.region, cp->hom.dd.region);
			strcpy_s(p->hom.dd.district, cp->hom.dd.district);
			strcpy_s(p->hom.dd.village, cp->hom.dd.village);
			p->hom.dd.home = cp->hom.dd.home;
			break;
	}
	if (x != 0) {
		strcpy_s(cp->name, str);
		strcpy_s(cp->surname, ptr);
		cp->hometype = i;
		switch (i) {
		case 1:
			strcpy_s(cp->hom.aa.street, otr);
			cp->hom.aa.home=k;
			cp->hom.aa.flat=l;
			break;
		case 2:
			strcpy_s(cp->hom.bb.region, ytr);
			strcpy_s(cp->hom.bb.city, itr);
			strcpy_s(cp->hom.bb.street, otr);
			cp->hom.bb.home=k;
			cp->hom.bb.flat=l;
			break;
		case 3:
			strcpy_s(cp->hom.cc.region, ytr);
			strcpy_s(cp->hom.cc.district, utr);
			strcpy_s(cp->hom.cc.city, itr);
			strcpy_s(cp->hom.cc.street, otr);
			cp->hom.cc.home=k;
			cp->hom.cc.flat=l;
			break;
		case 4:
			strcpy_s(cp->hom.dd.region, ytr);
			strcpy_s(cp->hom.dd.district, utr);
			strcpy_s(cp->hom.dd.village, vtr);
			cp->hom.dd.home=k;
			break;
		}
	}
}

int Str(spisok* p, spisok* cp, int k) {
	int c;
	switch (k) {
	case 1:
		c = strcmp(p->name, cp->name);
		return c;
	case 2:
		c = strcmp(p->surname, cp->surname);
		return c;
	case 3:
		c = p->hometype - cp->hometype;
		return c;
	}
	return 0;
}

void Delete(spisok* p, int n, int k) {
	int i, x = 0;
	for (i = k; i < n - 1; i++) {
		Change(&p[i], &p[i + 1], x);
	}
}

void PomVivod(spisok* p, int n) {
	int i;
	printf("\n");
	for (i = 0; i < n; i++) {
		Vivod(p, i); // Вызов функции для выводда каждой структуры
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "rus");			//"Лужинский Сергей 2 Минская Молодечно З-Сумицкого 2 45" "Саланович Евгений 4 Минская Слуцкий Весея 24"
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i, j, n, x, t=0, num, k;
	char st[25];
	printf("%s", argv[1]);
	n = argc-1;
	spisok* number;
	number = (spisok*)calloc(n, sizeof(spisok));
	if (number == NULL) {
		printf("Память не выделена");
		return 1;
	}
	Convert(number, argv, argc);
	PomVivod(number, n);

	do {
		printf("\nМеню:\n1-Частичный поиск\n2-Изменение структуры\n3-Удаление структуры\n4-Сортировка\n5-Поиск по параметру \nДля выходы наберите 9 \n");
		x = scanf_s("%d", &k);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		switch (k) {
		case 1:
			printf("\nВведите параметр поиска: \n1-фамилия, \n2-имя, \n3-область, \n4-район, \n5-город, \n6-улица, \n7-деревня \n "); // Частичный поиск (Предоставление выбора поиска)
			x = scanf_s("%d", &t);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			printf("Введите искомую информацию: ");
			rewind(stdin);
			gets_s(st); // Ввод частичной информации
			printf("\n");
			Poisk(number, n, st, t); // Вызов функции частичного поиска			// Частичный поиск окончен
			PomVivod(number, n);
			break;
		case 2:
			printf("\nВведите номер структуры, которую хотите изменить: ");	// Изменение структуры
			x = scanf_s("%d", &num);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			if (num < n)
				Izmen(&number[num]);
			else
				printf("Структура не найдена ");								// Изменение завершено
			PomVivod(number, n);
			break;
		case 3:
			printf("Введите номер структуры, которую хотите удалить: ");			// Удаление
			x = scanf_s("%d", &num);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			Delete(number, n, num);
			n--;																// Удаление завершено
			PomVivod(number, n);
			break;
		case 4:
			printf("\nВыберите параметр сортировки: \n1-фамилия 2-имя 3-место жительства \n"); // Сортировка
			x = scanf_s("%d", &num);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			for (i = 0; i < n; ++i)
				for (j = n - 1; j > i; --j) {
					t = Str(&number[j - 1], &number[j], num);
					if (t > 0) {
						Change(&number[j - 1], &number[j], num);
					}
				}																			// Сортировка закончилась
			PomVivod(number, n);
			break;
		case 5:
			printf("\nВведите параметр поиска: \n1-фамилия, \n2-имя, \n3-область, \n4-район, \n5-город, \n6-улица, \n7-деревня, \n8-дом, \n9-квартира\n "); // Поиск по параметру
			x = scanf_s("%d", &num);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			printf("Введите искомую информацию: ");
			st[1] = '\0';
			if (num == 9 || num == 8) {
				x = scanf_s("%d", &t);
				if (!x) {
					printf("Данные введены не верно ");
					return 1;
				}
			}
			else {
				rewind(stdin);
				gets_s(st);
			}
			for (i = 0; i < n; i++)
				switch (num) {
				case 1:
					j = strcmp(number[i].name, st);
					if (j == 0)
						Vivod(number, i);
					break;
				case 2:
					j = strcmp(number[i].surname, st);
					if (j == 0)
						Vivod(number, i);
					break;
				case 3:
					if (number[i].hometype == 2) {
						j = strcmp(number[i].hom.bb.region, st);
						Pomoch(number, j, i);
					}
					if (number[i].hometype == 3) {
						j = strcmp(number[i].hom.cc.region, st);
						Pomoch(number, j, i);
					}
					if (number[i].hometype == 4) {
						j = strcmp(number[i].hom.dd.region, st);
						Pomoch(number, j, i);
					}
					break;
				case 4:
					if (number[i].hometype == 3) {
						j = strcmp(number[i].hom.cc.district, st);
						Pomoch(number, j, i);
					}
					if (number[i].hometype == 4) {
						j = strcmp(number[i].hom.dd.district, st);
						Pomoch(number, j, i);
					}
					break;
				case 5:
					if (number[i].hometype == 2) {
						j = strcmp(number[i].hom.bb.city, st);
						Pomoch(number, j, i);
					}
					if (number[i].hometype == 3) {
						j = strcmp(number[i].hom.cc.city, st);
						Pomoch(number, j, i);
					}
					break;
				case 6:
					if (number[i].hometype == 1) {
						j = strcmp(number[i].hom.aa.street, st);
						Pomoch(number, j, i);
					}
					if (number[i].hometype == 2) {
						j = strcmp(number[i].hom.bb.street, st);
						Pomoch(number, j, i);
					}
					if (number[i].hometype == 3) {
						j = strcmp(number[i].hom.cc.street, st);
						Pomoch(number, j, i);
					}
					break;
				case 7:
					if (number[i].hometype == 4) {
						j = strcmp(number[i].hom.dd.village, st);
						Pomoch(number, j, i);
					}
					break;
				case 8:
					if (number[i].hometype == 1) {
						if (number[i].hom.aa.home == t) Vivod(number, i);
					}
					if (number[i].hometype == 2) {
						if (number[i].hom.bb.home == t) Vivod(number, i);
					}
					if (number[i].hometype == 3) {
						if (number[i].hom.cc.home == t) Vivod(number, i);
					}
					if (number[i].hometype == 4) {
						if (number[i].hom.dd.home == t) Vivod(number, i);
					}
					break;
				case 9:
					if (number[i].hometype == 1) {
						if (number[i].hom.aa.flat == t) Vivod(number, i);
					}
					if (number[i].hometype == 2) {
						if (number[i].hom.bb.flat == t) Vivod(number, i);
					}
					if (number[i].hometype == 3) {
						if (number[i].hom.cc.flat == t) Vivod(number, i);
					}
					break;
				}										// Конец поиска
			PomVivod(number, n);
			break;
		}
	} while (k != 9);
	free(number);	
	return 0;
}