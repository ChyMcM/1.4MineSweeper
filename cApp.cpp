#include "cApp.h"

wxIMPLEMENT_APP(cApp);
cApp::cApp()
{

}
cApp::~cApp()
{

}
bool cApp::OnInIt()
{
	frame1 = new Main();
	frame1->Show();
	return true;
}