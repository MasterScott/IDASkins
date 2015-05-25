QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += BUILD_LIB
TEMPLATE = lib

HEADERS += \
    Config.hpp \
    Core.hpp \
    IdaFontConfig.hpp \
    Settings.hpp \
    ThemeManifest.hpp \
    ThemeSelector.hpp \
    Utils.hpp \
    idaskins.h \
    idaskins.hpp \
    x64dbgWrapper.hpp

SOURCES += \
    Core.cpp \
    IdaFontConfig.cpp \
    idaskins.cpp \
    Settings.cpp \
    ThemeManifest.cpp \
    ThemeSelector.cpp \
    Utils.cpp

FORMS += \
    ui/ThemeEditorDialog.ui \
    ui/ThemeSelector.ui

!contains(QMAKE_HOST.arch, x86_64) {
    #message("x86 build")
    LIBS += -L"$$PWD/pluginsdk/" -lx32bridge
    LIBS += -L"$$PWD/pluginsdk/" -lx32dbg
    ## Windows x86 (32bit) specific build here
} else {
    #message("x86_64 build")
    LIBS += -L"$$PWD/pluginsdk/" -lx64bridge
    LIBS += -L"$$PWD/pluginsdk/" -lx64dbg
    ## Windows x64 (64bit) specific build here
}
