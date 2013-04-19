/***************************************************************
 * Name:      SS2MMApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Ryan Kornheisl (rkornheisl@gmail.com)
 * Created:   2013-02-14
 * Copyright: Ryan Kornheisl (www.shard-tech.com)
 * License:   GPLv3
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "SS2MMApp.h"
#include "SS2MMMain.h"

IMPLEMENT_APP(SS2MMApp);

bool SS2MMApp::OnInit()
{
    SS2MMFrame* frame = new SS2MMFrame(0L);

    frame->Show();

    return true;
}
