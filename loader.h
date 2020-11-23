#ifndef LOADER_H
#define LOADER_H

#include <config.h>
#include <connector.h>
#include <file.h>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QVector>

class Loader
{
public:
    Loader();
    bool dumpDataFromDataBase(QApplication *application, Config config, QString dateTableName);
    bool loadDataInDataBaseUsingDump(QApplication *application, Config config, QString dateTableName);
    bool loadDataInDataBaseUsingCSV(Config config, Connector connection, QString csvFileName);
    bool loadArrayDataInDB(Config config, Connector connection, QVector<QString> csvFileNames);

};

#endif // LOADER_H
