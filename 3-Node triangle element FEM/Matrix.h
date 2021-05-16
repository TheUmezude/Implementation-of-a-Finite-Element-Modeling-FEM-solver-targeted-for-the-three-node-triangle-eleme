#pragma once
/*
This Program was Developed by Nkemdilim Okechukwu Umezude, with assistance from Hoang Phan and Taoufik Touti.
The entirety of the project process and technique was conceived by Nkemdilim Okechukwu Umezude
*/

#include "Voids.h"
#include <math.h>
#ifndef Matrix_h
#define Matrix_h
void Global_Stiffness_Matrix(int size, double thickness, double v, double E, std::vector<Face> VF);
void Global_Stiffness_Matrix(int size, double thickness, double v, double E, std::vector<Face> VF)
{

	//std::map<int, std::map<int, int> > mymap;

	//mymap[9][2] = 7;
	//std::cout << mymap[9][2] << std::endl;

	//if (mymap.find(9) != mymap.end() && mymap[9].find(2) != mymap[9].end()) {
	//	std::cout << "My map contains a value for [9][2]" << std::endl;
	//}
	//else {
	//	std::cout << "My map does not contain a value for [9][2]" << std::endl;
	//}

	int CN;
	int CountCN = 0;
	cout << "Input Number of Constrained Nodes" << endl;
	cin >> CN;
	int noOfPutForceNodes;
	cout << "Input Number of Nodes you want to put force into" << endl;
	cin >> noOfPutForceNodes;
	std::vector<std::pair<int, std::pair<double, double>>> forceDetails;
	for (int i = 0; i < noOfPutForceNodes; i++)
	{
		std::pair<int, std::pair<double, double>> tempForce;
		int forceNode;
		cout << "Enter the specific node you want to put force into" << endl;
		cin >> tempForce.first;
		double forceX;
		double forceY;
		cout << "Enter the force for X:" << endl;
		cin >> tempForce.second.first;
		cout << "Enter the force for Y:" << endl;
		cin >> tempForce.second.second;

		forceDetails.push_back(tempForce);
	}
	int x;
	std::vector<int> Constrained_Vector;
	while (CountCN < CN)
	{
		cout << "\n Enter The Constrained Node:";
		cin >> x;
		Constrained_Vector.push_back(x);
		cout << endl;
		CountCN++;
	}
	double Scalar = E / (1 - pow(v, 2));
	//std::vector<double> Global_Vector;
	std::vector<Face>::iterator itr;
	std::pair<std::pair<int, int>, double> Temp;
	std::vector<std::pair<std::pair<int, int>, double>> Global;
	double D[3][3];
	D[0][0] = Scalar;
	D[0][1] = v * Scalar;
	D[0][2] = 0;
	D[1][0] = v * Scalar;
	D[1][1] = Scalar;
	D[1][2] = 0;
	D[2][0] = 0;
	D[2][1] = 0;
	D[2][2] = Scalar * ((1 - v) / 2);
	int h = 1;
	double* boundaryMatrix = new double[size * size];
	//cout << D[1][2] << endl;
	for (itr = VF.begin(); itr != VF.end(); itr++)
	{
		double B[3][6];
		double BT[6][3];
		double Inverse_Determinant = 2 * Area(*itr);
		//std::pair <std::pair<int, int>, double> BT;
		std::vector<std::pair <std::pair<int, int>, double>> V_BT;
		B[0][0] = (itr->V2.y - itr->V3.y) / Inverse_Determinant;
		B[0][1] = 0 / Inverse_Determinant;
		B[0][2] = (itr->V3.y - itr->V1.y) / Inverse_Determinant;
		B[0][3] = 0 / Inverse_Determinant;
		B[0][4] = (itr->V1.y - itr->V2.y) / Inverse_Determinant;
		B[0][5] = 0 / Inverse_Determinant;
		B[1][0] = 0 / Inverse_Determinant;
		B[1][1] = (itr->V3.x - itr->V2.x) / Inverse_Determinant;
		B[1][2] = 0 / Inverse_Determinant;
		B[1][3] = (itr->V1.x - itr->V3.x) / Inverse_Determinant;
		B[1][4] = 0 / Inverse_Determinant;
		B[1][5] = (itr->V2.x - itr->V1.x) / Inverse_Determinant;
		B[2][0] = (itr->V3.x - itr->V2.x) / Inverse_Determinant;
		B[2][1] = (itr->V2.y - itr->V3.y) / Inverse_Determinant;
		B[2][2] = (itr->V1.x - itr->V3.x) / Inverse_Determinant;
		B[2][3] = (itr->V3.y - itr->V1.y) / Inverse_Determinant;
		B[2][4] = (itr->V2.x - itr->V1.x) / Inverse_Determinant;
		B[2][5] = (itr->V1.y - itr->V2.y) / Inverse_Determinant;



		for (int i = 0; i < 6; ++i) { for (int j = 0; j < 3; ++j) { BT[i][j] = B[j][i]; } }
		double BD[3][6];
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				BD[i][j] = 0;
				for (int k = 0; k < 3; ++k)
				{
					// cout << "D[" << i << ", " << k << "]" << D[i][k] << endl;
					// cout << "B[" << k << ", " << j << "]" << B[k][j] << endl;
					BD[i][j] += D[i][k] * B[k][j];
				}
			}
		}
		/*
		// HOANG
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 6; ++j) {
				cout << BD[i][j] << "  ";
			}
			cout << endl;
		}
		//END
		*/
		double K[6][6];
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				K[i][j] = 0;
				for (int k = 0; k < 3; ++k)
				{
					K[i][j] += BT[i][k] * BD[k][j];
				}
			}
		}
		/*
		// HOANG
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 6; ++j) {
				cout << K[i][j] << "  ";
			}
			cout << endl;
		}
		//END
		*/

		cout << "The Local Stiffness Matrix for Face " << h << " is:" << endl;
		h++;


		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{

				K[i][j] = Area(*itr)*K[i][j] * thickness;
				cout << setw(12) << setprecision(6) << K[i][j] << "  ";
			}
			cout << endl;
			cout << endl;
		}

		cout << endl;
		int count = 0;
		for (int j = 0; j < 6; j++)
		{
			int count1 = 0;
			for (int i = 0; i < 6; i++)
			{
				Temp.second = K[i][j];
				if (count <= 5)
				{
					switch (count)
					{
					case 0:
						Temp.first.first = 2 * itr->V1.order - 1;
						break;
					case 1:
						Temp.first.first = 2 * itr->V1.order;
						break;
					case 2:
						Temp.first.first = 2 * itr->V2.order - 1;
						break;
					case 3:
						Temp.first.first = 2 * itr->V2.order;
						break;
					case 4:
						Temp.first.first = 2 * itr->V3.order - 1;
						break;
					case 5:
						Temp.first.first = 2 * itr->V3.order;
						break;
					}

					switch (count1)
					{
					case 0:
						Temp.first.second = 2 * itr->V1.order - 1;
						break;
					case 1:
						Temp.first.second = 2 * itr->V1.order;
						break;
					case 2:
						Temp.first.second = 2 * itr->V2.order - 1;
						break;
					case 3:
						Temp.first.second = 2 * itr->V2.order;
						break;
					case 4:
						Temp.first.second = 2 * itr->V3.order - 1;
						break;
					case 5:
						Temp.first.second = 2 * itr->V3.order;
						break;
					}
					count1++;
					Global_Assigning(Global, Temp);
				}
				else
				{
					cerr << "error counts" << endl;
				}
			}
			count++;
		}
	}

	cout << "\n\n Global Stiffness Matrix for the Sample is:\a" << endl;



	Global_Reading(Global);

	cout << endl;
	double* properGlobalMatrix = new double[size * size];
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			properGlobalMatrix[i * size + j] = 0;
		}
	}
	std::vector<std::pair<std::pair<int, int>, double>>::iterator itr1;
	for (itr1 = Global.begin(); itr1 != Global.end(); itr1++)
	{
		int i = itr1->first.first - 1;
		int j = itr1->first.second - 1;

		properGlobalMatrix[i * size + j] = itr1->second;
	}

	std::vector<double> keptElements;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			bool isZero = false;
			for (auto k = Constrained_Vector.begin(); k != Constrained_Vector.end(); k++)
			{
				if ((*k * 2 - 1) == (i + 1) || (*k * 2) == (i + 1) || (*k * 2 - 1) == (j + 1) || (*k * 2) == (j + 1))
				{
					isZero = true;
					//break;
				}
			}
			if (isZero)
			{
				boundaryMatrix[i * size + j] = 0;
			}
			else
			{
				boundaryMatrix[i * size + j] = properGlobalMatrix[i * size + j];
				keptElements.push_back(properGlobalMatrix[i * size + j]);
			}
		}
	}

	int sizeOfExtractedMatrix = sqrt(keptElements.size());
	double* extractedMatrix = new double[sizeOfExtractedMatrix * sizeOfExtractedMatrix];
	int indexExtractedMatrix = 0;
	std::vector<double>::iterator extractedMatrixItr;
	for (extractedMatrixItr = keptElements.begin(); extractedMatrixItr != keptElements.end(); extractedMatrixItr++)
	{
		extractedMatrix[int(indexExtractedMatrix / sizeOfExtractedMatrix) * sizeOfExtractedMatrix + indexExtractedMatrix % sizeOfExtractedMatrix] = *extractedMatrixItr;
		indexExtractedMatrix++;
	}
	double* inversedMatrix = inverse(extractedMatrix, sizeOfExtractedMatrix);

	double* forceMatrix = new double[size];
	std::vector<std::pair<int, std::pair<double, double>>>::iterator itrNodeForce;
	for (itrNodeForce = forceDetails.begin(); itrNodeForce != forceDetails.end(); itrNodeForce++)
	{
		forceMatrix[2 * itrNodeForce->first - 2] = itrNodeForce->second.first;
		forceMatrix[2 * itrNodeForce->first - 1] = itrNodeForce->second.second;
	}

	double* extractedForceMatrix = new double[sizeOfExtractedMatrix];
	int extractedForceMatrixIndex = 0;
	std::vector<int> excludedIndices;
	for (int i = 0; i < size; ++i)
	{
		bool isZero = false;
		for (auto k = Constrained_Vector.begin(); k != Constrained_Vector.end(); k++)
		{
			if ((*k * 2 - 1) == (i + 1) || (*k * 2) == (i + 1))
			{
				isZero = true;
			}
		}
		if (!isZero)
		{
			extractedForceMatrix[extractedForceMatrixIndex] = forceMatrix[i];
			excludedIndices.push_back(i);
			extractedForceMatrixIndex++;
		}
	}

	double* resultMatrix = new double[sizeOfExtractedMatrix];
	for (int i = 0; i < sizeOfExtractedMatrix; ++i)
	{
		resultMatrix[i] = 0;
		for (int k = 0; k < sizeOfExtractedMatrix; ++k)
		{
			resultMatrix[i] += inversedMatrix[i * sizeOfExtractedMatrix + k] * extractedForceMatrix[k];
		}
	}

	cout << "Global matrix with applied Boundary Conditions:" << endl;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << "(" << i + 1 << ", " << j + 1 << ") = " << boundaryMatrix[i * size + j] << endl;
		}
		cout << endl;
	}
	std::vector<std::pair<std::pair<int, int>, double>>::iterator itrf;
	std::vector<std::pair<std::pair<int, int>, double>> newvector;
	std::vector<int>::iterator itrg;

	int resultMatrixIndex = 0;
	for (auto k = excludedIndices.begin(); k != excludedIndices.end(); k++)
	{
		cout << "ID " << *k + 1 << ": " << resultMatrix[resultMatrixIndex] << endl;
		resultMatrixIndex++;
	}
	cout << "\n" << endl;
}

#endif /* Matrix_h */