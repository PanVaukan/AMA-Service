#ifndef TASK_H
#define TASK_H

#include "callinformation.h"
#include "callinformationcollector.h"
#include "config.h"
#include "connector.h"
#include "datagenerator.h"
#include "filewriter.h"
#include "loader.h"
#include "search.h"
#include "searchparameters.h"
#include "searchresult.h"
#include "xmlreader.h"

#include <QApplication>
#include <QString>
#include <QVector>
#include <QMap>
#include <QMultiMap>

class Task{
private:
    QVector<QString> tableNamesForImport;
    QVector<QString> tableNamesForAddIndex;
    QVector<QString> tableNamesForSearch;
    QVector<int> arrayOfDayOffsetForImportTable;
    QVector<int> arrayOfDayOffsetForAddIndex;
    QVector<int> arrayOfDayOffsetForSearch;
public:
    Task();
    void resetArraysForImport();
    void resetArraysForAddIndex();
    void resetArraysForSearch();
    QVector<QString> getTableNamesForImport();
    QVector<QString> getTableNamesForAddIndex();
    QVector<QString> getTableNamesForSearch();
    void setTableNamesForImport(QVector<QString> tableNames);
    void setTableNamesForAddIndex(QVector<QString> tableNames);
    void setTableNamesForSearch(QVector<QString> tableNames);
    void preparationTableNamesForImportInEWSD_db(int minDayOffset, int maxDayOffset);
    void preparationTableNamesForAddIndex(int minDayOffset, int maxDayOffset, QString dbName);
    void preparationTableNamesForSearchInDB(int minDayOffset, int maxDayOffset);
    QVector<int> getArrayOfDayOffsetForImportTable();
    QVector<int> getArrayOfDayOffsetForAddIndex();
    QVector<int> getArrayOfDayOffsetForSearch();
    void setArrayOfDateOffsetForImportTable();
    void setArrayOfDateOffsetForAddIndex();
    void setArrayOfDateOffsetForSearch();
    int loadTablesFromDataBase(QApplication *application, int minDayOffset, int maxDayOffset);
    int loadTablesInDataBase(QApplication *application, int minDayOffset, int maxDayOffset);
    int manualTableSynchronization(QApplication *application);
    int addGeneralKeysInEWSDBigTable();
    int addGeneralKeysAfterImportTablesInApusDatabase();
    int generateCallInformationInDB(int minDayOffset, int maxDayOffset, uint allowedCountRecords);
    int generateCallInformationForDB(QString databaseName);
    int searchInformationInDB();
};

#endif // TASK_H
