#pragma once
#include <vector>
#include <wx/frame.h>

class wxDirPickerCtrl;
class wxNotebook;
class Operation;

class MainFrame : public wxFrame
{
public:
	MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "ImageBatch",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 425),
		long style = wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN);

	~MainFrame();
private:
	wxDirPickerCtrl* dirPickerInput;
	wxDirPickerCtrl* dirPickerOutput;
	wxNotebook* notebook;

	std::vector<Operation*> operations;

	void OnCkUseInputAsOutput(wxCommandEvent& event);
	void OnBtStart(wxCommandEvent& event);
};
