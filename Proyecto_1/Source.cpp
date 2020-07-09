#include <iostream>
#include "CObjReader.h"

int main()
{
	//CObjReader* ptrObjReader = new CObjReader();m

	CObjReader* cubo = new CObjReader("SOLDIER.obj");
	cubo->readObjFile(cubo->Get_m_sFileName());
	system("pause");
	system("cls");
	cubo->Tokinize();
	system("pause");
	return 0;
}