#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct tree{
	int number;
	int coat;
	tree* left, *right;
};

struct stack {
	tree* cell;
	stack* next;
};

void Put(stack** memory, tree* ukazatel){
	stack* n=NULL;
	n = (stack*)calloc(1, sizeof(stack));
	if (!n) {
		printf("Ошибка выделения памяти ");
		//return 1;
	}
	if (n != NULL) {
		n->cell = ukazatel;
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

tree* Take(stack** memory) {
	stack* assistant=NULL;
	tree*n = NULL;
	assistant = *memory;
	*memory = assistant->next;
	if (assistant->next == NULL)
		*memory = NULL;
	n = assistant->cell;
	assistant->next = NULL;
	free(assistant);
	return n;
}

/*int Info(steak* memory) {
	int i=0;
	steak* helper;
	while (memory != NULL) {
		helper = memory->next;
		memory = helper;
		i++;
	}
	return i;
}*/

void Dublication(tree* source, tree** copy, stack** memory) {
	tree* helper, * assistant, * n, * current;
	int i, j;
	Free(copy);
	for (j = 0; *memory != NULL || source != NULL; j++) {
	//for (j = 0; j < 4; j++){
	while (source == NULL)
			source = Take(memory);
		n = NULL;
		n = (tree*)calloc(1, sizeof(tree));
		if (!n)
			printf("Ошибка выделения памяти ");
		if (n != NULL) {
			n->number = source->number;
			n->coat = source->coat;
			n->left = NULL;
			n->right = NULL;
			if (*copy == NULL)
				*copy = n;
			else {
				current = *copy;
				for (i = 0;; i++) {
					if (current->number == source->number) {
						current->coat = current->coat + 1;
						free(n);
						break;
					}
					if (source->number < current->number) {
						if (current->left == NULL) {
							current->left = n;
							break;
						}
						helper = current->left;
					}
					else {
						if (current->right == NULL) {
							current->right = n;
							break;
						}
						helper = current->right;
					}
					current = helper;
				}
			}
			n = NULL;
			assistant = source->right;
			if(source->left!=NULL)
				Put(memory, source->left);
			source = assistant;

		}
	}
}

void Output(tree* trees, int level) {
	if (trees) {
		Output(trees->right, level + 1);
		for (int i = 0; i < level; i++)
			printf("     ");
		printf(" %d(%d) \n", trees->number, trees->coat);
		Output(trees->left, level + 1);
	}

}

void Del_el(tree* current, tree* previous) {
	tree* assistant=NULL, * helper=NULL, *n;
	if (current->coat > 1)
		current->coat = current->coat - 1;
	else {
		if (previous->number < current->number) {
			if(current->right!=NULL)
				assistant = current->right;
			current->right = NULL;
			if(current->left!=NULL)
				helper = current->left;
			current->left = NULL;
			current = helper;
			if (current != NULL) {
				while (current->right != NULL) {
					helper = current->right;
					current = helper;
				}
				current->right = assistant;
			}
			n = previous->right;
			if (current != NULL)
				previous->right = current;
			else
				previous->right = assistant;
			free(n);
		}
		else {
			if (current->left != NULL)
				assistant = current->left;
			current->left = NULL;
			if (current->right != NULL)
				helper = current->right;
			current->right = NULL;
			current = helper;
			if (current != NULL) {
				while (current->left != NULL) {
					helper = current->left;
					current = helper;
				}
				current->left = assistant;
			}
			n = previous->left;
			if (current != NULL)
				previous->left = current;
			else
				previous->left = assistant;
			free(n);
		}
	}
}

void Del_main(tree** main){
	tree* helper=NULL,* assistant=NULL, * current=*main, *n;
	if (current->right == NULL && current->left == NULL)
		main = NULL;
	if (current->right != NULL){
		assistant = current->right;
		current->right = NULL;
	}
	if (current->left != NULL) {
		helper = current->left;
	}

}

void Search(tree** p, int sought, int k) {
	tree* helper, *assistant=*p, *current=*p, *n=NULL;
	int i;
	for (i = 0;; i++) {
		if (current->number == sought) {
			printf(" %d(%d) \n", current->number, current->coat);
			break;
		}
		if (sought < current->number) {
			if (current->left == NULL) {
				printf("Элемент не найден");
				break;
			}
			helper = current->left;
		}
		else {
			if (current->right == NULL) {
				printf("Элемент не найден");
				break;
			}
			helper = current->right;
		}
		assistant = current;
		current = helper;
	}
	if (k == 1) {//Удаление элемента
		/*if (current == assistant)
			Del_main(p);
		else*/
			Del_el(current, assistant);
	}
}
int Create(tree** p, int k) {
	tree* current=NULL, *n= NULL, * helper= NULL;
	int i;
	n = (tree*)calloc(1, sizeof(tree));
	if (!n) {
		printf("Ошибка выделения памяти ");
		return 1;
	}
	n->number = k;
	n->coat = 1;
	n->left = NULL;
	n->right = NULL;
	if (*p == NULL) 
		*p = n;
	else {
		current = *p;
		//while (current->left!=NULL || current->right!=NULL) {
		for(i=0;;i++){
			if (current->number == k) {
				current->coat = current->coat + 1;
				free(n);
				return 0;
			}
			if (k < current->number) {
				if (current->left == NULL) {
					current->left = n;
					return 0;
				}
				helper = current->left;
			}
			else {
				if (current->right == NULL) {
					current->right = n;
					return 0;
				}
				helper = current->right;
			}
				current = helper;
		}
	}
	return 0;
}

void Reading(char* str, tree** p) {
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
		Create(p, x);
	}
}

void Free(tree** source){
	tree* helper, * current=*source;
	while (current->right != NULL) {
		helper = current->right;
		Search(source, helper->number, 1);
	}
	while (current->left != NULL) {
		helper = current->left;
		Search(source, helper->number, 1);
	}
	//while(source!=NULL)
	Del_main(source);
}

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i, k, x, f;
	char str[100];
	tree* source = NULL, * copy = NULL;
	stack* memory=NULL;
	FILE* s;
	fopen_s(&s, "Tree.txt", "r");
	if (!s) {
		printf("Файл не был создан");
		return 1;
	}
	/*for (i = 0;; i++) {
		if (fgets(str, 100, s) == NULL) {
			//puts("no line");
			break;
		}
		Reading(str, &source);
	}
	Dublication(source, &copy, &memory);
	Output(source, 0);
	Output(copy, 0);*/
	do {
		printf("\nМеню:\n1-Вывод дерева\n2-Вывод копии дерева\n3-Создание дерева из файла\n4-Добавление элемента в дерево\n5-Создание копии дерева\n6-Поиск эелемента в дереве\n7-Удаление элемента\n8-Очистка дерева\nДля выходы наберите 9 \n");
		x = scanf_s("%d", &k);
		if (!x) {
			printf("Данные введены не верно ");
			return 1;
		}
		system("CLS");
		switch (k) {
		case 1:
			if (source == NULL)
				printf("Дерево пустое\n");
			printf("\n");
			Output(source, 0);
			break;
		case 2:
			if (copy == NULL)
				printf("Дерево пустое\n");
			printf("\n");
			Output(copy, 0);
			break;
		case 3:
			for (i = 0;; i++) {
				if (fgets(str, 100, s) == NULL) {
					//puts("no line");
					break;
				}
				Reading(str, &source);
			}
			break;
		case 4:
			printf("Введите значение элемента: ");
			x = scanf_s("%d", &f);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			Create(&source, f);
			break;
		case 5:
			Dublication(source, &copy, &memory);
			break;
		case 6:
			printf("Введите искомый элемент: ");
			x = scanf_s("%d", &f);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			Search(&source, f, 0);
			break;
		case 7:
			printf("Введите элемент, который хотите удалить: ");
			x = scanf_s("%d", &f);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			Search(&source, f, 1);
			break;
		case 8:
			printf("Введите номер дерева, которое хотите удалить:\n1-Удалить основное дерево\n2-Удалить копию дерева\n");
			x = scanf_s("%d", &f);
			if (!x) {
				printf("Данные введены не верно ");
				return 1;
			}
			switch (f) {
			case 1:
				Free(&source);
				break;
			case 2:
				Free(&copy);
				break;
			}
			break;
		}
	} while (k != 9);
	fclose(s);
	return 0;
}