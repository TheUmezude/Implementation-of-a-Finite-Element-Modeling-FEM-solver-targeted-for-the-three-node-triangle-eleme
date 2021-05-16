/*
This Program was Developed by Nkemdilim Okechukwu Umezude, with assistance from Hoang Phan and Taoufik Touti.
The entirety of the project process and technique was conceived by Nkemdilim Okechukwu Umezude
*/

#include "Matrix.h"
#include "Voids.h"
#include <string>
using namespace std;
int main(int argc, char* argv[])
{
	string filename;
	cout << "This program performs numerical FEA analysis for any sample meshed with triangular elements" << endl;
	cout << "When prompted for File path, enter it as in this example 'C://Users//Ukem//Desktop//Example1.txt'\n" << endl;

	cout << "Input filename (Absolute Path to the file):" << endl;     // Absolute path example: "C://Users//Ukem//Desktop//Example1.txt"
	cin >> filename;
	ifstream triangleobj;
	triangleobj.open(filename);

	cout << "\n";
	// triangleobj.open("C://Users//Ukem//Desktop//Example1.txt");
	string input_char;
	vector<Vertex>::iterator itr;
	vector<Face>::iterator itrf;

	Vertex VX;
	Face F;
	vector<Vertex> VVX;
	vector<Face> VF;
	VX.order = 0;
	F.index = 0;

	VVX.size();

	double a, b, c;
	if (triangleobj.is_open())
	{
		string streamer1;
		while (getline(triangleobj, streamer1))
		{
			stringstream r(streamer1);
			r >> input_char >> a >> b >> c;
			if (input_char == "v")
			{
				VX.order++;
				VX.x = a;
				VX.y = b;
				VX.z = c;
				VVX.push_back(VX);
				//cout << VX.order << "    " << VX.x << "    " << VX.y << "    " << VX.z << endl;

			}
			else
			{
				F.index++;
				F.V1.order = a;
				F.V2.order = b;
				F.V3.order = c;
				for (itr = VVX.begin(); itr != VVX.end(); ++itr)
				{
					if (itr->order == F.V1.order)
					{
						F.V1 = *itr;
						//cout << itr->order << endl;
					}
					else if (itr->order == F.V2.order)
					{
						F.V2 = *itr;
						//cout << itr->order << endl;
					}
					else if (itr->order == F.V3.order)
					{
						F.V3 = *itr;
						//cout << itr->order << endl;
					}
					else {
						continue;
					}
				}
				VF.push_back(F);
				//cout << "pushed" << endl;

			}
		}
	}
	else
	{
		cerr << "error input" << endl;
	}

	void ReadVVX(Vertex& V);
	void ReadFace(Face& F);
	double T, P, E;
	cout << "Input the thickness of the sample:" << endl;
	cin >> T;
	cout << endl;

	cout << "Input the Poisson's Ratio of the material:" << endl;
	cin >> P;
	cout << endl;

	cout << "Input the Young's Modulus of the material:" << endl;
	cin >> E;
	cout << endl;

	Global_Stiffness_Matrix(2 * VVX.size(), T, P, E, VF);
	for (itrf = VF.begin(); itrf != VF.end(); itrf++)
	{
		ReadFace(*itrf);
	}

	system("pause");
	EXIT_SUCCESS;

}

