#pragma once
#include <vector>
#include <string>
#include <wx/panel.h>
#include "Operation.h"

class wxSpinCtrl;

class CropPanel : public wxPanel, public Operation
{
public:
	CropPanel(wxWindow* parent);
	~CropPanel();

	// Crop all the input files and save them in the output dir
	bool Process(const std::vector<std::string>& inputFiles,
		const std::string& outputDir);

private:
	wxSpinCtrl* spinLeft;
	wxSpinCtrl* spinRight;
	wxSpinCtrl* spinTop;
	wxSpinCtrl* spinBottom;
};
