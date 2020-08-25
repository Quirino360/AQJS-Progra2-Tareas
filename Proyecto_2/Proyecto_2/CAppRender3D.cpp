#include "CAppRender3D.h"
#include "CTextureLoader.h"
#include "List_Impl.cpp"
#include <cstdlib>
#include <time.h>

CAppRender3D::CAppRender3D() :
	ID(0),
	RenderMode(true),
	m_uObjIND{ 0 }, 
	m_uShasderID{ 0 },
	m_pObjR {nullptr},
	m_currentDeltaTime {0.0},
	m_objectRotation {0.0},
	m_objectPosition {0.0f, 0.0f, 0.0f},
	m_rotationSpeed {DEFAULT_ROTATION_SPEED}
{
	TopLeft = CVector3(left, top, 0);
	ButtumRight = CVector3(right, down, 0);
	tree = nullptr;
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
			initialize();

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

	if (m_pObjR == nullptr)
	{
		m_pObjR = new CObjReader();
		tree = new KdTree();
		m_pObjR->ObjSetMemAndVar("Cubo.obj");
		m_pObjR->set_m_uObjID(ID);
		m_lista.Insert(m_pObjR);
		tree->insertElementObj(m_pObjR);
		//setObjXYZ();
	}

	pos_x = 3 - rand() % (3 + 3);
	pos_y = 2 - rand() % (2 + 2);

	m_lista.getCurrentValue()->Set_m_objectPosition(pos_x, pos_y, 0);

	m_lista.getCurrentValue()->set_m_TextureID(0);

	if (!CTextureLoader::loadTexture("../Resources/MEDIA/TEXTURES/mc_dirt_cube_512x384.tga", &m_lista.getCurrentValue()->get_m_TextureID(), m_ptrRenderer))
	{
		cout << "Textura no encontarada" << endl;
	}

	m_uShasderID = m_ptrRenderer->getShaderProgramID(SHADER_PROGRAM_TEXTURED_OBJECT);

	bool savedInGraphicMemory = m_ptrRenderer->allocateGraphicsMemoryForObject(&m_uShasderID, &m_lista.getCurrentValue()->get_m_uObjID() , m_lista.getCurrentValue()->Get_m_pVertices(),
		m_lista.getCurrentValue()->Get_m_iCountVertices(), m_lista.getCurrentValue()->Get_m_pNormales(), m_lista.getCurrentValue()->Get_m_iCountNormales(),
		m_lista.getCurrentValue()->Get_m_pUVCoords(), m_lista.getCurrentValue()->Get_m_iCountUVCoords(), m_lista.getCurrentValue()->Get_m_pIndVertices(),
		m_lista.getCurrentValue()->Get_m_iCountFaces(), m_lista.getCurrentValue()->Get_m_pIndNormales(), m_lista.getCurrentValue()->Get_m_iCountFaces(),
		m_lista.getCurrentValue()->Get_m_pIndUVCoords(), m_lista.getCurrentValue()->Get_m_iCountFaces());


	

	cout << "pos x = " << m_lista.getCurrentValue()->Get_m_objectPosition()->X << endl;
	cout << "pos y = " << m_lista.getCurrentValue()->Get_m_objectPosition()->Y << endl;
	cout << "Obj ID = " << m_lista.getCurrentValue()->get_m_uObjID() << endl;

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

	if (Inside() && RenderMode == true)
	{
		float color[3] = { 1.0f, 1.0f, 1.0f };
		setObjXYZ();

		if (m_lista.getCurrentValue()->get_m_uObjID() > 0)
		{
			m_ptrRenderer->renderObject(&m_uShasderID, &m_lista.getCurrentValue()->get_m_uObjID(), &m_lista.getCurrentValue()->get_m_TextureID(), m_lista.getCurrentValue()->Get_m_iCountFaces(), color, &modelMatrix, COpenGLRenderer::TRIANGLES, false);
			//m_ptrRenderer->renderObject(&m_uShasderID, &m_uObjIND, &noTexture, m_pObjR->Get_m_iCountFaces(), color, &modelMatrix, COpenGLRenderer::TRIANGLES, false);
		}
	}
	else if (RenderMode == false)
	{
		renderMultiple(tree->m_root);
	}

	
}

void CAppRender3D::renderMultiple(KdTreeNode* kd)
{
	unsigned int noTexture = 0;
	float color[3] = { 1.0f,1.0f,1.0f };
	if (kd->getLeft() != nullptr)
	{
		renderMultiple(kd->getLeft());

	}
	if (kd->getRigth() != nullptr) 
	{
		renderMultiple(kd->getRigth());
	}
	if (Inside()) {

		setObjXYZ(kd);
		
		if (kd->get_m_Data()->get_m_uObjID() > 0) 
		{
			m_ptrRenderer->renderObject(&m_uShasderID, &kd->get_m_Data()->get_m_uObjID(), &kd->get_m_Data()->get_m_TextureID(), kd->get_m_Data()->Get_m_iCountFaces(), color, &modelMatrix, COpenGLRenderer::TRIANGLES, false);
		}

	}
}




