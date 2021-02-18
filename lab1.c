#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Line
{
	int n; //
	int* str;//
} Line;

typedef struct Matrix
{
	int lines;
	Line* mx;
} Matrix;

Matrix* generate_test_matrix();
int getInt(); //Ввод целочисленного значения
Matrix* input(); //Ввод целой матрицы
void output(const char * msg, Matrix matr); //Вывод матрицы
static inline int find_min_index(Line* line); //Индекс наименьшего элемента массива
Matrix* new_matrix(Matrix *matr); //Создать матрицу на основе предыдущей

int main(int argc, char const *argv[])
{
	Matrix* matr = input(); 
	Matrix* matr2 = new_matrix(matr);
	output("Source", *matr);
	output("Result", *matr2);
	erase(matr);
	erase(matr2);
	return 0;
}

int getInt(){

	int input_value;
	//Ввод, пока не будут числа. gets() для очищения буфера ввода
	for(;fscanf(stdin, "%d", &input_value) == 0; gets())  
		printf("Try again: ");
		
	return input_value;
}

Matrix* input(){

	Matrix* matr = malloc(sizeof(Matrix));
	printf("Enter matrix size: ");
	matr->lines = getInt(); //Вводим количество строк в массиве
	matr->mx = calloc(sizeof(Line), matr->lines); //Выделяем память под массив строк
	for (int i = 0; i < matr->lines; ++i) //Заполняем строки поочерёдно
	{
		Line* line = &matr->mx[i];
		printf("Enter size of line #%d: ", i);
		line->n = getInt(); //Ввод кол-ва элементов в строке
		line->str = calloc(sizeof(int), matr->mx[i].n); //Выделяем память под строку
		for (int k = 0; k < line->n; ++k) //Проход по всей строке
		{
			printf("Enter(%d): ", k);
			line->str[k] = getInt(); //Вводим элемент в строке
		}
	}

	return matr;
}


void output(const char * msg, Matrix matr){

	printf("---------------------------------------%s\n", msg);
	for (int i = 0; i < matr.lines; ++i) //Проход по всем строкам
	{
		for (int j = 0; j < matr.mx[i].n; ++j) //Проход по всем элементам в строке
			printf("%d ", matr.mx[i].str[j]);
		printf("\n");
	}
	printf("---------------------------------------\n");
}

void erase(Matrix* matr){

	for (int i = 0; i < matr->lines; ++i) //Проход по всем строкам
		free(matr->mx[i].str);		
	free(matr->mx);		

}

static inline int find_min_index(Line* line)
{
	int min_index = 0;
	for (int i = 0; i < line->n; ++i) // Проход по всем элементам в строке
		if (line->str[i] < line->str[min_index]) //Если элемент меньше наименьшего
			min_index = i; //То он и становится наименьшим
	return min_index;
}

Matrix* new_matrix(Matrix *matr){

	Matrix* tmp = malloc(sizeof(Matrix)); //
	tmp->mx = calloc(sizeof(Line), matr->lines);	
	tmp->lines = matr->lines;
	int min_index;
	for (int l = 0; l < matr->lines; ++l) //Проход по всем строкам "старой" матрицы
	{
		Line* old_line = &matr->mx[l];			
		Line* new_line = &tmp->mx[l];		
		min_index = find_min_index(old_line); //Находим индекс наименьшего элемента			
		new_line->n = old_line->n - min_index; //Находим кол-во элементов в новой строке
		new_line->str = calloc(sizeof(int), new_line->n); //Выделяем память под строку

		for (int i = 0; i < new_line->n; ++i) //Заполнем строку из старой матрицы
			new_line->str[i] = old_line->str[i+min_index];
		
		//? memcpy((void*)(new_line->str), old_line->str+min_index, new_line->n);
	}	

	return tmp;
}

Matrix* generate_test_matrix(){

	Matrix* matr = malloc(sizeof(Matrix));
	int line_size[] = {4, 10, 8, 5, 7};
	int lines[][10] = {
		{100, 67, 16, 87, 74, 84, 28, 73, 71, 21},
		{ 90, 36, 27,  3, 68, 96, 66, 39, 18, 37},
		{ 31, 63, 69, 76, 35, 54, 59, 86, 13, 25},
		{ 64,  5, 48, 97, 32, 24, 80, 44,  8, 20},
		{  1, 29, 22,  7, 51, 42, 11, 58, 30, 98},
		{ 23, 60, 83, 46, 56, 52, 85, 88, 43, 41},
		{ 45, 99,  4, 15, 53, 34, 12, 49, 78, 50},
		{ 61, 19, 40, 81, 65, 10,  9, 77, 75, 70},
		{  2, 26, 47, 14, 89, 57, 33, 95, 79, 93},
		{  1, 91, 38, 82, 17, 94, 92,  6, 62, 72}
	};

	matr->lines = sizeof(line_size) / sizeof(int);
	matr->mx = calloc(sizeof(Line), matr->lines);
	for (int i = 0; i < matr->lines; ++i)
	{
		Line* line = &matr->mx[i];
		line->n = line_size[i];
		line->str = calloc(sizeof(int),line->n);
		for (int j = 0; j < line->n; ++j)
			line->str[j] = lines[i][j];
	}

	return matr;
}