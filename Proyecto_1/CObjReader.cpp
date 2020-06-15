#include "CObjReader.h"

//Insertar el string con la extencion .obj
CObjReader::CObjReader(const string& FileName) :
	m_pVertices(nullptr),
	m_pNormales(nullptr),
	m_pUVCoords(nullptr),
	m_pIndVertices(nullptr),
	m_pIndNormales(nullptr),
	m_pIndUVCoords(nullptr),
	m_iNumVertices(0),
	m_iNumNormales(0),
	m_iNumUVCoords(0),
	m_iNumQuads(0),
	m_iVerticeVectorType(0),
	m_iNormalesVectorType(0),
	m_iUVCoordVectorType(0),
	m_iFacesVectorType(0),
	m_sTextureArch(""),
	File(FileName),
	m_FacesSubIndices(0)
{

	fstream m_object(FileName);
	if (!m_object)
	{
		cout << "Error al abrir" << FileName << endl;
	}
}

//Dtor
CObjReader::~CObjReader()
{
	if (m_pVertices != nullptr)
	{
		delete[] m_pVertices;
	}
	if (m_pNormales != nullptr)
	{
		delete[] m_pNormales;
	}
	if (m_pUVCoords != nullptr)
	{
		delete[] m_pUVCoords;
	}
	if (m_pIndVertices != nullptr)
	{
		delete[] m_pIndVertices;
	}
	if (m_pIndNormales != nullptr)
	{
		delete[] m_pIndNormales;
	}
	if (m_pIndNormales != nullptr)
	{
		delete[] m_pIndUVCoords;
	}
}

bool CObjReader::readObjFile(string pfilename)
{
	fstream m_object(File);
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
}

void CObjReader::Tokinize()
{
	fstream m_object(File);
	while (!m_object.eof())
	{
		// v, vt, vn, f
		stringstream Line_Text;
		string text;

		getline(m_object, text);
		Line_Text << text;
		text = "";
		Line_Text >> text;

		//vertices
		if (text == "v")
		{
			//para ver cuantas cordenadas usa el obj
			if (m_iVerticeVectorType == 0)
			{
				while (!Line_Text.eof())
				{
					float x;
					Line_Text >> x;

					m_iVerticeVectorType++;
				}
			}
			m_iNumVertices++;
		}

		//vertices de textura
		else if (text == "vt")
		{
			if (m_iUVCoordVectorType == 0)
			{
				while (!Line_Text.eof())
				{
					float x;
					Line_Text >> x;

					m_iUVCoordVectorType++;
				}
			}
			m_iNumUVCoords++;

		}

		//vertices de normales
		else if (text == "vn")
		{
			if (m_iNormalesVectorType == 0)
			{
				while (!Line_Text.eof())
				{
					float x;
					Line_Text >> x;

					m_iNormalesVectorType++;
				}
			}
			m_iNumNormales++;
		}

		//faces
		else if (text == "f")
		{
			if (m_iFacesVectorType == 0)
			{
				while (!Line_Text.eof())
				{
					string x;
					stringstream texto_2;
					Line_Text >> x;
					texto_2 << x;

					m_iFacesVectorType++;
					if (m_FacesSubIndices == 0)
					{
						while (!texto_2.eof())
						{
							int num;
							char diagonal;
							if (texto_2 >> num)
							{
								m_FacesSubIndices++;
							}
							else
							{
								texto_2.clear();
							}
							texto_2 >> diagonal;
						}
					}
				}
			}
			m_iNumQuads++;
		}
	}

	m_object.close();

	///////////////////////////////////////////////////////////////////////////////////////
	cout << "Vertices = " << m_iNumVertices * m_iVerticeVectorType << endl;
	cout << "Texture = " << m_iNumUVCoords * m_iUVCoordVectorType << endl;
	cout << "Normales = " << m_iNumNormales * m_iNormalesVectorType << endl;
	cout << "Faces = " << m_iNumQuads * m_iFacesVectorType * m_FacesSubIndices << endl;
	///////////////////////////////////////////////////////////////////////////////////////

	ReserveMemory();

	m_object.open(File);
	while (!m_object.eof())
	{
		// v, vt, vn, f
		unsigned int v = 0, vt = 0, vn = 0, f = 0;
		stringstream Line_Text;
		string text;

		getline(m_object, text);
		Line_Text << text;
		text = "";
		Line_Text >> text;

		//vertices
		if (text == "v")
		{
			for (int i = 0; i < m_iVerticeVectorType; i++)
			{
				Line_Text >> m_pVertices[v];
				v++;
			}
		}

		//vertices de textura
		else if (text == "vt")
		{
			for (int i = 0; i < m_iUVCoordVectorType; i++)
			{
				Line_Text >> m_pUVCoords[vt];
				vt++;
			}
		}

		//vertices de normales
		else if (text == "vn")
		{
			for (int i = 0; i < m_iNormalesVectorType; i++)
			{
				Line_Text >> m_pNormales[vn];
				vn++;
			}
		}

		//faces
		else if (text == "f")
		{
			char c;
			for (int i = 0; i < m_iFacesVectorType; i++)
			{

				Line_Text >> m_pIndVertices[f] >> c;

				if (!(Line_Text >> m_pIndUVCoords[f]))
				{
					Line_Text.clear();
				}
				Line_Text >> c;

				if (!(Line_Text >> m_pIndNormales[f]))
				{
					Line_Text.clear();
				}
				f++;
			}
		}
	}
}

void CObjReader::ReserveMemory()
{
	m_pVertices = new float[m_iNumVertices * m_iVerticeVectorType];
	memset(m_pVertices, 00000000, m_iNumVertices * m_iVerticeVectorType * sizeof(float));

	m_pUVCoords = new float[m_iNumUVCoords * m_iUVCoordVectorType];
	memset(m_pUVCoords, 00000000, m_iNumUVCoords * m_iUVCoordVectorType * sizeof(float));

	m_pNormales = new float[m_iNumNormales * m_iNormalesVectorType];
	memset(m_pNormales, 00000000, m_iNumNormales * m_iNormalesVectorType * sizeof(float));

	m_pIndVertices = new unsigned short[m_iNumQuads * m_iFacesVectorType];// numero de figura por la catidad de vertices de cada figura
	memset(m_pIndVertices, 00, m_iNumQuads * m_iFacesVectorType * sizeof(unsigned short));

	if (m_FacesSubIndices > 1)
	{
		m_pIndNormales = new unsigned short[m_iNumQuads * m_iFacesVectorType];
		memset(m_pIndVertices, 00, m_iNumQuads * m_iFacesVectorType * sizeof(unsigned short));

	}

	if (m_FacesSubIndices == 3) // para ver si tiene textura
	{
		m_pIndUVCoords = new unsigned short[m_iNumQuads * m_iFacesVectorType];
		memset(m_pIndVertices, 00, m_iNumQuads * m_iFacesVectorType * sizeof(unsigned short));
	}

	cout << "Meomory reserved" << endl;
}

void CObjReader::printObj()
{

}