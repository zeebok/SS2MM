/***************************************************************
 * Name:      SS2MMMain.cpp
 * Purpose:   Code for Main Frame Class
 * Author:    Ryan Kornheisl (rkornheisl@gmail.com)
 * Created:   2013-01-10
 * Copyright: Ryan Kornheisl (www.shard-tech.com)
 * License:   GPLv3
 **************************************************************/

#include "wx/wxprec.h"

#ifdef WX_PRECOMP
#include "wx_pch.h"
#include <wx/wx.h>
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__


#include "SS2MMMain.h"

BEGIN_EVENT_TABLE(SS2MMFrame, wxFrame)
    EVT_CLOSE(SS2MMFrame::OnClose)
    EVT_MENU(idMenuQuit, SS2MMFrame::OnQuit)
    EVT_MENU(idMenuAbout, SS2MMFrame::OnAbout)
END_EVENT_TABLE()

SS2MMFrame::SS2MMFrame(wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style ) :
    wxFrame( parent, id, title, pos, size, style),
    status(_("Ready")),
    version(_("v0.1"))
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    // File Menu
    mbar = new wxMenuBar(0);
    wxMenu* fileMenu;
    fileMenu = new wxMenu();
    wxMenuItem* menuFileQuit = new wxMenuItem(fileMenu, idMenuQuit, wxString(wxT("&Quit")) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL);
    fileMenu->Append(menuFileQuit );
    mbar->Append(fileMenu, wxT("&File"));

    // Mod Menu
    wxMenu* modMenu;
    modMenu = new wxMenu();
    wxMenuItem* menuModScan = new wxMenuItem(modMenu, idMenuScan, wxString(wxT("&Scan")) + wxT('\t') + wxT("F5"), wxT("Scan for available mods"), wxITEM_NORMAL);
    modMenu->Append(menuModScan);

    wxMenuItem* menuModInstall = new wxMenuItem(modMenu, idMenuInstall, wxString(wxT("&Install")), wxT("Install a mod from file"), wxITEM_NORMAL);
    modMenu->Append(menuModInstall);

    wxMenuItem* menuModActivate = new wxMenuItem(modMenu, idMenuActivate, wxString(wxT("&Activate/Deactivate")) + wxT('\t') + wxT("F8"), wxT("Activate/Deactivate currently selected mod"), wxITEM_NORMAL);
    modMenu->Append(menuModActivate);
    mbar->Append(modMenu, wxT("&Mods"));

    // Help Menu
    wxMenu* helpMenu;
    helpMenu = new wxMenu();
    wxMenuItem* menuHelpAbout = new wxMenuItem(helpMenu, idMenuAbout, wxString(wxT("&About")) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL);
    helpMenu->Append(menuHelpAbout);
    mbar->Append(helpMenu, wxT("&Help"));
    this->SetMenuBar(mbar);

    // Make Toolbar
    toolbar = CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL | wxTB_NOICONS | wxTB_TEXT, -1, _("Toolobar"));
    toolbar->AddTool(idMenuScan, _("Scan"), NULL, wxT("Scan for new mods"), wxITEM_NORMAL);
    toolbar->AddTool(idMenuInstall, _("Install"), NULL, wxT("Install a mod from file"), wxITEM_NORMAL);
    toolbar->AddTool(idMenuActivate, _("Activate/Deactivate"), NULL, wxT("Active or Deactivate selected mod"), wxITEM_NORMAL);
    toolbar->Realize();
    Connect(idMenuScan, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SS2MMFrame::OnScan));
    Connect(idMenuInstall, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SS2MMFrame::OnInstall));
    Connect(idMenuActivate, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SS2MMFrame::OnActivate));
    toolbar->Show(true);

    // Status bar (shows current status and version)
    statusBar = this->CreateStatusBar(2, wxST_SIZEGRIP, wxID_ANY);
    statusBar->SetStatusText(status, 0);
    statusBar->SetStatusText(version, 1);
    int widths[2] = {-1, 100};
    this->SetStatusWidths(2, widths);

    // Main Panels
    wxPanel* panel = new wxPanel(this, -1);
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* infoBox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* modBox = new wxBoxSizer(wxVERTICAL);

    // Available/Inactive Mod List
    wxStaticText* inactiveText = new wxStaticText(panel, wxID_ANY, wxT("Available Mods:"));
    wxBoxSizer* inactiveBox = new wxBoxSizer(wxHORIZONTAL);
    inactiveList = new wxListView(panel, wxID_ANY, wxPoint(-1, -1), wxSize(-1, -1), wxLC_SORT_ASCENDING | wxLC_LIST, wxDefaultValidator, _("InactiveModList"));
    inactiveBox->Add(inactiveList, 2, wxEXPAND | wxALL, 10);
    Connect(inactiveList->GetId(), wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(SS2MMFrame::OnInactiveDragInit));

    inactiveList->Show(true);

    // Active Mod List
    wxStaticText* activeText = new wxStaticText(panel, wxID_ANY, wxT("Active Mods:"));
    wxBoxSizer* activeBox = new wxBoxSizer(wxHORIZONTAL);
    activeList = new wxListView(panel, wxID_ANY, wxPoint(-1, -1), wxSize(-1, -1), wxLC_SORT_ASCENDING | wxLC_LIST, wxDefaultValidator, _("InactiveModList"));
    activeBox->Add(activeList, 2, wxEXPAND | wxALL, 10);
    Connect(activeList->GetId(), wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(SS2MMFrame::OnActiveDragInit));

    activeList->Show(true);

    // Mod Info Panel
    wxStaticText* infoText = new wxStaticText(panel, wxID_ANY, wxT("Mod Info:"));
    infoBox->Add(infoText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);
    modInfo = new wxStaticText(panel, wxID_ANY, wxT("Select a mod"));
    modInfo->Wrap(200);
    infoBox->Add(modInfo, 0, wxTOP | wxRIGHT, 10);

    // Add all of the various pieces into their proper parents
    modBox->Add(inactiveText, 0, wxLEFT, 10);
    modBox->Add(inactiveBox, 2, wxEXPAND | wxLEFT | wxRIGHT);
    modBox->Add(activeText, 0, wxLEFT, 10);
    modBox->Add(activeBox, 2, wxEXPAND | wxALL);
    hbox->Add(modBox, 2, wxEXPAND | wxALL | wxALIGN_LEFT);
    hbox->Add(infoBox);
    panel->SetSizer(hbox);
    Center();
}

