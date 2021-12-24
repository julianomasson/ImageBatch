#include "App.h"

#include <wx/image.h>

#include "MainFrame.h"

IMPLEMENT_APP(App)

bool App::OnInit() {
	wxInitAllImageHandlers();
	// Initialize the main window
	mainFrame = new MainFrame(nullptr);
	mainFrame->Show(true);
	this->SetTopWindow(mainFrame);
	return true;
}

int App::OnExit()
{
	return 0;
}
