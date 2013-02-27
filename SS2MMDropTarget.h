#ifndef SS2MMDROPTARGET_H
#define SS2MMDROPTARGET_H

#include <wx/listctrl.h>
#include <wx/dnd.h>

class SS2MMDropTarget : public wxTextDropTarget
{
    public:
        SS2MMDropTarget(wxListCtrl* owner, wxListCtrl* source);

        bool OnDropText(wxCoord x, wxCoord y, const wxString& data);
    protected:
    private:
        wxListCtrl* owner;
        wxListCtrl* source;
};

#endif // SS2MMDROPTARGET_H