void CAppRender3D::setObjXYZ()
{
	float color[3] = { 1.0f, 1.0f, 1.0f };

	//unsigned int noTexture = 0;
	//CVector3 pos;

	CVector3 totalDegreesRotatedRadians = *m_lista.getCurrentValue()->Get_m_objectRotation() * (3.1459 / 180.0);

	std::srand(time(NULL));

	MathHelper::Matrix4 scaleMatrix;
	scaleMatrix.m[0][0] = m_lista.getCurrentValue()->Get_m_objectScale()->getX();
	scaleMatrix.m[1][1] = m_lista.getCurrentValue()->Get_m_objectScale()->getY();
	scaleMatrix.m[2][2] = m_lista.getCurrentValue()->Get_m_objectScale()->getZ();

	MathHelper::Matrix4 translationMatrix;
	translationMatrix.m[0][3] =m_lista.getCurrentValue()->Get_m_objectPosition()->X;
	translationMatrix.m[1][3] =m_lista.getCurrentValue()->Get_m_objectPosition()->Y;
	translationMatrix.m[2][3] =m_lista.getCurrentValue()->Get_m_objectPosition()->Z;
	translationMatrix = MathHelper::Transpose(translationMatrix);

	float cosx = cosf((float)totalDegreesRotatedRadians.X);
	float cosy = cosf((float)totalDegreesRotatedRadians.Y);
	float cosz = cosf((float)totalDegreesRotatedRadians.Z);

	float sinx = sinf((float)totalDegreesRotatedRadians.X);
	float siny = sinf((float)totalDegreesRotatedRadians.Y);
	float sinz = sinf((float)totalDegreesRotatedRadians.Z);


	//Pitch
	MathHelper::Matrix4 rotationX;
	rotationX.m[1][1] = cosx;
	rotationX.m[1][2] = -sinx;
	rotationX.m[2][1] = sinx;
	rotationX.m[2][2] = cosx;
	rotationX = MathHelper::Transpose(rotationX);

	//Yaw
	MathHelper::Matrix4 rotationY;
	rotationY.m[0][0] = cosy;
	rotationY.m[0][2] = siny;
	rotationY.m[2][0] = -siny;
	rotationY.m[2][2] = cosy;
	rotationY = MathHelper::Transpose(rotationY);

	//Roll
	MathHelper::Matrix4 rotationZ;
	rotationY.m[0][0] = cosz;
	rotationY.m[0][1] = sinz;
	rotationY.m[1][0] = -sinz;
	rotationY.m[1][1] = cosz;
	rotationY = MathHelper::Transpose(rotationZ);

	MathHelper::Matrix4 totalRotation = MathHelper::Multiply(rotationX, rotationY);
	totalRotation = MathHelper::Multiply(totalRotation, rotationZ);

	modelMatrix = MathHelper::Multiply(totalRotation, translationMatrix);
	modelMatrix = MathHelper::Multiply(modelMatrix, scaleMatrix);
}

void CAppRender3D::setObjXYZ(KdTreeNode* kd)
{
	float color[3] = { 1.0f, 1.0f, 1.0f };

	//unsigned int noTexture = 0;
	//CVector3 pos;
	
	CVector3 totalDegreesRotatedRadians = *kd->get_m_Data()->Get_m_objectRotation() * (3.1459 / 180.0);

	std::srand(time(NULL));

	MathHelper::Matrix4 scaleMatrix;
	scaleMatrix.m[0][0] = kd->get_m_Data()->Get_m_objectScale()->getX();
	scaleMatrix.m[1][1] = kd->get_m_Data()->Get_m_objectScale()->getY();
	scaleMatrix.m[2][2] = kd->get_m_Data()->Get_m_objectScale()->getZ();

	MathHelper::Matrix4 translationMatrix;
	translationMatrix.m[0][3] = kd->get_m_Data()->Get_m_objectPosition()->X;
	translationMatrix.m[1][3] = kd->get_m_Data()->Get_m_objectPosition()->Y;
	translationMatrix.m[2][3] = kd->get_m_Data()->Get_m_objectPosition()->Z;
	translationMatrix = MathHelper::Transpose(translationMatrix);

	float cosx = cosf((float)totalDegreesRotatedRadians.X);
	float cosy = cosf((float)totalDegreesRotatedRadians.Y);
	float cosz = cosf((float)totalDegreesRotatedRadians.Z);

	float sinx = sinf((float)totalDegreesRotatedRadians.X);
	float siny = sinf((float)totalDegreesRotatedRadians.Y);
	float sinz = sinf((float)totalDegreesRotatedRadians.Z);


	//Pitch
	MathHelper::Matrix4 rotationX;
	rotationX.m[1][1] = cosx;
	rotationX.m[1][2] = -sinx;
	rotationX.m[2][1] = sinx;
	rotationX.m[2][2] = cosx;
	rotationX = MathHelper::Transpose(rotationX);

	//Yaw
	MathHelper::Matrix4 rotationY;
	rotationY.m[0][0] = cosy;
	rotationY.m[0][2] = siny;
	rotationY.m[2][0] = -siny;
	rotationY.m[2][2] = cosy;
	rotationY = MathHelper::Transpose(rotationY);

	//Roll
	MathHelper::Matrix4 rotationZ;
	rotationY.m[0][0] = cosz;
	rotationY.m[0][1] = sinz;
	rotationY.m[1][0] = -sinz;
	rotationY.m[1][1] = cosz;
	rotationY = MathHelper::Transpose(rotationZ);

	MathHelper::Matrix4 totalRotation = MathHelper::Multiply(rotationX, rotationY);
	totalRotation = MathHelper::Multiply(totalRotation, rotationZ);

	modelMatrix = MathHelper::Multiply(totalRotation, translationMatrix);
	modelMatrix = MathHelper::Multiply(modelMatrix, scaleMatrix);
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

		ID++;
		m_pObjR->set_m_uObjID(ID);
		m_lista.Insert(m_pObjR);
		//setObjXYZ();
		//initialize();
	}
}

