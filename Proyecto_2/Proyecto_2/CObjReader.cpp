#include "CObjReader.h"
#include <cstdlib>
#include <time.h>

//Insertar el string con la extencion .obj
CObjReader::CObjReader(const string& FileName) :
	m_pVertices(nullptr),
	m_pNormales(nullptr),
	m_pUVCoords(nullptr),
	m_pIndVertices(nullptr),
	m_pIndNormales(nullptr),
	m_pIndUVCoords(nullptr),
	m_iCountVertices(0),
	m_iCountNormales(0),
	m_iCountUVCoords(0),
	m_iCountFaces(0),
	m_iVectorVertices(0),
	m_iVectorNormales(0),
	m_iVectorUVCoords(0),
	m_iVectorFaces(0),
	m_sTextureArch(""),
	File_Name(FileName),
	m_FacesSubIndices(0),
	m_sTexture(""),
	m_uObjID(0),
	m_ShaderID(0),
	m_TextureID(0)

{
	float pos_x = 3 - rand() % (3 + 3);
	float pos_y = 2 - rand() % (2 + 2);

	m_objectRotation = new CVector3(0,0,0);
	m_objectPosition = new CVector3(pos_x, pos_y,0);
	m_objectScale = new CVector3(1,1,1);

	fstream m_object(FileName);
	if (!m_object)
	{
		cout << "Error al abrir" << FileName << endl;
	}
}

CObjReader::CObjReader():
	m_pVertices(nullptr),
	m_pNormales(nullptr),
	m_pUVCoords(nullptr),
	m_pIndVertices(nullptr),
	m_pIndNormales(nullptr),
	m_pIndUVCoords(nullptr),
	m_iCountVertices(0),
	m_iCountNormales(0),
	m_iCountUVCoords(0),
	m_iCountFaces(0),
	m_iVectorVertices(0),
	m_iVectorNormales(0),
	m_iVectorUVCoords(0),
	m_iVectorFaces(0),
	m_sTextureArch(""),
	m_FacesSubIndices(0),
	m_sTexture(""),
	m_uObjID(0),
	m_ShaderID(0),
	m_TextureID(0)
{
	float pos_x = 3 - rand() % (3 + 3);
	float pos_y = 2 - rand() % (2 + 2);

	m_objectRotation = new CVector3(0, 0, 0);
	m_objectPosition = new CVector3(pos_x, pos_y, 0);
	m_objectScale = new CVector3(1, 1, 1);
}

CObjReader::CObjReader(const CObjReader& cpy)
{

	m_objectRotation = new CVector3(0, 0, 0);
	m_objectPosition = new CVector3(cpy.Get_m_objectPosition()->X, cpy.Get_m_objectPosition()->Y, 0);
	m_objectScale = new CVector3(1, 1, 1);

	m_iCountVertices = cpy.m_iCountVertices;
	m_iCountNormales = cpy.m_iCountNormales;
	m_iCountUVCoords = cpy.m_iCountUVCoords;
	m_iCountFaces = cpy.m_iCountFaces;
	m_iVectorVertices = cpy.m_iVectorVertices;
	m_iVectorNormales = cpy.m_iVectorNormales;
	m_iVectorUVCoords = cpy.m_iVectorUVCoords;
	m_iVectorFaces = cpy.m_iVectorFaces;
	m_sTextureArch = cpy.m_sTextureArch;
	m_FacesSubIndices = cpy.m_FacesSubIndices;
	m_sTexture = cpy.m_sTexture;
	m_uObjID = cpy.m_uObjID;
	m_ShaderID = cpy.m_ShaderID;
	m_TextureID = cpy.m_TextureID;
	File_Name = cpy.File_Name;

	m_pVertices = new float[cpy.m_iCountVertices * cpy.m_iVectorVertices];
	memset(m_pVertices, 0, (cpy.m_iCountVertices * cpy.m_iVectorVertices) * sizeof(float));
	memcpy(m_pVertices, cpy.m_pVertices, (cpy.m_iCountVertices * cpy.m_iVectorVertices) * sizeof(float));

	m_pNormales = new float[cpy.m_iCountNormales * cpy.m_iVectorNormales];
	memset(m_pNormales, 0, (cpy.m_iCountNormales * cpy.m_iVectorNormales) * sizeof(float));
	memcpy(m_pNormales, cpy.m_pNormales, (cpy.m_iCountNormales * cpy.m_iVectorNormales) * sizeof(float));

	m_pUVCoords = new float[cpy.m_iCountUVCoords * cpy.m_iVectorUVCoords];
	memset(m_pUVCoords, 0, (cpy.m_iCountUVCoords * cpy.m_iVectorUVCoords) * sizeof(float));
	memcpy(m_pUVCoords, cpy.m_pUVCoords, (cpy.m_iCountUVCoords * cpy.m_iVectorUVCoords) * sizeof(float));

	m_pIndVertices = new unsigned short[cpy.m_iCountFaces * cpy.m_iVectorFaces];// numero de figura por la catidad de vertices de cada figura
	memset(m_pIndVertices, 0, (cpy.m_iCountFaces * cpy.m_iVectorFaces) * sizeof(unsigned short));
	memcpy(m_pIndVertices, cpy.m_pIndVertices, (cpy.m_iCountFaces * cpy.m_iVectorFaces) * sizeof(unsigned short));


	if (cpy.m_FacesSubIndices != 1)
	{
		m_pIndNormales = new unsigned short[cpy.m_iCountFaces * cpy.m_iVectorFaces];
		memset(m_pIndNormales, 0, (cpy.m_iCountFaces * cpy.m_iVectorFaces) * sizeof(unsigned short));
		memcpy(m_pIndNormales, cpy.m_pIndNormales, (cpy.m_iCountFaces * cpy.m_iVectorFaces) * sizeof(unsigned short));
	}

	if (cpy.m_FacesSubIndices == 3) // para ver si tiene textura
	{
		m_pIndUVCoords = new unsigned short[cpy.m_iCountFaces * cpy.m_iVectorFaces];
		memset(m_pIndUVCoords, 0, (cpy.m_iCountFaces * cpy.m_iVectorFaces) * sizeof(unsigned short));
		memcpy(m_pIndUVCoords, cpy.m_pIndUVCoords, (cpy.m_iCountFaces * cpy.m_iVectorFaces) * sizeof(unsigned short));
	}


	std::cout << "m_pVertices = " << m_pVertices << std::endl;
	std::cout << "Copy m_pVertices = " << cpy.m_pVertices << std::endl;
}

