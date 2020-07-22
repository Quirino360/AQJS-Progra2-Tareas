#pragma once
#include <Windows.h>
#include "CApp.h"
#include <iostream>
#include "Globals.h"
#include "CObjReader.h"
#include "ListaDoblemeteLigada.h"

class CAppRender3D :
	public CApp
{
public:
	CAppRender3D();
	~CAppRender3D();

	CObjReader* m_pObjR;
	ListaDoblemeteLigada m_lista;
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