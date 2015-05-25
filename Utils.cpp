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

#ifdef BUILD_IDA
#include <ida.hpp>
#include <diskio.hpp>
#endif // BUILD_IDA

namespace Utils
{

QDir getThemesDir()
{
    return QDir(QString(idadir(nullptr)) + "/skin");
}

QString getThemesPath()
{
    return getThemesDir().absolutePath();
}

bool getCurrentThemeDir(QDir &dir)
{
    Settings settings;
    QVariant themeDirSetting = settings.value(Settings::kSelectedThemeDir);
    if (themeDirSetting.isNull()) return false;
    if (!themeDirSetting.canConvert<QString>())
    {
        settings.remove(Settings::kSelectedThemeDir);
        return false;
    }

    QDir tmp = getThemesPath() + "/" + themeDirSetting.toString();
    if (tmp.exists())
    {
        dir = tmp;
        return true;
    }
    
    return false;
}

}