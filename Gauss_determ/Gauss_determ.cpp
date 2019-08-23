// Gauss_determ.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

void showMassiv(vector<vector<double>>&myVec, const int ROW, const int COL, string &path)
{
	ofstream fout;
	fout.open(path, ofstream::app);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			fout << myVec[i][j] << '\t';
		}
		fout << '\n';
	}
	fout << '\n'; fout << '\n';
}

int main()
{
	setlocale(LC_ALL, "RU");

	string path = "matrix.txt";		// все вычисления в файле
	ofstream fout;
	fout.open(path);
	if (!fout.is_open()) { cout << "Ошибка открытия файла" << endl; }
	else
	{
		cout << "Все вычисления хранятся в файле - " << path << endl;
		cout << endl;
	}

	int n, i = 0, j = 0, k = 0, t = 0, choice;
	cout << "Введите размерность матрицы nxn:\n";
	cin >> n;
	cin.ignore(32767, '\n');

	vector<vector<double>> myVector1(n, vector<double>(n));
	vector<vector<double>> myVector2(n, vector<double>(n));
	vector<vector<double>> myVector3(n, vector<double>(n));
	vector<vector<double>> myVector4(n, vector<double>(n));


	while (n <= 0 && n != 1)
	{
		cout << "Ошибка! Возможно вы ввели недопустимый символ\n Попробуйте еще раз\n"; cin >> n;
	}

	do
	{
		cout << "Хотите ввести числа сами или ввести рандомные? 1 - сами, 2 - рандомные\n";
		cin >> choice;
	} while (choice != 1 && choice != 2);

	const int ROW = n, COL = n; double det = 1;
	srand(time(NULL));

	if (choice == 1)
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				cout << "Введите элемент a " << i << ' ' << j << endl;
				cin >> myVector1[i][j];
				cin.ignore(32767, '\n');
				myVector2[i][j] = myVector1[i][j];
				myVector3[i][j] = myVector2[i][j];
				myVector4[i][j] = myVector3[i][j];
			}
		}
	}
	else if (choice == 2)
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				myVector1[i][j] = rand() % 4;
				if (i % 2 == 0 && j % 2 != 0)
				{
					myVector1[i][j] *= (-1);
				}
				myVector2[i][j] = myVector1[i][j]; myVector3[i][j] = myVector2[i][j];
				myVector4[i][j] = myVector3[i][j];
			}
		}
	}
	showMassiv(myVector1, ROW, COL, path);

	if (myVector1[0][0] == 0 && myVector1[ROW - 1][0] != 0)
	{
		for (int j = 0; j < COL; j++)
		{

			double h = myVector1[0][j];
			myVector1[0][j] = myVector1[ROW - 1][j];
			myVector1[ROW - 1][j] = h;
		}
		det = -1;
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			myVector2[i][j] = myVector1[i][j]; myVector3[i][j] = myVector2[i][j];
			myVector4[i][j] = myVector3[i][j];
		}
	}

	if (myVector1[0][0] != 0)
	{
		for (int i = 1; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (myVector1[i][0] != (-myVector1[i][0]))
				{
					myVector2[i][j] = myVector1[i][j] + (-myVector1[0][j] * (myVector1[i][0] / myVector1[0][0]));
					myVector3[i][j] = myVector2[i][j];
				}
				else
				{
					myVector2[i][j] = (myVector1[i][0] * myVector1[0][j]) - myVector1[i][j];
					myVector3[i][j] = myVector2[i][j];
				}
			}
		}
	}
	showMassiv(myVector2, ROW, COL, path);

	if (myVector2[1][0] == 0 && myVector2[1][1] == 0 && myVector2[1][2] == 0)
	{
		cout << "DETERMINANT = 0";
	}
	if (myVector2[1][1] == 0)
	{
		for (int i = 0; i < ROW; i++)
		{
			myVector2[1][i] += myVector2[2][i];
			myVector3[1][i] = myVector2[1][i];
		}
	}
	for (int i = 2, k = 2; i < ROW, k < ROW; i++, k++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (myVector2[1][1] != 0)
			{
				myVector2[i][j] = myVector2[i][j] + (-myVector2[1][j] * (myVector3[k][1] / myVector2[1][1]));
				myVector1[i][j] = myVector2[i][j];
			}
			//else { cout << "DETERMINANT = 0" << endl; return 0; }
		}
	}
	showMassiv(myVector2, ROW, COL, path);

	if (n == 3)
	{
		if (myVector4[0][0] < 0)
		{
			for (int i = 0; i < ROW; i++)
			{
				det *= myVector2[i][i];
			}
			cout << "DETERMINANT\t=\t" << det * (-1) << endl;
			return 0;
		}
		else
		{
			for (int i = 0; i < ROW; i++)
			{
				det *= myVector2[i][i];
			}
			cout << "DETERMINANT\t=\t" << det << endl;
			return 0;
		}
	}

	if (myVector2[2][0] == 0 && myVector2[2][1] == 0 && myVector2[2][2] == 0 && myVector2[2][3])
	{
		cout << "DETERMINANT = 0";
	}
	if (myVector2[2][2] == 0)
	{
		for (int i = 0; i < ROW; i++)
		{
			myVector2[2][i] += myVector2[3][i];
		}
	}

	for (int i = 3, k = 3; i < ROW, k < ROW; i++, k++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (myVector2[2][2] != 0)
			{
				myVector2[i][j] = myVector2[i][j] + (-myVector2[2][j] * (myVector1[k][2] / myVector2[2][2]));
				myVector3[i][j] = myVector2[i][j];
			}
		}
	}
	showMassiv(myVector2, ROW, COL, path);
	if (n == 4)
	{
		if (myVector4[0][0] < 0)
		{
			for (int i = 0; i < ROW; i++)
			{
				det *= myVector2[i][i];
			}
			cout << "DETERMINANT\t=\t" << det * (-1) << endl; return 0;
		}
		else
		{
			for (int i = 0; i < ROW; i++)
			{
				det *= myVector2[i][i];
			}
			cout << "DETERMINANT\t=\t" << det << endl; return 0;
		}
	}

	if (myVector2[3][3] == 0)
	{
		for (int i = 0; i < ROW; i++)
		{
			myVector2[3][i] += myVector2[4][i];
		}
	}

	if (myVector2[3][0] == 0 && myVector2[3][1] == 0 && myVector2[3][2] == 0 && myVector2[3][3] && myVector2[3][4] == 0)
	{
		cout << "DETERMINANT = 0" << endl;
	}

	/*в этой части кода я уже и подзабыл суть логики, код писал давно и не закомментировал
	должным образом. Но в общем это выглядит так, что в зависимости от размера матрицы, идет проверка на нули
	, тобишь если под главной диагональю все нули, то цикл прекращается, если нет, то продолжаем, и 
	заодно изменяем i,j чтобы не было путаницы*/

	for (int i = 4, k = 4, t = 3; i < ROW, k < ROW, t < ROW; i++, k++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (myVector2[i][i] == 0)
			{
				for (int j = 0; j < ROW; j++)
				{
					myVector2[i][j] += myVector2[k][j];
				}
			}
			if (myVector2[i - 1][i - 1] != 0)
			{
				myVector2[i][j] = myVector2[i][j] + (-myVector2[t][j] * (myVector3[k][t] / myVector2[t][t]));
			}
			if (myVector2[ROW - 1][ROW - 2] == 0 && i == ROW - 1 && j == ROW - 1)
			{
				showMassiv(myVector2, ROW, COL, path);
				if (myVector4[0][0] < 0)
				{
					for (int i = 0; i < ROW; i++)
					{
						det *= myVector2[i][i];
					}
					cout << "DETERMINANT\t=\t" << det * (-1) << endl; return 0;
				}
				else
				{
					for (int i = 0; i < ROW; i++)
					{
						det *= myVector2[i][i];
					}
					cout << "DETERMINANT\t=\t" << det << endl; return 0;
				}
			}
			if (i == ROW - 1 && j == ROW - 1 && myVector2[ROW - 1][ROW - 2] != 0)
			{
				showMassiv(myVector2, ROW, COL, path);
				for (int i = 4; i < ROW; i++)
				{
					for (int j = 3; j < COL; j++)
					{
						myVector3[i][j] = myVector2[i][j];
					}
				}
				t++; // с каждым увеличением t преобразуются в 0 эти же строки с номером i=t
				i = t;
				k = t;
			}
		}
	}

	fout.close();
}


