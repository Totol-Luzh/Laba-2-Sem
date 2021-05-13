#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct info {
	char skobka;
	info* next_el;
};

void Copy(char* str, info* top, int n, int k) { // Функция сравнения операторов и слов
	int i, j, l=k-n, x, kl;
	char table[][10] = { "for", "while", "do", "if", "switch"};
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
		if (kl == l && l!=0) printf("\nСовпадение по оператору %s", table[j]);
		//printf("\n");
	}


}

void Poisk(char* str, info* top) { // Функция поиск слов и операторов
	int i=0, n, k, l;
	while (str[i] != '\0' && str[i] != '\n') {
		while (str[i] == ' ' || str[i] == '	' || str[i] == '(' || str[i] == '{' && str[i] != '\t') {
			if (str[i] == '{' || str[i]=='}')
				Copy(str, top, i, i);
			if (str[i] == '(')
				while (str[i] != ')')i++;
			i++;
		}
		n = i;
		while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0' && str[i] != '(' && str[i] != '{' && str[i] != '\t') i++;
		k = i - 1;
		l = n;
		/*printf("\n");
		for (l; l < k - n; l++)
			printf("%c", str[l]);
		printf("\n");*/
		Copy(str, top, n, k);
	
	}



}

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* s;
	info* top = NULL;
	int i, j, k;
	char str[100];
	fopen_s(&s, "CodeC.txt", "a+");
	if (!s) {
		printf("Файл не был создан");
		return 1;
	}
	for (i = 0;; i++) {
		if (fgets(str, 100, s) == NULL) break;
		printf("[%d] %s", i, str);
		k = i;
		Poisk(str, top);
	}














	fclose(s);
	return 0;
}