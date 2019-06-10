// DataProgram.cpp : This file contains functions which 
// extracts the vertices from the obj file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

unsigned long getFileLength(std::ifstream& file)
{
	if (!file.good()) return 0;

	unsigned long pos = file.tellg();
	file.seekg(0, std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);

	return len;
}

void Extract_3DModel_to_C_header(const char* filename)
{
	// Open the input file 
	std::ifstream infile;
	infile.open(filename, std::ios::in);
	if (!infile) return;

	// Make the output file name
	std::stringstream sfile(filename);
	std::string outFileName;
	std::getline(sfile, outFileName, '.');
	std::string ext("Data.h");
	outFileName += ext;
	std::cout << "file name: " << outFileName << std::endl;
	
	// Open the output file
	std::ofstream outfile;
	outfile.open(outFileName, std::ios::out);
	if (!outfile) return;

	// Check the data in the input file
	unsigned long len = getFileLength(infile);
	if (len == 0) return;   // "Empty File" 
	std::cout << "file length: " << len<< std::endl;

	outfile << "float vertices[]={" << std::endl;

	std::string lineData;
	while (infile.good())
	{
		std::getline(infile, lineData);
		std::stringstream ss(lineData);
		std::string vertex ;
		float vX=0, vY=0, vZ=0;
		ss >> vertex;
		//std::cout << vertex << "    ";
		if (vertex.compare("v") == 0)
		{
			ss >> vX >> vY >> vZ;
			outfile << vX << "," << vY << "," << vZ << "," << std::endl;
		}
		//std::cout << vX <<"," << vY << "," <<vZ << "," << std::endl;
	}
	long pos = outfile.tellp();
	outfile.seekp(pos - 3);
	outfile.write("\n", 1);
	outfile << "}" << std::endl;

	infile.close();
	outfile.close();
	return;   // can't reserve memory
}

int main()
{
	Extract_3DModel_to_C_header("Bowl.obj");
	Extract_3DModel_to_C_header("10106_Computer Mouse_v1_L3.obj");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
