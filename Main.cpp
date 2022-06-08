#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
      EVT_BUTTON(10001, OnButtonClick)
wxEND_EVENT_TABLE()
Main::Main() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(30,30), wxSize(800,600))
{
	btn = new wxButton * [height * width];
	wxGridSizer* grid = new wxGridSizer(height, width, 0, 0);
	field = new int [height * width];
	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			btn[y * width + x] = new wxButton(this, 10000 + (y * width + x));
			btn[y * width + x]->SetFont(font);
			grid->Add(btn[y * width + x], 1, wxEXPAND | wxALL);

			btn[y * width + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::OnButtonClick, this);
			field[y* width + x] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}
Main::~Main()
{
	delete[]btn;
}
void Main::OnButtonClick(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % width;
	int y = (evt.GetId() - 10000) / width;
	if (firstclick)
	{
		int mines = 30;
		while(mines)
		{
			int rx = rand() % width;
			int ry = rand() % height;
			if (field[ry * width + rx] == 0 && rx != x && ry != y)
			{
				field[ry * width + rx] = -1;
				mines--;
			}
		}
		firstclick = false;
	}
	btn[y * width + x]->Enable(false);
	if (field[y * width + x] == -1)
	{
		wxMessageBox("Game Over :c");
		//reset
		firstclick = true;
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				field[y * width + x] = 0;
				btn[y * width + x]->SetLabel("");
				btn[y * width + x]->Enable(true);
			}
		}
	}
	else
	{
		int nearbyboom = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (field[(y + j) * width + (x + i)] == -1)
				{
					nearbyboom++;
				}
			}
			if (nearbyboom > 0)
			{
				btn[y * width + x]->SetLabel(std::to_string(nearbyboom));
			}
		}
	}
	evt.Skip();
}