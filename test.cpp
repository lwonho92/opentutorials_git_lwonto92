#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

#define ROW 1
#define N	3
#define COL 8

char DELIM[256] = "{};, ";

void hypothesis(double **w, double **x, double **h);
void train(double **w, double **x, double *y, double alpha);

int main(void)
{
	double **w = NULL;
	double **x = NULL;
	double y[COL] = { 0, 0, 0, 0, 0, 0, 1, 1 };

	char line[256] = { 0 };
	char *tmp;
	ifstream myfile("input2.txt");

	double sum = 0;
	double alpha = 0.001;

	double check1[3] = { 1, 2, 2 };
	double check2[3] = { 1, 5, 5 };
	double check3[3] = { 1, 4, 3 };
	double check4[3] = { 1, 3, 5 };

	int i, j;

	w = new double*[ROW];
	x = new double*[N];

	for (i = 0; i < ROW; i++)
		w[i] = new double[N];
	for (i = 0; i < N; i++)
		x[i] = new double[COL];


	for (i = 0; i < ROW; i++)
		for (int j = 0; j < N; j++)
			cin >> w[i][j];

	if (myfile.is_open())
	{
		for (i = 0; myfile.getline(line, sizeof line); i++)
		{
			tmp = strtok(line, DELIM);
			x[i][0] = atoi(tmp);
			for (j = 1; tmp = strtok(NULL, DELIM); j++)
				x[i][j] = atoi(tmp);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < 2001; i++)
		train(w, x, y, alpha);
	for (i = 0; i < N; i++)
		cout << w[0][i] << '\t';
	cout << endl;

	//////////////////////////////////////////////////////////////////////////////////////////////////
	sum = 0;
	for (j = 0; j < N; j++)
		sum += w[0][j] * check1[j];
	cout << 1.0 / (1 + exp(-sum)) << endl;

	sum = 0;
	for (j = 0; j < N; j++)
		sum += w[0][j] * check2[j];
	cout << 1.0 / (1 + exp(-sum)) << endl;

	sum = 0;
	for (j = 0; j < N; j++)
		sum += w[0][j] * check3[j];
	cout << 1.0 / (1 + exp(-sum)) << endl;

	sum = 0;
	for (j = 0; j < N; j++)
		sum += w[0][j] * check4[j];
	cout << 1.0 / (1 + exp(-sum)) << endl;

	return 0;
}

void hypothesis(double **w, double **x, double **h)
{
	int i, j, k;
	double sum;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			sum = 0;
			for (k = 0; k < N; k++)
			{
				sum += w[i][k] * x[k][j];
			}
			h[i][j] = 1 / (1 + exp(-sum));
		}
	}
}
void train(double **w, double **x, double *y, double alpha)
{
	double **h = NULL;
	int i, j;
	double sum;

	h = new double*[ROW];
	for (i = 0; i < ROW; i++)
	{
		h[i] = new double[COL];
		memset(h[i], 0, sizeof(double) * COL);
	}

	hypothesis(w, x, h);

	for (i = 0; i < N; i++)
	{
		sum = 0;
		for (j = 0; j < COL; j++)
			sum += (y[j] - h[0][j]) * x[i][j];
		w[0][i] += alpha * sum / COL;
	}
}