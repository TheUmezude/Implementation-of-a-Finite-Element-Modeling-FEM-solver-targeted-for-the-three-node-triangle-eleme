#pragma once
/*
This Program was Developed by Nkemdilim Okechukwu Umezude, with assistance from Hoang Phan and Taoufik Touti.
The entirety of the project process and technique was conceived by Nkemdilim Okechukwu Umezude
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#ifndef Voids_h
#define Voids_h
using namespace std;
struct Vertex {
	int order;
	double x, y, z;

};

//double Kglobal[8][8] = { 0 };
//
//int** Kg = new int*[number_of_nodes*2];
//for (int i = 0; i < number_of_nodes * 2; ++i)
//	Kg[i] = new int[number_of_nodes * 2];

struct Face {
	int index;
	Vertex V1, V2, V3;

};
void ReadVVX(Vertex& V)
{
	cout << "(" << V.x << "," << V.y << "," << V.z << ")    ";
};
void ReadFace(Face& F)
{
	cout << "Face #" << F.index << "    ";
	cout << "Vertex" << F.V1.order << " "; ReadVVX(F.V1);
	cout << "Vertex" << F.V2.order << " "; ReadVVX(F.V2);
	cout << "Vertex" << F.V3.order << " "; ReadVVX(F.V3);
	cout << endl;
}
double Area(Face F);
double Area(Face F)
{
	double Area = ((F.V2.x * F.V3.y - F.V3.x * F.V2.y) + (F.V3.x * F.V1.y - F.V1.x * F.V3.y) + (F.V1.x * F.V2.y - F.V2.x * F.V1.y)) / 2;
	return Area;
}
void B_Reading(std::pair <std::pair<int, int>, double>& T);
void B_Reading(std::pair <std::pair<int, int>, double>& T)
{
	std::pair<int, int> index = T.first;
	cout << "(" << index.first << "," << index.second << ")" << "  " << T.second << endl;
	//	Kglobal[index.first][index.second] += T.second;
}
void Global_Assigning(std::vector<std::pair<std::pair<int, int>, double>>& GF, std::pair <std::pair<int, int>, double>& T);
void Global_Assigning(std::vector<std::pair<std::pair<int, int>, double>>& GF, std::pair <std::pair<int, int>, double>& T)
{
	std::vector<std::pair<std::pair<int, int>, double>>::iterator itr;
	bool pairExists = false;
	for (itr = GF.begin(); itr != GF.end(); itr++)
	{
		if (itr->first.first == T.first.first && itr->first.second == T.first.second)
		{
			pairExists = true;
		}
	}

	if (pairExists)
	{
		for (itr = GF.begin(); itr != GF.end(); itr++)
		{
			if (itr->first.first == T.first.first && itr->first.second == T.first.second)
			{
				itr->second = itr->second + T.second;
				break;
			}
		}
	}
	else
	{
		GF.push_back(T);
	}
}
void Global_Reading(std::vector<std::pair<std::pair<int, int>, double>>& GF);
void Global_Reading(std::vector<std::pair<std::pair<int, int>, double>>& GF)
{
	std::vector<std::pair<std::pair<int, int>, double>>::iterator itr;
	for (itr = GF.begin(); itr != GF.end(); itr++)
	{
		B_Reading(*itr);
	}
}
void B_Formulate(std::pair <std::pair<int, int>, double>& T, std::vector<int> &Constrained_Vector);
void B_Formulate(std::pair <std::pair<int, int>, double>& T, std::vector<int> &Constrained_Vector)
{
	std::pair<int, int> index = T.first;
	bool isZero = false;

	for (auto i = Constrained_Vector.begin(); i != Constrained_Vector.end(); i++) {
		if ((*i * 2 - 1) == index.first || (*i * 2) == index.first || (*i * 2 - 1) == index.second || (*i * 2) == index.second) {
			isZero = true;
		}
	}

	if (isZero) {
		cout << "(" << index.first << "," << index.second << ")" << "  " << 0 << endl;
	}
	else {
		cout << "(" << index.first << "," << index.second << ")" << "  " << T.second << endl;
	}
}
void Global_Formulate(std::vector<std::pair<std::pair<int, int>, double>>& GF, std::vector<int> &Constrained_Vector);
void Global_Formulate(std::vector<std::pair<std::pair<int, int>, double>>& GF, std::vector<int> &Constrained_Vector)
{
	std::vector<std::pair<std::pair<int, int>, double>>::iterator itr;
	for (itr = GF.begin(); itr != GF.end(); itr++)
	{
		B_Formulate(*itr, Constrained_Vector);
	}
}
double* inverse(double matrix[], int size);
double* inverse(double matrix[], int size)
{
	int i, j, k, n = size;
	double* inversedMatrix = new double[2 * n * n];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			inversedMatrix[(i * 2 * n) + j] = matrix[(i * n) + j];
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = n; j < 2 * n; j++)
		{
			if (i == j - n)
				inversedMatrix[i * 2 * n + j] = 1;
			else
				inversedMatrix[i * 2 * n + j] = 0;
		}
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < 2 * size; ++j) {
			//cout << inversedMatrix[i * 2 * size + j] << " ";
		}
		//cout << endl;
	}
	for (i = 0; i < n; i++)
	{
		double t = inversedMatrix[i * 2 * n + i];
		for (j = i; j < 2 * n; j++)
			inversedMatrix[i * 2 * n + j] = inversedMatrix[i * 2 * n + j] / t;
		for (j = 0; j < n; j++)
		{
			if (i != j)
			{
				t = inversedMatrix[j * 2 * n + i];
				for (k = 0; k < 2 * n; k++)
					inversedMatrix[j * 2 * n + k] = inversedMatrix[j * 2 * n + k] - t * inversedMatrix[i * 2 * n + k];
			}
		}
	}

	double* resultMatrix = new double[n * n];
	for (i = 0; i < n; i++)
	{
		for (j = n; j < 2 * n; j++)
		{
			resultMatrix[i * n + j - n] = inversedMatrix[i * 2 * n + j];
		}
	}

	return resultMatrix;
}
#endif /* Voids_h */