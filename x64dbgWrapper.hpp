#ifndef X64DBGWRAPPER_H
#define X64DBGWRAPPER_H
#ifndef BUILD_IDA

//
// WINDOWS
//
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

//
// X64DBG
//
#include "pluginsdk/_plugins.h"
#include "pluginsdk/bridgemain.h"
#include "pluginsdk/_dbgfunctions.h"

//
// IDA types
//
#define idaapi
#define PLUGIN_SKIP 0
#define PLUGIN_KEEP 0
#define PLUGIN_UNL 0
#define IWID_ALL 0

//
// IDA functions
//
#define msg _plugin_logprintf

static void request_refresh(int)
{
    GuiUpdateAllViews();
}

static const char *idadir(const char *Subdir)
{
    static char tempBuffer[MAX_PATH];

    if (GetCurrentDirectoryA(ARRAYSIZE(tempBuffer), tempBuffer) == 0)
        return nullptr;

    // Append the subdirectory
    if (Subdir)
    {
        strcat_s(tempBuffer, "\\");
        strcat_s(tempBuffer, Subdir);
    }

    return tempBuffer;
}

static bool is_idaq()
{
    return true;
}

#endif // ndef BUILD_IDA
#endif // X64DBGWRAPPER_H
