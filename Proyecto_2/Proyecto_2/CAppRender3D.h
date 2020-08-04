#pragma once
#include <Windows.h>
#include <iostream>
#include "CApp.h"
#include "ListaDoblemeteLigada.h"
#include "Globals.h"
#include "CObjReader.h"

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
	ListaDoblemeteLigada<CObjReader> m_lista;
	unsigned int m_uObjIND;
	unsigned int m_uShasderID;
	unsigned int m_TextureID;

	void Run();
	bool initialize();
	void update(float dt);
	void render();

	void onF2(int mods);       
	void onF12(int mods);
	void onArrowLeft(int mods);
	void onArrowRight(int mods);

};