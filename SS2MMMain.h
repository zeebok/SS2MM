/***************************************************************
 * Name:      SS2MMMain.h
 * Purpose:   Defines Application Frame
 * Author:    Ryan Kornheisl (rkornheisl@gmail.com)
 * Created:   2013-02-14
 * Copyright: Ryan Kornheisl (www.shard-tech.com)
 * License:   GPLv3
 **************************************************************/

#ifndef SS2MMMAIN_H
#define SS2MMMAIN_H

// Define WX_GCH in order to support precompiled headers with GCC compiler.
// You have to create the header "wx_pch.h" and include all files needed
// for compile your gui inside it.
// Then, compile it and place the file "wx_pch.h.gch" into the same
// directory that "wx_pch.h".
#ifdef WX_GCH
#include <wx_pch.h>
#else
#include <wx/wx.h>
#endif


#include "SS2MMApp.h"
#include "SS2MMDropTarget.h"

enum
{
  idMenuQuit = 1,
  idMenuAbout,
  idMenuScan,
  idMenuInstall,
  idMenuActivate
};

class SS2MMFrame: public wxFrame
{
    DECLARE_EVENT_TABLE()
    public:
        SS2MMFrame(wxWindow* parent, int id = wxID_ANY, wxString title = wxT("System Shock 2 Mod Manager"), wxPoint pos = wxDefaultPosition, wxSize size = wxSize(800, 600), int style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
        ~SS2MMFrame();
    private:
        wxMenuBar* mbar;
        wxStatusBar* statusBar;
        wxToolBar* toolbar;
        wxListView* inactiveList;
        wxListView* activeList;
        wxStaticText* modInfo;
        wxString status;
        const wxString version;

        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnScan(wxCommandEvent& event);
        void OnInstall(wxCommandEvent& event);
        void OnActivate(wxCommandEvent& event);

        void OnInactiveDragInit(wxListEvent& event);
        void OnActiveDragInit(wxListEvent& event);
};

#endif // SS2MMMAIN_H
