#pragma once
#include "wx/wx.h"
class Main : public wxFrame
{
public:
	Main();
	~Main();
public:
	int height = 10;
	int width = 10;
	wxButton** btn;
	int* field = nullptr;
	bool firstclick = true;
	void OnButtonClick(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

