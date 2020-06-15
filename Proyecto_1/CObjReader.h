#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

	unsigned int m_iNumVertices;
	unsigned int m_iNumNormales;
	unsigned int m_iNumUVCoords;
	unsigned int m_iNumQuads;

	unsigned int m_iVerticeVectorType;
	unsigned int m_iNormalesVectorType;
	unsigned int m_iUVCoordVectorType;
	unsigned int m_iFacesVectorType;

	unsigned int m_FacesSubIndices;

	std::string File;
	std::string m_sTextureArch;

public:
	//Constructor (Ctor)
	CObjReader(const string& FileName);

	//Destructor (Dtor)
	~CObjReader();

	// Reads an obj file
	bool readObjFile(string pfilename);

	//Tokinize
	void Tokinize();

	//reserve memory
	void ReserveMemory();

	//Print to console
	void printObj();



public:
	inline float* Get_m_pVertices() { return m_pVertices; }
	inline float* Get_m_pNormales() { return m_pNormales; }
	inline float* Get_m_pUVCoords() { return m_pUVCoords; }

	inline unsigned  short* Get_m_pIndVertices() { return m_pIndVertices; }
	inline unsigned short* Get_m_pIndNormales() { return m_pIndNormales; }
	inline unsigned short* Get_m_pIndUVCoords() { return m_pIndUVCoords; }

	inline unsigned int Get_m_iNumVertices() { return m_iNumVertices; };
	inline unsigned int Get_m_iNumNormales() { return m_iNumNormales; };
	inline unsigned int Get_m_iNumUVCoords() { return m_iNumUVCoords; };
	inline unsigned int Get_m_iNumQuads() { return m_iNumQuads; };

	inline unsigned int Get_m_iVerticeVectorType() { return m_iVerticeVectorType; }
	inline unsigned int Get_m_iNormalesVectorType() { return m_iNormalesVectorType; }
	inline unsigned int Get_m_iUVCoordVectorType() { return m_iUVCoordVectorType; }
	inline unsigned int Get_m_iFacesVectorType() { return m_iFacesVectorType; }

	inline unsigned int Get_m_FacesSubIndices() { return m_FacesSubIndices; }

	inline string Get_m_sFileName() { return File; };
};

