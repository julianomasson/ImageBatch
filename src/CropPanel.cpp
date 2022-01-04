#include "CropPanel.h"

// WX
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/progdlg.h>

// OpenCV
#include <opencv2/opencv.hpp>

CropPanel::CropPanel(wxWindow* parent) : wxPanel(parent)
{
	auto boxSizer = new wxBoxSizer(wxVERTICAL);
	
	auto flexGrid = new wxFlexGridSizer(2);

	flexGrid->Add(new wxStaticText(this, wxID_ANY, "Left"), 0, wxALL, 5);
	spinLeft = new wxSpinCtrl(this, wxID_ANY);
	spinLeft->SetMax(50000);
	flexGrid->Add(spinLeft, 0, wxALL, 5);

	flexGrid->Add(new wxStaticText(this, wxID_ANY, "Right"), 0, wxALL, 5);
	spinRight = new wxSpinCtrl(this, wxID_ANY);
	spinRight->SetMax(50000);
	flexGrid->Add(spinRight, 0, wxALL, 5);

	flexGrid->Add(new wxStaticText(this, wxID_ANY, "Top"), 0, wxALL, 5);
	spinTop = new wxSpinCtrl(this, wxID_ANY);
	spinTop->SetMax(50000);
	flexGrid->Add(spinTop, 0, wxALL, 5);

	flexGrid->Add(new wxStaticText(this, wxID_ANY, "Bottom"), 0, wxALL, 5);
	spinBottom = new wxSpinCtrl(this, wxID_ANY);
	spinBottom->SetMax(50000);
	flexGrid->Add(spinBottom, 0, wxALL, 5);

	boxSizer->Add(flexGrid, 0, wxALL | wxEXPAND, 5);

	this->SetSizer(boxSizer);
	this->Layout();
	this->Centre(wxBOTH);
}

CropPanel::~CropPanel()
{

}

bool CropPanel::Process(const std::vector<std::string>& inputFiles,
	const std::string& outputDir)
{
	const auto numberOfFiles = inputFiles.size();
	const auto updateString = "/" + std::to_string(numberOfFiles);
	wxProgressDialog progDialog("Cropping images", "0" + updateString,
		numberOfFiles, this, wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_CAN_ABORT);
	// Get the parameters
	const auto leftOffset = spinLeft->GetValue();
	const auto rightOffset = spinRight->GetValue();
	const auto topOffset = spinTop->GetValue();
	const auto bottomOffset = spinBottom->GetValue();
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
		// Crop
		auto croppedImg = img(cv::Range(topOffset, img.rows - bottomOffset),
			cv::Range(leftOffset, img.cols - rightOffset));
		if (!croppedImg.data)
		{
			wxLogError("Error cropping image " + wxString(fileName));
			continue;
		}
		// Save image
		if (!cv::imwrite(outputDir + fileName, croppedImg))
		{
			wxLogError("Error saving image " + wxString(fileName));
		}
	}
	return true;
}