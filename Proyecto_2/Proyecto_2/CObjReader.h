#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class CObjReader
{
private:

	float* m_pVertices;
	float* m_pUVCoords;
	float* m_pNormales;

	unsigned short* m_pIndVertices;
	unsigned short* m_pIndUVCoords;
	unsigned short* m_pIndNormales;

	unsigned int m_iCountVertices;
	unsigned int m_iCountNormales;
	unsigned int m_iCountUVCoords;
	unsigned int m_iCountFaces;

	unsigned int m_iVectorVertices;
	unsigned int m_iVectorNormales;
	unsigned int m_iVectorUVCoords;
	unsigned int m_iVectorFaces;

	unsigned int m_FacesSubIndices;

	std::string File_Name;
	std::string m_sTextureArch;

public:
	//Constructor (Ctor)
	CObjReader(const string& FileName);
	CObjReader();

	//Destructor (Dtor)
	~CObjReader();

	// Reads an obj file
	bool OpenObjFile(string pfilename);

	//Tokinize
	void ObjSetMemAndVar(string pfilename);

	void ReadFigures(string Vertices, int Indice);
	//reserve memory
	void ReserveMemory();

	//Print to console
	void printObj();



public:
	float* Get_m_pVertices() { return m_pVertices; }
	float* Get_m_pNormales() { return m_pNormales; }
	float* Get_m_pUVCoords() { return m_pUVCoords; }

	unsigned  short* Get_m_pIndVertices() { return m_pIndVertices; }
	unsigned short* Get_m_pIndNormales() { return m_pIndNormales; }
	unsigned short* Get_m_pIndUVCoords() { return m_pIndUVCoords; }

	unsigned int Get_m_iCountVertices() { return m_iCountVertices; };
	unsigned int Get_m_iCountNormales() { return m_iCountNormales; };
	unsigned int Get_m_iCountUVCoords() { return m_iCountUVCoords; };
	unsigned int Get_m_iCountFaces() { return m_iCountFaces; };

	unsigned int Get_m_iVerticeVectorType() { return m_iVectorVertices; }
	unsigned int Get_m_iNormalesVectorType() { return m_iVectorNormales; }
	unsigned int Get_m_iUVCoordVectorType() { return m_iVectorUVCoords; }
	unsigned int Get_m_iFacesVectorType() { return m_iVectorFaces; }

	unsigned int Get_m_FacesSubIndices() { return m_FacesSubIndices; }

	string Get_m_sFileName() { return File_Name; };
};
