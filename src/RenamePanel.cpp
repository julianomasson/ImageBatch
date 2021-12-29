#include "RenamePanel.h"

// WX
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/progdlg.h>

RenamePanel::RenamePanel(wxWindow* parent) : wxPanel(parent)
{
	auto boxSizer = new wxBoxSizer(wxVERTICAL);
	
	boxSizer->Add(new wxStaticText(this, wxID_ANY, 
		"Define the name template below, following the example: Test_?\n"
		"The \"?\" will be replaced by the count of images."
	), 0, wxALL, 5);

	auto flexGrid = new wxFlexGridSizer(2);
	flexGrid->Add(new wxStaticText(this, wxID_ANY, "Name template"), 0, wxALL, 5);
	textCtrl = new wxTextCtrl(this, wxID_ANY);
	textCtrl->Bind(wxEVT_TEXT, &RenamePanel::OnTextCtrlChanged, this);
	flexGrid->Add(textCtrl, 0, wxALL, 5);

	boxSizer->Add(flexGrid, 0, wxALL | wxEXPAND, 5);

	this->SetSizer(boxSizer);
	this->Layout();
	this->Centre(wxBOTH);
}

RenamePanel::~RenamePanel()
{

}

bool RenamePanel::Process(const std::vector<std::string>& inputFiles,
	const std::string& outputDir)
{
	if (textCtrl->GetValue().Find("?") == wxNOT_FOUND)
	{
		wxLogWarning("You need to add at least one \"?\" in the name template.");
		return false;
	}
	const auto numberOfFiles = inputFiles.size();
	const auto updateString = "/" + std::to_string(numberOfFiles);
	wxProgressDialog progDialog("Renaming images", "0" + updateString,
		numberOfFiles, this, wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_CAN_ABORT);
	// Get number of digits in the count
	const auto numberOfDigits = std::to_string(numberOfFiles).size() + 1;
	int count = 0;
	for (const auto &file : inputFiles)
	{
		if (!progDialog.Update(count, std::to_string(count) + updateString))
		{
			return false;
		}
		// Create the new file name
		const auto countString = std::to_string(count);
		const auto numberOfZeros =  numberOfDigits - countString.size() - 1;
		auto newName = std::to_string(static_cast<int>(std::pow(10,numberOfZeros))) + countString;
		newName[0] = '0';
		auto nameTemplate = textCtrl->GetValue();
		nameTemplate.Replace("?", newName);
		if (!wxCopyFile(file, outputDir + nameTemplate + GetFileExtension(file)))
		{
			wxLogError("Error renaming the image " + wxString(GetFileName(file)));
		}
		count++;
	}
	return true;
}

void RenamePanel::OnTextCtrlChanged(wxCommandEvent& event)
{
	const auto text = textCtrl->GetValue().ToStdString();
	const auto textSize = text.size();
	std::string charToSeek = "?";
	int count = 0;
	for (size_t i = 0; i < textSize; i++)
	{
		if (text[i] == charToSeek)
		{
			count++;
			if (count >= 2)
			{
				wxLogError("You can only add one \"?\".");
				textCtrl->SetValue(text.substr(0, i));
				return;
			}
		}
	}
}
