#pragma once
#include <vector>
#include <string>
#include <wx/panel.h>
#include "Operation.h"

class wxTextCtrl;

class RenamePanel : public wxPanel, public Operation
{
public:
	RenamePanel(wxWindow* parent);
	~RenamePanel();

	// Rename all the input files and save them in the output dir
	bool Process(const std::vector<std::string>& inputFiles,
		const std::string& outputDir);

private:
	wxTextCtrl* textCtrl;

	void OnTextCtrlChanged(wxCommandEvent& event);
};
