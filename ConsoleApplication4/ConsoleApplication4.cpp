// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*Массивы динамические двумерные.
Вриант № 47*/
#include <iostream>
#include <math.h>
#include <locale.h>

using namespace std;
typedef int telem;          //объявление типа элемента массива;
typedef telem* tmas;        //объявление типа "указатель на telem";
typedef telem* tstr;		//определение типа "указатель на telem"
typedef tstr* tmatr;		//тип "указатель на указатель на telem"

void setNumbersWorkA(tmas a, int n);
telem getABSEvenNumb(tmas a, int n, int maxOddInd);
int getMaxOddInd(tmas a, int n);
telem getSumOddNumb(tmas a, int n, int maxOddInd);
void input_matr(tmatr a, int str);
telem sumNegativeNumbs(tmatr a, int size);

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа №9 Динамические массивы: Вариант №47\n" << endl;
	cout << "А) Определить произведение абсолютных значений элементов массива с чётными номерами" <<
		"\n   и сумму значений элементов с нечётными номерами, номера которых больше номера первого элемента" <<
		" \n   с наибольшим неположительным значением " << endl;
	//Ввод исходных данных;
	cout << "\nВведите колличество элементов массива: ";
	int n;
	telem absSum = 0;
	int maxOddInd = 0;
	telem oddSum = 0;
	cin >> n;
	tmas array = new telem[n];   /*создание переменной-указателя на telem,
					выделение динамической памяти под массив
					адрес начала области заносится в a*/
	setNumbersWorkA(array, n);
	maxOddInd = getMaxOddInd(array, n);
	absSum = getABSEvenNumb(array, n, maxOddInd);
	cout << "\nПроизведение абсолютных значений элементов массива с четными номерами: " << absSum << endl;
	if (absSum == 0)
	{
		cout << "\nУмножение на 0"
			<< "или колличество элементов, в интервале = " << absSum << endl;
	}
	oddSum = getSumOddNumb(array, n, maxOddInd);
	cout << "\nCуммa значений элементов с нечётными номерами: " << oddSum << endl;

	cout << "\nБ) В заданной квадратной матрице размера 2n×2n найти сумму отрицательных значений " <<
		"\n   элементов области 7, умноженную на их количество." << endl;
	int a;
	telem sumNegative = 0;
	cout << "\nВведите число n: ";
	cin >> a;
	int size = a * 2;
	tmatr matr;				//переменная-указатель на указатель на telem
	matr = new tstr[size];		/*выделение динамической памяти под массив
					указателей на строки массива*/
	for (int i = 0; i < size; i++)	//выделение памяти под каждую строку:
		*(matr + i) = new telem[size];	/*каждому элементу массива указателей
							на строки присваивается адрес начала
							области памяти, выделяемой под строку*/
	input_matr(matr, size);
	sumNegative = sumNegativeNumbs(matr, size);
	cout << "\nСумма отрицательных значений матрицы, умноженнная на их колличество: " << sumNegative << endl;

	//Освобождение динамической памяти
	for (int i = 0; i < size; i++)
		delete* (matr + i);
	delete[]matr;

	return 0;
}

void setNumbersWorkA(tmas a, int length) {                            //функция для ввода элементов одномерного массива;
	cout << "Введите одной строкой элементы массива из ";
	cout << length << " чисел и нажмите <Enter>" << endl << " ";
	for (int i = 0; i < length; i++)
		cin >> a[i];
}

telem getABSEvenNumb(tmas array, int size, int maxOddInd) {                              /*функция определения произведения
																		абсолютных величин элементов массива
																		с четными номерами*/
	if (maxOddInd % 2 != 0)
	{
		maxOddInd += 1;                                                //если индекс нечетный, то добавляем 1, чтобы начать цикл с четного числа;
	}
	else
	{
		maxOddInd += 2;                                                //если индекс четный, то прибавляем 2, т.к. это число не должно входить в интервал;
	}
	telem absSum = 1;                                                  //переменную приравниваю к 1, чтобы умножение сработало верно;
	int numb = 0;                                                      //добавил счетчик элементов, удовлетворяющих условиям задачи;
	for (int i = maxOddInd; i < size; i += 2)
	{
		numb++;
		absSum *= abs(array[i]);
	}
	if (!numb)                                                     //если нет элментов, удовлетворяющим условиям задачи, то функция вернет 0;
	{
		absSum = 0;
	}
	return absSum;
}

int getMaxOddInd(tmas array, int length) {
	telem min = 0;
	telem maxOdd = 0;
	int maxOddInd = 0;
	for (int i = 0; i < length; i++)
	{
		min = array[i];
		for (int j = 0; j < length; j++)
		{
			if (array[j] < 0)                        //в цикл запускаются только те элементы, которые меньше 0, т.е. отрицательные;
			{
				maxOdd = array[j];
				if (min < maxOdd) {                  /*находим МАКСИМАЛЬНОЕ ОТРИЦАТЕЬНОЕ число, проверка проходит ТОЛЬКО для отрицательных чисел,
														из них мы ищем максимальное, которое ближе всего к 0;*/
					min = maxOdd;
					maxOddInd = j;

				}
			}
		}
	}
	return maxOddInd;
}

telem getSumOddNumb(tmas array, int length, int maxOddInd) {                          /*функция определения суммы значений элементов с нечётными номерами,
																		 номера которых больше номера первого элемента
																		 с наибольшим неположительным значением */
	if (maxOddInd % 2 == 0)
	{
		maxOddInd -= 1;
	}
	telem sum = 0;
	for (int i = maxOddInd + 2; i < length; i += 2)
	{
		sum = sum + array[i];
	}
	return sum;
}

void input_matr(tmatr a, int size)                                   //функция для ввода элементов двумерного массива;
{
	cout << "Введите построчно через пробел элементы";
	cout << "массива размера " << size << "х" << size;
	cout << "\n После ввода строки нажимайте <Enter>" << endl;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cin >> *(*(a + i) + j);
}

telem sumNegativeNumbs(tmatr matr, int size) {                        /*функция определения суммы отрицательных
																			  значений элементов, умноженных на их количество */
	telem min = 0;
	telem sum = 0;
	int numb = 0;
	int n = size / 2;
	for (int i = n; i < size; i++) {
		for (int j = 0; j < n; j++) {
			if (matr[i][j] < 0) {
				sum += matr[i][j];
				numb++;
			}
			else continue;
		}
		n--;
	}
	sum *= numb;
	return sum;
}