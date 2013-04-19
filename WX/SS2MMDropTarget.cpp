/***************************************************************
 * Name:      SS2MMDropTarget.cpp
 * Purpose:   Code for Drop Target Class
 * Author:    Ryan Kornheisl (rkornheisl@gmail.com)
 * Created:   2013-02-14
 * Copyright: Ryan Kornheisl (www.shard-tech.com)
 * License:   GPLv3
 **************************************************************/

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

    source->DeleteItem(sourceItemIndex);
    owner->InsertItem(0, data);

    return true;
}
