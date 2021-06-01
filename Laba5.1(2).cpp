#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//struct info {
//	char skobka;
//	info* next_el;
//};

struct stack {
	char cell;
	stack* next;
};

int row = 0, column = 0, number = 0;
char ms[50][255];

void Put(stack** memory, char info) {
	stack* n = NULL;
	n = (stack*)calloc(1, sizeof(stack));
	if (!n) {
		printf("Ошибка выделения памяти ");
		//return 1;
	}
	if (n != NULL) {
		n->cell = info;
		n->next = NULL;
		if (*memory == NULL)
			*memory = n;
		else {
			//assistant = *memory;
			//*memory = n;
			n->next = *memory;
			*memory = n;
		}
	}
}

char Take(stack** memory) {
	stack* assistant = NULL;
	char n = NULL;
	assistant = *memory;
	*memory = assistant->next;
	if (assistant->next == NULL)
		*memory = NULL;
	n = assistant->cell;
	assistant->next = NULL;
	free(assistant);
	return n;
}

int Print_stack(stack* memory) {
	stack* helper;
	int i=0;
	char info;
	while (memory != NULL) {
		info = memory->cell;
		helper = memory->next;
		memory = helper;
		printf("%c", info);
		i++;
	}
	return i;
}

int Copy(char* str, stack** top, int n, int k) { // Функция сравнения операторов и слов
	int i, j, l=k-n+1, x, kl;
	char table[][10] = { "if", "for", "do", "while", "switch", '{', '}'};
	for(j=0;j<5;j++){
		//printf("\n");
		x = n; kl = 0;
		for(i=0;i<l+1;i++){
			if (str[x] == table[j][i]) { 
				printf("%c", str[x]);
				kl++; 
			}
			else
				break;
			x++;
		}
		if (kl == l && l != 0) {
			printf("\nСовпадение по оператору %s", table[j]);
			return j+1;//Отправляется номер совпадающей строки
		}
	}
	return 8;//Если не найдено сходства
}

int Scan(stack **top){
	int n, k, l, x = 0, g = 0;
	char str[10];
	for (row = 0; row<50; row++) {
		column = 0;
		while (ms[row][column] != '\0' && ms[row][column] != '\n') {
			while (ms[row][column] == ' ' || ms[row][column] == '(' || ms[row][column] == '{' || ms[row][column] == '}' || ms[row][column] != '\t') {
				if (ms[row][column] == '{' || ms[row][column] == '}') {
					x = Copy(ms[row], top, column, column);
					return x;
				}
				if (ms[row][column] == '(')
					while (ms[row][column] != ')')column++;
				column++;
			}
			n = column;
			while (ms[row][column] != ' ' && ms[row][column] != '\n' && ms[row][column] != '\0' && ms[row][column] != '(' && ms[row][column] != '{' && ms[row][column] != '\t' && ms[row][column] != ';') column++;
			k = column - 1;
			l = n;
			x = Copy(ms[row], top, n, k);
			if(x!=8)
				return x;
		}
	}
}

void Operator(stack** top) {
	int k = 0;
	char symbol;
	if(number==0)
		number =Scan(top);
	if (number == 1) {		// Для if
		Put(top, '1');
		number = Scan(top);
		if (number == 6) {
			number = Scan(top);
			while (number != 7) {
				Operator(top);
				number = Scan(top);
			}
		}
		else Operator(top);
		symbol = Take(top);
		if (symbol != '1')
			printf("Error \n");
	}
	if (number == 2) {		//Для for
		Put(top, '2');
		if (Scan(top) == 6)
			while (Scan(top) != 7)
				Operator(top);
		else Operator(top);
		symbol = Take(top);
		if (symbol != '2')
			printf("Error \n");
	}
	if (number == 3) {		//Для do
		Put(top, '3');
		if(Scan(top)!=6)
			printf("Error \n");
		while (Scan(top) != 7)
			 Operator(top);
		if(Scan(top)!=4)
			printf("Error \n");
		symbol = Take(top);
		if (symbol != '3')
			printf("Error \n");
	}
	if (number == 4) {		//Для while
		Put(top, '4');
		if (Scan(top) == 6)
			while (Scan(top) != 7)
				Operator(top);
		else Operator(top);
		symbol = Take(top);
		if (symbol != '4')
			printf("Error \n");
	}
	if(Print_stack!=0)
		printf("Error \n");


}

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* s;
	stack* top = NULL;
	int i, k;
	
	fopen_s(&s, "CodeC.txt", "a+");
	if (!s) {
		printf("Файл не был создан");
		return 1;
	}
	for (i = 0;; i++) {
		if (fgets(ms[i], 100, s) == NULL) break;
		printf("\n[%d] %s", i, ms[i]);
		k = i;
		//Poisk(str, &top);
	}
	Operator(&top);














	fclose(s);
	return 0;
}