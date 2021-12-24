#include "ResizePanel.h"

// WX
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>

ResizePanel::ResizePanel(wxWindow* parent) : wxPanel(parent)
{
	auto boxSizer = new wxBoxSizer(wxVERTICAL);
	
	auto radioFree = new wxRadioButton(this, freeAspect, "Free aspect");
	radioFree->Bind(wxEVT_RADIOBUTTON, &ResizePanel::OnRadioChanged, this);
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
	spinWidth->SetMax(50000);
	flexGrid->Add(spinWidth, 0, wxALL, 5);
	flexGrid->Add(new wxStaticText(this, wxID_ANY, "Height"), 0, wxALL, 5);
	spinHeight = new wxSpinCtrl(this, wxID_ANY);
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
	return false;
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
