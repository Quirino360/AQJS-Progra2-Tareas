#pragma once
#include <Windows.h>
#include <iostream>
#include "CApp.h"
#include "ListaDoblemeteLigada.h"
#include "Globals.h"
#include "CObjReader.h"
#include "CVector3.h"
#include "KdTree.h"

class CAppRender3D :
	public CApp
{
public:
	CAppRender3D();
	~CAppRender3D();

	double m_currentDeltaTime;
	double m_objectRotation;
	CVector3 m_objectPosition;
	double m_rotationSpeed;

	CObjReader* m_pObjR;
	KdTree* tree;
	ListaDoblemeteLigada<CObjReader> m_lista;
	unsigned int m_uObjIND;
	unsigned int m_uShasderID;
	unsigned int m_TextureID;

	void Run();
	bool initialize();
	void update(float dt);
	void render();
	void renderMultiple (KdTreeNode* kd);
	void setObjXYZ();
	void setObjXYZ(KdTreeNode* kd);

	void onF2(int mods);       
	void onF3(int mods);
	void onF4(int mods);
	void onF5(int mods);
	void onF12(int mods);
	void onArrowUp(int mods);
	void onArrowDown(int mods);
	void onArrowLeft(int mods);
	void onArrowRight(int mods);

private:

	bool RenderMode;
	float pos_x;
	float pos_y;

	float top = 2;
	float down = -2;
	float left = 4;
	float right = -4;

	CVector3 ButtumRight;
	CVector3 TopLeft;

	int ID;

	MathHelper::Matrix4 modelMatrix;

	bool Inside();
};