/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 athre0z
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Utils.hpp"
#include "Settings.hpp"

#include "Config.hpp"
#include "Core.hpp"

#include "idaskins.hpp"

#include <QtGui>
#include <QDockWidget>
#include <functional>

#ifdef BUILD_IDA
#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <diskio.hpp>
#endif // BUILD_IDA

// ============================================================================

/**
 * @brief   Initialization callback for IDA.
 * @return  A @c PLUGIN_ constant from loader.hpp.
 */
int idaapi init()
{
    if (!is_idaq()) return PLUGIN_SKIP;
    msg("[" PLUGIN_NAME "] " PLUGIN_TEXTUAL_VERSION " by athre0z loaded!\n");

    try
    {
        Core::instance();
    }
    catch (const std::runtime_error &e)
    {
        msg("[" PLUGIN_NAME "][ERROR] Cannot load plugin: %s\n", e.what());
        return PLUGIN_UNL;
    }

    return PLUGIN_KEEP;
}

/**
 * @brief   Run callback for IDA.
 */
void idaapi run(int /*arg*/)
{
    Core::instance().runPlugin();
}

/**
 * @brief   Shutdown callback for IDA.
 */
void idaapi term()
{
    if (Core::isInstantiated())
        Core::freeInstance();
}

#ifdef BUILD_IDA
plugin_t PLUGIN =
{
    IDP_INTERFACE_VERSION,
    PLUGIN_FIX,
    &init,
    &term,
    &run,
    "Advanced IDA skinning",
    "Plugin providing advanced skinning features using Qt stylesheets.",
    PLUGIN_NAME ": Settings",
    "Ctrl-Shift-S"
};
#endif // BUILD_IDA

#ifndef BUILD_IDA
int g_MenuHandle;
int g_PluginHandle;

void MenuEntryCallback(CBTYPE Type, PLUG_CB_MENUENTRY *Info)
{
    Q_UNUSED(Type);

    switch (Info->hEntry)
    {
        case 0:
            run(Info->hEntry);
            break;
    }
}

DLL_EXPORT bool pluginit(PLUG_INITSTRUCT *InitStruct)
{
    InitStruct->pluginVersion	= PLUGIN_VERSION;
    InitStruct->sdkVersion		= PLUG_SDKVERSION;
    g_PluginHandle				= InitStruct->pluginHandle;
    strcpy_s(InitStruct->pluginName, PLUGIN_NAME);

    // Add any of the callbacks
    _plugin_registercallback(g_PluginHandle, CB_MENUENTRY, (CBPLUGIN)MenuEntryCallback);
    return true;
}

DLL_EXPORT bool plugstop()
{
    // Clear the menu
    _plugin_menuclear(g_MenuHandle);

    // Remove callbacks
    _plugin_unregistercallback(g_PluginHandle, CB_MENUENTRY);

    // Free resources
    term();
    return true;
}

DLL_EXPORT void plugsetup(PLUG_SETUPSTRUCT *SetupStruct)
{
    g_MenuHandle = SetupStruct->hMenu;

    // Initialize the menu
    _plugin_menuaddentry(g_MenuHandle, 0, "&Settings");

    // Plugin initialization
    init();
}
#endif // ndef BUILD_IDA

// ============================================================================
