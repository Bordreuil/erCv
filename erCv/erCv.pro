#-------------------------------------------------
#
# Project created by QtCreator 2013-06-17T15:37:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = erCv
TEMPLATE = lib

DEFINES += ERCV_LIBRARY

SOURCES += ercv.cpp

HEADERS += ercv.h\
        erCv_global.h \
    ../include/erCv/documentation.hpp \
    ../include/erCv/erCalibration.hpp \
    ../include/erCv/erCv.hpp \
    ../include/erCv/erCvAnalysis.hpp \
    ../include/erCv/erCvBase.hpp \
    ../include/erCv/erCvExtract.hpp \
    ../include/erCv/erCvFilters.hpp \
    ../include/erCv/erCvFiltersParams.hpp \
    ../include/erCv/erCvSegmentation.hpp \
    ../include/erCv/erCvSegmentationParams.hpp \
    ../include/erCv/erCvToCgal.hpp \
    ../include/erCv/erCvTools.hpp

symbian {
    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0A87382
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = erCv.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}