//Dtor
CObjReader::~CObjReader()
{
	if (m_pVertices != nullptr)
	{
		delete[] m_pVertices;
		m_pVertices = nullptr;
	}
	if (m_pNormales != nullptr)
	{
		delete[] m_pNormales;
		m_pNormales = nullptr;
	}
	if (m_pUVCoords != nullptr)
	{
		delete[] m_pUVCoords;
		m_pUVCoords = nullptr;
	}
	if (m_pIndVertices != nullptr)
	{
		delete[] m_pIndVertices;
		m_pIndVertices = nullptr;
	}
	if (m_pIndNormales != nullptr)
	{
		delete[] m_pIndNormales;
		m_pIndNormales = nullptr;
	}
	if (m_pIndUVCoords != nullptr)
	{
		delete[] m_pIndUVCoords;
		m_pIndUVCoords = nullptr;
	}

}

bool CObjReader::OpenObjFile(string pfilename)
{
	std::cout << "Memm set File name = " << File_Name << std::endl;

	fstream m_object(pfilename);
	if (!m_object)
	{
		cout << "No se pudo cargar el archivo" << endl;
		return false;

	}
	else
	{
		while (!m_object.eof())
		{
			string line;
			getline(m_object, line);
			cout << line << endl;

		}
		return true;
	}
	ObjSetMemAndVar(pfilename);
}




