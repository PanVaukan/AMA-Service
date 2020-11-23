#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T11:46:46
#
#-------------------------------------------------

QT       += core gui sql xml widgets

CODECFORTR = UTF-8

CODECFORSRC = UTF-8

DEFINES += QT_MESSAGELOGCONTEXT

TARGET = AMA-Search
TEMPLATE = app


SOURCES += main.cpp\
    amasearch.cpp \
    config.cpp \
    xmlreader.cpp \
    callinformation.cpp \
    callinformationcollector.cpp \
    datagenerator.cpp \
    connector.cpp \
    logger.cpp \
    sqlgenerator.cpp \
    searchparameters.cpp \
    search.cpp \
    searchresult.cpp \
    converter.cpp \
    filewriter.cpp \
    loader.cpp \
    file.cpp \
    randomgenerator.cpp \
    randomcpp11generator.cpp \
    loggingcategories.cpp \
    tableinfo.cpp \
    sheduler.cpp \
    task.cpp

HEADERS  += amasearch.h \
    config.h \
    xmlreader.h \
    callinformation.h \
    callinformationcollector.h \
    datagenerator.h \
    connector.h \
    logger.h \
    sqlgenerator.h \
    searchparameters.h \
    search.h \
    searchresult.h \
    converter.h \
    filewriter.h \
    loader.h \
    file.h \
    randomgenerator.h \
    randomcpp11generator.h \
    loggingcategories.h \
    tableinfo.h \
    sheduler.h \
    task.h

FORMS    += amasearch.ui
