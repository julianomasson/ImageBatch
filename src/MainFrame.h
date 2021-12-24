#pragma once
#include <wx/frame.h>

class wxDirPickerCtrl;

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

	void OnCkUseInputAsOutput(wxCommandEvent& event);
};
