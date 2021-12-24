#include "MainFrame.h"

// WX
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>

#include "Operation.h"
#include "ResizePanel.h"

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetBackgroundColour(wxColor(240, 240, 240));
	auto boxSizer = new wxBoxSizer(wxVERTICAL);
	
	// Directories
	auto staticSizerDir = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, "Image selection"), wxVERTICAL);
	auto flexGridDir = new wxFlexGridSizer(2);
	// Input dir
	flexGridDir->Add(new wxStaticText(this, wxID_ANY, "Input directory"));
	dirPickerInput = new wxDirPickerCtrl(this, wxID_ANY);
	flexGridDir->Add(dirPickerInput, 0, wxALL, 5);
	// Output dir
	flexGridDir->Add(new wxStaticText(this, wxID_ANY, "Output directory"));
	dirPickerOutput = new wxDirPickerCtrl(this, wxID_ANY);
	flexGridDir->Add(dirPickerOutput, 0, wxALL, 5);
	// Used the input directory as output
	flexGridDir->AddSpacer(1);
	auto cbUseInputAsOutput = new wxCheckBox(
		this, wxID_ANY, "Use input directory as output \n(the files will be overwritten).");
	cbUseInputAsOutput->Bind(wxEVT_CHECKBOX, &MainFrame::OnCkUseInputAsOutput, this);
	flexGridDir->Add(cbUseInputAsOutput, 0, wxALL, 5);
	staticSizerDir->Add(flexGridDir, 1, wxALIGN_CENTER_HORIZONTAL, 5);
	boxSizer->Add(staticSizerDir, 0, wxALL | wxEXPAND, 5);

	// Operations
	auto staticSizerOperations = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, "Operations"), wxVERTICAL);
	notebook = new wxNotebook(this, wxID_ANY);

	auto resizePanel = new ResizePanel(notebook);
	notebook->AddPage(resizePanel, "Resize", true);
	operations.emplace_back(resizePanel);

	staticSizerOperations->Add(notebook, 1, wxEXPAND | wxALL, 5);
	// Button start
	auto btStart = new wxButton(this, wxID_ANY, "Start");
	btStart->Bind(wxEVT_BUTTON, &MainFrame::OnBtStart, this);
	staticSizerOperations->Add(btStart, 1, wxALIGN_CENTER_HORIZONTAL, 5);

	boxSizer->Add(staticSizerOperations, 0, wxALL | wxEXPAND, 5);


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
}
