#include <iostream>
#include "CObjReader.h"
#include "CApp.h"
#include "CAppRender3D.h"
#include "ListaDoblemeteLigada.h"

int main()
{
	/*ListaDoblemeteLigada m_lista;

	m_lista.Insert(100);
	m_lista.Insert(100);
	m_lista.Insert(5);

	m_lista.DeleteNumber(100);
	m_lista.Print();
	system("pause");*/

	//CObjReader Reader;

	CApp* app = new CAppRender3D();          // Pointer to BASE class CApp
	//app = new CAppCubeTest(800, 600);        // Using pointer to base class, create a new object of DERIVED class
	app->Run();                              // Run the app
	delete app;                             // Delete pointer
	app = NULL;
	
	return 0;
	
}