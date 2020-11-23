#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QStringList>
#include <QDate>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

class File
{
public:
    File();
    //*********************************************
    QString getAbsoluteATS20AMAFilePathByDateFileName(QString,QString);
    //*********************************************
    quint32 getFileNameLastHourModifiedByDate(QString);
    //*********************************************
    QDate getLastDateModifiedOfAMAFile(QString);
    //**************************************************
    QString getStringDateOfCreateOfAMAFile(QString, QString);
    //**************************************************
    QString getLastStringDateModifiedOfAMAFile(QString, QString);
    //**************************************************
    QString getFileNameFromFullPathToAMAFile(QString);
    //**************************************************
    QString getBaseNameFromFullPathToAMAFile(QString);
    //**************************************************
    QString getDateFileNameByFullPathAMAFile(QString,QString);
    //**************************************************
    QString getLetterFromBaseName(QString);
    //**************************************************
    int getCodeOfLetter(QString);
    //**************************************************
    QString getNextLetterByCodeLetter(int);
    //**************************************************
    int getIndexPositionSubstr(QString,QString,int);
    //**************************************************
    int countSubDirsByAbsolutePath(QString);
    //**************************************************
    bool isRootAMAStationDir(QString);
    //**************************************************
    bool isAMAFile(QString);
    //**************************************************
    bool isBrestATS(QString);
    //**************************************************
    bool isATSFolder(QString,QString);
    //**************************************************
    QString getPathBySubDir(QString,QString);
    //**************************************************
    QString getAtsName(QString);
    //**************************************************
    QString getExistsFullFileNameByPath(QString,QString);
    //**************************************************
    QString getFullFileNameByPath(QString,QString);
};

#endif // FILE_H
