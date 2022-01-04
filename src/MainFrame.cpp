#include "MainFrame.h"

// WX
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/log.h>
#include <wx/dir.h>

#include "Operation.h"
#include "ResizePanel.h"
#include "CropPanel.h"
#include "RenamePanel.h"

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetIcons(wxICON(AAAAAA_ICON));
	this->SetBackgroundColour(wxColor(240, 240, 240));
	auto boxSizer = new wxBoxSizer(wxVERTICAL);
	
	// Directories
	auto staticSizerDir = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, "Image selection"), wxVERTICAL);
	auto flexGridDir = new wxFlexGridSizer(2);
	flexGridDir->AddGrowableCol(1);
	flexGridDir->SetFlexibleDirection(wxBOTH);
	// Input dir
	flexGridDir->Add(new wxStaticText(this, wxID_ANY, "Input directory"));
	dirPickerInput = new wxDirPickerCtrl(this, wxID_ANY);
	flexGridDir->Add(dirPickerInput, 0, wxALL | wxEXPAND, 5);
	// Output dir
	flexGridDir->Add(new wxStaticText(this, wxID_ANY, "Output directory"));
	dirPickerOutput = new wxDirPickerCtrl(this, wxID_ANY);
	flexGridDir->Add(dirPickerOutput, 0, wxALL | wxEXPAND, 5);
	// Used the input directory as output
	flexGridDir->AddSpacer(1);
	auto cbUseInputAsOutput = new wxCheckBox(
		this, wxID_ANY, "Use input directory as output (the files will be overwritten).");
	cbUseInputAsOutput->Bind(wxEVT_CHECKBOX, &MainFrame::OnCkUseInputAsOutput, this);
	flexGridDir->Add(cbUseInputAsOutput, 0, wxALL, 5);
	staticSizerDir->Add(flexGridDir, 1, wxALL | wxEXPAND, 5);
	boxSizer->Add(staticSizerDir, 0, wxALL | wxEXPAND, 5);

	// Operations
	auto staticSizerOperations = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, "Operations"), wxVERTICAL);
	notebook = new wxNotebook(this, wxID_ANY);

	auto resizePanel = new ResizePanel(notebook);
	notebook->AddPage(resizePanel, "Resize", true);
	operations.emplace_back(resizePanel);

	auto cropPanel = new CropPanel(notebook);
	notebook->AddPage(cropPanel, "Crop", true);
	operations.emplace_back(cropPanel);

	auto renamePanel = new RenamePanel(notebook);
	notebook->AddPage(renamePanel, "Rename", true);
	operations.emplace_back(renamePanel);

	notebook->SetSelection(0);

	staticSizerOperations->Add(notebook, 1, wxALL | wxEXPAND, 5);
	boxSizer->Add(staticSizerOperations, 0, wxALL | wxEXPAND, 5);

	// Button start
	auto btStart = new wxButton(this, wxID_ANY, "Start");
	btStart->Bind(wxEVT_BUTTON, &MainFrame::OnBtStart, this);
	boxSizer->Add(btStart, 0, wxALIGN_CENTER_HORIZONTAL, 5);


	this->SetSizer(boxSizer);
	this->Layout();
	this->Centre(wxBOTH);
}

MainFrame::~MainFrame()
{

}

void MainFrame::OnCkUseInputAsOutput(wxCommandEvent & event)
{
	const auto state = event.IsChecked();
	if (state)
	{
		dirPickerOutput->SetPath(dirPickerInput->GetPath());
	}
	dirPickerOutput->Enable(!state);
}

void MainFrame::OnBtStart(wxCommandEvent & event)
{
	// Update the output if the checkbox is checked
	OnCkUseInputAsOutput((wxCommandEvent) NULL);
	// Get the dir
	const auto inputDir = dirPickerInput->GetPath();
	const auto outputDir = dirPickerOutput->GetPath() + "/";
	if (inputDir == "" || outputDir == "")
	{
		wxLogError("Please select the input and output directories.");
		return;
	}
	// Get the files
	std::vector<std::string> files;
	// Supported files got from the OpenCV imread documentation
	std::vector<std::string> supportedFiles = { "JPG", "jpg",
		"JPEG", "jpeg",
		"PNG", "png",
		"TIFF", "tiff"
	};
	wxArrayString filesAux;
	const auto numberOfFiles = wxDir::GetAllFiles(inputDir, &filesAux);
	for (size_t i = 0; i < numberOfFiles; i++)
	{
		const auto file = filesAux.Item(i);
		wxString ext;
		wxFileName::SplitPath(file, nullptr, nullptr, &ext);
		for (const auto& sup : supportedFiles)
		{
			if (sup == ext)
			{
				files.emplace_back(file.ToStdString());
				break;
			}
		}
	}
	if (files.size() == 0)
	{
		wxLogError("The selected input directory did not have any supported file.");
		return;
	}
	const auto selectedOperation = notebook->GetSelection();
	if (selectedOperation == wxNOT_FOUND || selectedOperation >= operations.size())
	{
		wxLogError("Could not define the operation.");
	}
	if (!operations[selectedOperation]->Process(files, outputDir.ToStdString()))
	{
		wxLogError("Error in the operation");
	}
}
