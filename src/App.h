#pragma once

#ifdef WIN32
#include "wx/msw/winundef.h"
#endif

#include <wx\app.h>

class MainFrame;

class App : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();
private:
	MainFrame* mainFrame;
};

DECLARE_APP(App)
