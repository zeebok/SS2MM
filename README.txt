System Shock 2 Mod Manager
--------------------------

Started with WxWidgets, but decided to go with Qt after comparing ease of use and documentation quality.

Should do the following:

* Find mods available, or "installed", by scanning the MODDIR specified in SS2MM.h
* Install new mods from a zip file; unzips the mod to MODDIR and adds to list of available mods
* Activate and Deactivate mods; involves adding/removing the mod's directory from the mod_paths list within cam.cfg

This code is released under the GPLv3