void CAppRender3D::onF3(int mods)
{
	for (int i = 0; i <= 20; i++)
	{
		m_pObjR = new CObjReader();
		m_pObjR->ObjSetMemAndVar("Cubo.obj");
		m_pObjR->set_m_uObjID(ID);
		m_lista.Insert(m_pObjR);
		initialize();
		tree->insertElementObj(m_pObjR);
		//setObjXYZ();
		cout << "Cubo creado" << endl;
	}
}

void CAppRender3D::onF4(int mods)
{
	RenderMode = true;
}

void CAppRender3D::onF5(int mods)
{
	RenderMode = false;
}

void CAppRender3D::onF12(int mods)
{
	m_ptrWindow = nullptr;
}

void CAppRender3D::onArrowUp(int mods)
{
	if (mods & KEY_MOD_SHIFT)
	{
		
		top += 0.1f;
		std::cout << "Top = " << top << std::endl;
		//return;
	}
	if (mods & KEY_MOD_CONTROL)
	{
		down += 0.1f;
		std::cout << "Down = " << down << std::endl;
		//return;
	}
	TopLeft = CVector3(left, top, 0);
	ButtumRight = CVector3(right, down, 0);
}

void CAppRender3D::onArrowDown(int mods)
{
	if (mods & KEY_MOD_SHIFT)
	{
		top -= 0.1f;
		std::cout << "Top = " << top << std::endl;
		//return;
	}
	if (mods & KEY_MOD_CONTROL)
	{
		down -= 0.1f;
		std::cout << "Down = " << down << std::endl;
		//return;
	}
	TopLeft = CVector3(left, top, 0);
	ButtumRight = CVector3(right, down, 0);
}

void CAppRender3D::onArrowLeft(int mods)
{
	if (mods & KEY_MOD_SHIFT)
	{
		left -= 0.1f;
		std::cout << "Left = " << left << std::endl;
		//return;
	}
	if (mods & KEY_MOD_CONTROL)
	{
		std::cout << "Right = " << right << std::endl;
		right -= 0.1f;
		//return;
	}
	if (!mods)
	{
		m_lista.SetToPrev();
		std::cout << "ID = " << m_lista.getCurrentValue()->get_m_uObjID() << endl;
	}
	TopLeft = CVector3(left, top, 0);
	ButtumRight = CVector3(right, down, 0);
}

void CAppRender3D::onArrowRight(int mods)
{
	if (mods & KEY_MOD_SHIFT)
	{
		left += 0.1f;
		std::cout << "Left = " << left << std::endl;
		//return;
	}
	if (mods & KEY_MOD_CONTROL)
	{
		std::cout << "Right = " << right << std::endl;
		right += 0.1f;
		//return;
	}
	if (!mods)
	{
		m_lista.SetToNext();
		std::cout << "ID = " << m_lista.getCurrentValue()->get_m_uObjID() << endl;
	}
	TopLeft = CVector3(left, top, 0);
	ButtumRight = CVector3(right, down, 0);
}

bool CAppRender3D::Inside()
{
	if (m_lista.getCurrentValue()->Get_m_objectPosition()->getX() <= TopLeft.getX() && m_lista.getCurrentValue()->Get_m_objectPosition()->getX() >= ButtumRight.getX()
		&& m_lista.getCurrentValue()->Get_m_objectPosition()->getY() <= TopLeft.getY() && m_lista.getCurrentValue()->Get_m_objectPosition()->getY() >= ButtumRight.getY())
	{
		return true;
	}
	return false;
}
