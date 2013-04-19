/***************************************************************
 * Name:      SS2MMApp.cpp
 * Purpose:   GUI application to install and manage mods for SS2
 * Author:    Ryan Kornheisl (rkornheisl@gmail.com)
 * Created:   2013-02-14
 * Copyright: Ryan Kornheisl (www.shard-tech.com)
 * License:   GPLv3
 **************************************************************/

#ifndef SS2MMAPP_H
#define SS2MMAPP_H

#include <wx/app.h>

class SS2MMApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // SS2MMAPP_H
