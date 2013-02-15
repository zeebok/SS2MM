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
#include "minizip/unzip.h" // contrib in zLib 1.2.7

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


    statusBar = this->CreateStatusBar(2, wxST_SIZEGRIP, wxID_ANY);
    statusBar->SetStatusText(status, 0);
    statusBar->SetStatusText(version, 1);
    int widths[2] = {-1, 100};
    this->SetStatusWidths(2, widths);
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

}

void SS2MMFrame::OnInstall(wxCommandEvent& event)
{

}

void SS2MMFrame::OnActivate(wxCommandEvent& event)
{

}
