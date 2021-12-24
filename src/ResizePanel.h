#pragma once
#include <vector>
#include <string>
#include <wx/panel.h>
#include "Operation.h"

class wxSpinCtrl;

class ResizePanel : public wxPanel, public Operation
{
public:
	ResizePanel(wxWindow* parent);
	~ResizePanel();

	// Resize all the input files and save them in the output dir
	bool Process(const std::vector<std::string>& inputFiles,
		const std::string& outputDir);

private:
	wxSpinCtrl* spinWidth;
	wxSpinCtrl* spinHeight;

	// Disable/Enable the spinWidth and spinHeight depending on the desired aspect ratio
	void OnRadioChanged(wxCommandEvent& event);

	// Radio ids
	enum
	{
		freeAspect,
		fixedWidth,
		fixedHeight
	};
};
