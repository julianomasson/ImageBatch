#include "ResizePanel.h"

// WX
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/progdlg.h>

// OpenCV
#include <opencv2/opencv.hpp>

ResizePanel::ResizePanel(wxWindow* parent) : wxPanel(parent)
{
	auto boxSizer = new wxBoxSizer(wxVERTICAL);
	
	auto radioFree = new wxRadioButton(this, freeAspect, "Free aspect");
	radioFree->Bind(wxEVT_RADIOBUTTON, &ResizePanel::OnRadioChanged, this);
	radioFree->SetValue(true);
	boxSizer->Add(radioFree, 0, wxALL, 5);
	auto radioFixedWidth = new wxRadioButton(this, fixedWidth, "Fixed width");
	radioFixedWidth->Bind(wxEVT_RADIOBUTTON, &ResizePanel::OnRadioChanged, this);
	boxSizer->Add(radioFixedWidth, 0, wxALL, 5);
	auto radioFixedHeight = new wxRadioButton(this, fixedHeight, "Fixed height");
	radioFixedHeight->Bind(wxEVT_RADIOBUTTON, &ResizePanel::OnRadioChanged, this);
	boxSizer->Add(radioFixedHeight, 0, wxALL, 5);

	auto flexGrid = new wxFlexGridSizer(2);

	flexGrid->Add(new wxStaticText(this, wxID_ANY, "Width"), 0, wxALL, 5);
	spinWidth = new wxSpinCtrl(this, wxID_ANY);
	spinWidth->SetMin(1);
	spinWidth->SetMax(50000);
	flexGrid->Add(spinWidth, 0, wxALL, 5);
	flexGrid->Add(new wxStaticText(this, wxID_ANY, "Height"), 0, wxALL, 5);
	spinHeight = new wxSpinCtrl(this, wxID_ANY);
	spinHeight->SetMin(1);
	spinHeight->SetMax(50000);
	flexGrid->Add(spinHeight, 0, wxALL, 5);

	boxSizer->Add(flexGrid, 0, wxALL | wxEXPAND, 5);

	this->SetSizer(boxSizer);
	this->Layout();
	this->Centre(wxBOTH);
}

ResizePanel::~ResizePanel()
{

}

bool ResizePanel::Process(const std::vector<std::string>& inputFiles,
	const std::string& outputDir)
{
	const auto numberOfFiles = inputFiles.size();
	const auto updateString = "/" + std::to_string(numberOfFiles);
	wxProgressDialog progDialog("Resizing images", "0" + updateString,
		numberOfFiles, this, wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_CAN_ABORT);
	// Get the parameters
	const auto width = spinWidth->GetValue();
	const auto height = spinHeight->GetValue();
	const auto useFixedHeight = ((wxRadioButton*)this->GetWindowChild(fixedHeight))->GetValue();
	const auto useFixedWidth = ((wxRadioButton*)this->GetWindowChild(fixedWidth))->GetValue();
	int count = 0;
	for (const auto &file : inputFiles)
	{
		if (!progDialog.Update(count, std::to_string(count) + updateString))
		{
			return false;
		}
		count++;
		const auto fileName = GetFileName(file);
		// Load file
		const auto img = cv::imread(file);
		if (!img.data)
		{
			wxLogError("Error loading image " + wxString(fileName));
			continue;
		}
		cv::Size sizeDst(width, height);
		// Check if some radio was selected
		if (useFixedHeight)
		{
			sizeDst.width = (img.cols * sizeDst.height) / img.rows;
		}
		else if (useFixedWidth)
		{
			sizeDst.height = (img.rows * sizeDst.width) / img.cols;
		}
		// Resize
		cv::Mat dst;
		cv::resize(img, dst, sizeDst);
		if (!dst.data)
		{
			wxLogError("Error resizing image " + wxString(fileName));
			continue;
		}
		// Save image
		if (!cv::imwrite(outputDir + fileName, dst))
		{
			wxLogError("Error saving image " + wxString(fileName));
		}
	}
	return true;
}

void ResizePanel::OnRadioChanged(wxCommandEvent & event)
{
	spinWidth->Enable();
	spinHeight->Enable();
	switch (event.GetId())
	{
	case ResizePanel::fixedWidth:
		spinHeight->Disable();
		break;
	case ResizePanel::fixedHeight:
		spinWidth->Disable();
		break;
	}
}
