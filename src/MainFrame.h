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
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800, 600),
		long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MainFrame();
private:
	wxDirPickerCtrl* dirPickerInput;
	wxDirPickerCtrl* dirPickerOutput;
	wxNotebook* notebook;

	std::vector<Operation*> operations;

	void OnCkUseInputAsOutput(wxCommandEvent& event);
	void OnBtStart(wxCommandEvent& event);
};
