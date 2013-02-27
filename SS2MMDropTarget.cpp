#include "SS2MMDropTarget.h"

SS2MMDropTarget::SS2MMDropTarget(wxListCtrl* owner, wxListCtrl* source)
{
    this->owner = owner;
    this->source = source;
}

bool SS2MMDropTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{

    long sourceItemIndex = source->FindItem(-1, data);
    if(sourceItemIndex == wxNOT_FOUND)
    {
        return false;
    }

    owner->InsertItem(0, data);
    source->DeleteItem(sourceItemIndex);

    return true;
}
