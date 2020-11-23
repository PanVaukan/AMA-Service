#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <callinformation.h>
#include <QMultiMap>
#include <QList>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>

class FileWriter
{
public:
    FileWriter();
    bool writeCSVFile(QString fileName, QVector<CallInformation> callInfoCollectionData, bool isRealData);
    bool writeCSVFilesForLoadDataInMySQLServer(QString directory, QMultiMap<QDate,CallInformation> callInfoCollectionDataWithDates,bool isRealData);


};

#endif // FILEWRITER_H
