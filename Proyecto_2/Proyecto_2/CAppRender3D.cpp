#include "CAppRender3D.h"
#include "CTextureLoader.h"



CAppRender3D::CAppRender3D() :
	m_uObjIND{ 0 }, 
	m_uShasderID{ 0 },
	m_pObjR {nullptr},
	m_currentDeltaTime {0.0},
	m_objectRotation {0.0},
	m_objectPosition {0.0f, 0.0f, 0.0f},
	m_rotationSpeed {DEFAULT_ROTATION_SPEED}
{
}

CAppRender3D::~CAppRender3D()
{
	if (m_pObjR != nullptr)
	{
		delete m_pObjR;
		m_pObjR = nullptr;
	}
	if (m_uObjIND > 0)
	{
		m_ptrRenderer->freeGraphicsMemoryForObject(&m_uObjIND);
	}
}

void CAppRender3D::Run()
{
	if (canRun())
	{
		if (m_ptrWindow->create("Ventana"))
		{
			// Create the window
			// Note : The following create() method creates the window itself. Do not make any OpenGL calls before this line, your app...
			//initialize();

			//set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.25f, 0.0f, 0.75f);

			//Enter main Loop
			cout << "Enter Main loop" << endl;
			m_ptrWindow->mainLoop(this);

		}

	}
}

bool CAppRender3D::initialize()
{
	m_TextureID = 0;
	//Resources/MEDIA/TEXTURES/mc_dirt_cube_512x384.tga
	/*      ../ sirve para buscar carpetas atraz        */
	if (!CTextureLoader::loadTexture("../Resources/MEDIA/TEXTURES/mc_dirt_cube_512x384.tga", &m_TextureID, m_ptrRenderer))
	{
		cout << "///////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << "Textura no encontarada" << endl;
		cout << "///////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	}
	//m_pObjR = new CObjReader();
	//m_pObjR->readObjFile("Cubo.obj");

	//m_uShasderID = m_ptrRenderer->getShaderProgramID(SHADER_PROGRAM_COLOR_OBJECT);
	m_uShasderID = m_ptrRenderer->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);

	bool savedInGraphicMemory = m_ptrRenderer->allocateGraphicsMemoryForObject(&m_uShasderID, &m_uObjIND, m_lista.First->getData()->Get_m_pVertices(),
		m_lista.First->getData()->Get_m_iCountVertices(), m_lista.First->getData()->Get_m_pNormales(), m_lista.First->getData()->Get_m_iCountNormales(),
		m_lista.First->getData()->Get_m_pUVCoords(), m_lista.First->getData()->Get_m_iCountUVCoords(), m_lista.First->getData()->Get_m_pIndVertices(),
		m_lista.First->getData()->Get_m_iCountFaces(), m_lista.First->getData()->Get_m_pIndNormales(), m_lista.First->getData()->Get_m_iCountFaces(),
		m_lista.First->getData()->Get_m_pIndUVCoords(), m_lista.First->getData()->Get_m_iCountFaces());

	return true;
}

void CAppRender3D::update(float deltaTime)
{
	double degreesToRotate = 0.0;
	if (deltaTime <= 0.0f)
	{
		return;
	}
	m_currentDeltaTime = deltaTime;

	degreesToRotate = m_rotationSpeed * (deltaTime/1000.0f);
	m_objectRotation += degreesToRotate;

	while (m_objectRotation > 360)
	{
		m_objectRotation -= 360;
	}
	if (m_objectRotation < 0.0)
	{
		m_objectRotation = 0.0;
	}

}

void CAppRender3D::render()
{

	float color[3] = { 1.0f, 1.0f, 1.0f };
	//unsigned int noTexture = 0;
	CVector3 pos;

	double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;
	m_objectPosition.setValues(1.0f, 2.0, -1.0f);

	MathHelper::Matrix4 scaleMatrix;
	scaleMatrix.m[0][0] = 0.25f;
	scaleMatrix.m[1][1] = 0.25f;
	scaleMatrix.m[2][2] = 0.25f;

	MathHelper::Matrix4 translationMatrix;
	translationMatrix.m[0][3] = m_objectPosition.X;
	translationMatrix.m[1][3] = m_objectPosition.Y;
	translationMatrix.m[2][3] = m_objectPosition.Z;
	translationMatrix = MathHelper::Transpose(translationMatrix);

	float cos = cosf((float)totalDegreesRotatedRadians);
	float sin = sinf((float)totalDegreesRotatedRadians);
	
	//Pitch
	MathHelper::Matrix4 rotationX;
	rotationX.m[1][1] = cos;
	rotationX.m[1][2] = -sin;
	rotationX.m[2][1] = sin;
	rotationX.m[2][2] = cos;
	rotationX = MathHelper::Transpose(rotationX);

	//Yaw
	MathHelper::Matrix4 rotationY;
	rotationY.m[0][0] = cos;
	rotationY.m[0][2] = sin;
	rotationY.m[2][0] = -sin;
	rotationY.m[2][2] = cos;
	rotationY = MathHelper::Transpose(rotationY);

	//Roll

	MathHelper::Matrix4 totalRotation = MathHelper::Multiply(rotationX, rotationY);

	MathHelper::Matrix4 modelMatrix = MathHelper::Multiply(totalRotation, translationMatrix);
	//MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrixRotationTranslation((float)totalDegreesRotatedRadians, m_objectPosition);

	if (m_uObjIND > 0)
	{
		m_ptrRenderer->renderObject(&m_uShasderID, &m_uObjIND, &m_TextureID, m_lista.First->getData()->Get_m_iCountFaces(), color, &modelMatrix, COpenGLRenderer::TRIANGLES, false);
		//m_ptrRenderer->renderObject(&m_uShasderID, &m_uObjIND, &noTexture, m_pObjR->Get_m_iCountFaces(), color, &modelMatrix, COpenGLRenderer::TRIANGLES, false);
	}

}

void CAppRender3D::onF2(int mods)
{
	std::wstring wideStringBuffer = L"";
	wideStringBuffer.resize(MAX_PATH);

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	//ofn.lpstrFilter = L" Obj Files\0.obj\0 Stl Files\0.stl\0 3DS Files\0.3ds\0 All files\0.*\0";
	ofn.lpstrFilter = L" Obj Files\0*.obj\0 Stl Files\0*.stl\0 3DS Files\0*.3ds\0 All files\0*.*\0";
	ofn.lpstrFile = &wideStringBuffer[0];
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Select a model file";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wideStringBuffer[0], (int)wideStringBuffer.size(), NULL, 0, NULL, NULL);
		std::string multibyteString(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wideStringBuffer[0], (int)wideStringBuffer.size(), &multibyteString[0], size_needed, NULL, NULL);
		cout << "Filename to load: " << multibyteString.c_str() << endl;
		m_pObjR = new CObjReader();
		m_pObjR->ObjSetMemAndVar(multibyteString); //To read file name
		m_lista.Insert(m_pObjR);
		//m_lista.First = m_lista.End->GetNext();
		initialize();
	}
}

void CAppRender3D::onF12(int mods)
{
	m_ptrWindow = nullptr;
}

void CAppRender3D::onArrowLeft(int mods)
{
	m_lista.First = m_lista.First->GetPrev();
	initialize();
}

void CAppRender3D::onArrowRight(int mods)
{
	m_lista.First = m_lista.First->GetNext();
	initialize();

}
