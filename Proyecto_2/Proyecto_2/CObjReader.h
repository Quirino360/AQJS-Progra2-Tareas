#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "CVector3.h"

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

	///////////////////////////////////

	std::string m_sTexture;

	CVector3* m_objectRotation;
	CVector3* m_objectPosition;
	CVector3* m_objectScale;

	unsigned int m_uObjID;
	unsigned int m_ShaderID;
	unsigned int m_TextureID;

public:
	//Constructor (Ctor)
	CObjReader(const string& FileName);
	CObjReader(const CObjReader& cpy);
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

	bool IsEmpty() { if (m_pVertices == nullptr) { return false; } return true; }

public:
	float* Get_m_pVertices() const { return m_pVertices; }
	float* Get_m_pNormales() const { return m_pNormales; }
	float* Get_m_pUVCoords() const { return m_pUVCoords; }

	unsigned  short* Get_m_pIndVertices() const { return m_pIndVertices; }
	unsigned short* Get_m_pIndNormales() const { return m_pIndNormales; }
	unsigned short* Get_m_pIndUVCoords() const { return m_pIndUVCoords; }

	unsigned int Get_m_iCountVertices() const { return m_iCountVertices; };
	unsigned int Get_m_iCountNormales() const { return m_iCountNormales; };
	unsigned int Get_m_iCountUVCoords() const { return m_iCountUVCoords; };
	unsigned int Get_m_iCountFaces() const { return m_iCountFaces; };

	unsigned int Get_m_iVerticeVectorType() const { return m_iVectorVertices; }
	unsigned int Get_m_iNormalesVectorType() const { return m_iVectorNormales; }
	unsigned int Get_m_iUVCoordVectorType() const { return m_iVectorUVCoords; }
	unsigned int Get_m_iFacesVectorType() const { return m_iVectorFaces; }

	unsigned int Get_m_FacesSubIndices() const { return m_FacesSubIndices; }

	string Get_m_sFileName() const { return File_Name; };

	std::string get_m_sTexture() const { return m_sTexture; };
	std::string set_m_sTexture(std::string _m_sTexture) { return m_sTexture = _m_sTexture; };


	CVector3* Get_m_objectRotation() const { return m_objectRotation; };
	CVector3* Get_m_objectPosition() const { return m_objectPosition; };
	CVector3* Get_m_objectScale() const { return m_objectScale; };

	void Set_m_objectRotation(float _x, float _y, float _z) {  m_objectRotation = new CVector3(_x, _y, _z); };
	void Set_m_objectPosition(float _x, float _y, float _z) {  m_objectPosition = new CVector3(_x, _y, _z); };
	void Set_m_objectScale(float _x, float _y, float _z) {  m_objectScale = new CVector3(_x, _y, _z); };

	 unsigned int& get_m_uObjID()   { return m_uObjID; };
	 unsigned int& get_m_ShaderID()   { return m_ShaderID; };
	 unsigned int& get_m_TextureID()  { return m_TextureID; };

	void set_m_uObjID(unsigned int _muObjID) {  m_uObjID = _muObjID; };
	void set_m_ShaderID(unsigned int _m_ShaderID) {  m_ShaderID = _m_ShaderID; };
	void set_m_TextureID(unsigned int _m_TextureID) {  m_TextureID = _m_TextureID; };
};