void CObjReader::ObjSetMemAndVar(string StringObj)
{
	File_Name = StringObj;
	string string_ReadObjFile;
	fstream ObjFile(StringObj);

	while (!ObjFile.eof())
	{
		// v, vt, vn, f
		getline(ObjFile, string_ReadObjFile);
		stringstream Token_ObjFile;
		Token_ObjFile << string_ReadObjFile;
		Token_ObjFile >> string_ReadObjFile;

		//vertices
		if (string_ReadObjFile == "v")
		{
			//para ver cuantas cordenadas usa el obj

			if (m_iCountVertices == 0)
			{
				while (!Token_ObjFile.eof())
				{
					float ReadFloat;
					Token_ObjFile >> ReadFloat;
					m_iVectorVertices++;
				}
			}
			m_iCountVertices++;
		}

		//vertices de normales
		else if (string_ReadObjFile == "vn")
		{
			if (m_iCountNormales == 0)
			{
				while (!Token_ObjFile.eof())
				{
					float ReadFloat;
					m_iVectorNormales++;
					Token_ObjFile >> ReadFloat;
				}
			}
			m_iCountNormales++;
		}

		//vertices de textura
		else if (string_ReadObjFile == "vt")
		{
			if (m_iCountUVCoords == 0)
			{
				while (!Token_ObjFile.eof())
				{
					float ReadFloat;
					m_iVectorUVCoords++;
					Token_ObjFile >> ReadFloat;
				}
			}
			m_iCountUVCoords++;
		}

		//faces
		else if (string_ReadObjFile == "f")
		{
			m_iCountFaces++;
			int iVecFaces = 0;
			if (iVecFaces == 0)
			{
				while (!Token_ObjFile.eof())
				{
					stringstream TT_ReadString;
					string ReadString;
					m_iVectorFaces = 3;
					iVecFaces++;
					Token_ObjFile >> ReadString;
					TT_ReadString << ReadString;

					if (m_FacesSubIndices == 0)
					{
						while (!TT_ReadString.eof())
						{
							int ReadInt = 0;
							char ReadChar = '\0';

							if (TT_ReadString >> ReadInt)
							{
								m_FacesSubIndices++;
							}
							else
							{
								TT_ReadString.clear();
							}
							TT_ReadString >> ReadChar;
						}
					}
				}

				if (iVecFaces == 4)
				{
					m_iCountFaces++;
				}
				else if (iVecFaces > 4)
				{
					cout << "**Tiene más de 4 caras**" << endl;
				}
			}
		}
	}

	ObjFile.close();

	ReserveMemory();

	ObjFile.open(StringObj);
	int v = 0, vt = 0, vn = 0, f = 0;
	int F = 0;

	while (!ObjFile.eof())
	{
		// v, vt, vn, f
		getline(ObjFile, string_ReadObjFile);
		stringstream Token_Obj;
		Token_Obj << string_ReadObjFile;
		Token_Obj >> string_ReadObjFile;

		//vertices
		if (string_ReadObjFile == "v")
		{
			for (int i = 0; i < m_iVectorVertices; i++)
			{
				Token_Obj >> m_pVertices[v++];
			}
		}

		//vertices de normales
		else if (string_ReadObjFile == "vn")
		{
			for (int i = 0; i < m_iVectorNormales; i++)
			{
				Token_Obj >> m_pNormales[vt++];
			}
		}

		//vertices de textura
		else if (string_ReadObjFile == "vt")
		{
			for (int i = 0; i < m_iVectorUVCoords; i++)
			{
				Token_Obj >> m_pUVCoords[vn++];
			}
		}

		//faces
		else if (string_ReadObjFile == "f")
		{
			vector<string> VectorStrings;
			while (!Token_Obj.eof())
			{
				string Temporal;
				Token_Obj >> Temporal;
				if (Temporal != "")
				{
					VectorStrings.push_back(Temporal);
				}
			}
			for (int i = 3; i <= VectorStrings.size(); i++)
			{
				ReadFigures(VectorStrings[0], F++);
				ReadFigures(VectorStrings[i - 2], F++);
				ReadFigures(VectorStrings[i - 1], F++);
			}
		}
	}
	ObjFile.close();
	///////////////////////////////////////////////////////////////////////////////////////
	/*cout << "Vertices = " << m_iCountVertices * m_iVectorVertices << endl;
	cout << "Texture = " << m_iCountUVCoords * m_iVectorUVCoords << endl;
	cout << "Normales = " << m_iCountNormales * m_iVectorNormales << endl;
	cout << "Faces = " << m_iCountFaces * m_iVectorFaces * m_FacesSubIndices << endl;*/
	///////////////////////////////////////////////////////////////////////////////////////
}


void CObjReader::ReadFigures(string Vertices, int Indice)
{
	char ReadDiagonal = '\0';
	stringstream Token_Obj;
	Token_Obj << Vertices;

	Token_Obj >> m_pIndVertices[Indice] >> ReadDiagonal;
	m_pIndVertices[Indice]--;

	if (m_FacesSubIndices == 3)
	{
		if (!(Token_Obj >> m_pIndUVCoords[Indice]))
		{
			Token_Obj.clear();
		}
		m_pIndUVCoords[Indice]--;
	}
	Token_Obj >> ReadDiagonal;

	if (m_FacesSubIndices != 1)
	{
		if (!(Token_Obj >> m_pIndNormales[Indice]))
		{
			Token_Obj.clear();
		}
		m_pIndNormales[Indice]--;
	}
}

void CObjReader::ReserveMemory()
{

	m_pVertices = new float[m_iCountVertices * m_iVectorVertices];
	memset(m_pVertices, 0, (m_iCountVertices * m_iVectorVertices) * sizeof(float));

	m_pNormales = new float[m_iCountNormales * m_iVectorNormales];
	memset(m_pNormales, 0, (m_iCountNormales * m_iVectorNormales) * sizeof(float));

	m_pUVCoords = new float[m_iCountUVCoords * m_iVectorUVCoords];
	memset(m_pUVCoords, 0, (m_iCountUVCoords * m_iVectorUVCoords) * sizeof(float));

	m_pIndVertices = new unsigned short[m_iCountFaces * m_iVectorFaces];// numero de figura por la catidad de vertices de cada figura
	memset(m_pIndVertices, 0, (m_iCountFaces * m_iVectorFaces) * sizeof(unsigned short));

	if (m_FacesSubIndices != 1)
	{
		m_pIndNormales = new unsigned short[m_iCountFaces * m_iVectorFaces];
		memset(m_pIndNormales, 0, (m_iCountFaces * m_iVectorFaces) * sizeof(unsigned short));

	}

	if (m_FacesSubIndices == 3) // para ver si tiene textura
	{
		m_pIndUVCoords = new unsigned short[m_iCountFaces * m_iVectorFaces];
		memset(m_pIndUVCoords, 0, (m_iCountFaces * m_iVectorFaces) * sizeof(unsigned short));
	}
	//cout << "Meomory reserved" << endl;
}

void CObjReader::printObj()
{

}