SS2MMFrame::~SS2MMFrame()
{
}

void SS2MMFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void SS2MMFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void SS2MMFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = _("System Shock 2 Mod Manager v0.1\n\nAuthor: Ryan <zeebok> Kornheisl");
    wxMessageBox(msg, _("About"));
}

void SS2MMFrame::OnScan(wxCommandEvent& event)
{
    status = _("Scanning for mods");
    inactiveList->InsertItem(0, _("Test Mod"));
    status = _("Ready");
}

void SS2MMFrame::OnInstall(wxCommandEvent& event)
{
    status = _("Installing mod");

    status = _("Ready");
}

void SS2MMFrame::OnActivate(wxCommandEvent& event)
{

}

void SS2MMFrame::OnInactiveDragInit(wxListEvent& event)
{
    SS2MMDropTarget* activeDropTarget = new SS2MMDropTarget(activeList, inactiveList);
    activeList->SetDropTarget(activeDropTarget);
    wxString mod = inactiveList->GetItemText(event.GetIndex());
    wxTextDataObject modTDO(mod);
    wxDropSource inactiveTDS(modTDO, inactiveList);
    inactiveTDS.DoDragDrop(wxDrag_DefaultMove);
}

void SS2MMFrame::OnActiveDragInit(wxListEvent& event)
{
    SS2MMDropTarget* inactiveDropTarget = new SS2MMDropTarget(inactiveList, activeList);
    inactiveList->SetDropTarget(inactiveDropTarget);
    wxString mod = activeList->GetItemText(event.GetIndex());
    wxTextDataObject modTDO(mod);
    wxDropSource activeTDS(modTDO, activeList);
    activeTDS.DoDragDrop(wxDrag_DefaultMove);
}
