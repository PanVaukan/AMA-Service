#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <config.h>

#include <QString>
#include <QVector>
#include <QStringList>
#include <QMap>
#include <QDate>
#include <QDateTime>

class SearchParameters
{
private:
    QString MySQLServerHostName;
    bool selectAllData;
    bool answer;
    QString phoneNumberA;
    QString phoneNumberB;
    quint32 callDuration;
    quint32 startSearchDateTime;
    quint32 endSearchDateTime;

    QMap<QString, QStringList> searchParametersForMySQLquery;
    QMap<QString, QStringList>::iterator searchParamsMapCurrentIterator;

    QVector<QString> apusDBTables;
    QVector<QString> ewsdDBTables;

    QVector<QString> readySQLQuerysForSearchInEWSDdb;
    QVector<QString> readySQLQuerysForSearchInAPUSdb;

public:
    SearchParameters();
    QString getMySQLServerHostName();
    void setMySQLServerHostName(QString host);
    bool getSelectAllData();
    void setSelectAllData(bool selectAll);
    bool getAnswer();
    void setAnswer(uint answer_);
    quint32 getCallDuration();
    void setCallDuration(uint callDuration_);
    QString getPhoneNumberA();
    void setPhoneNumberA(QString phoneNumberA_);
    QString getPhoneNumberB();
    void setPhoneNumberB(QString phoneNumberB_);
    quint32 getStartSearchDateTime();
    void setStartSearchDateTime(uint startSearchDateTime_);
    quint32 getEndSearchDateTime();
    void setEndSearchDateTime(uint endSearchDateTime_);
    void addNewSearchParameter(QString key, QString value);
    QMap<QString, QStringList> getSearchParametersForMySQLquery();
    QStringList getSearchValuesByKey(QString key);
    QString getSearchValueByKey(QString key, int item);
    QString addSearchParametersToSQLQuery(QString MySQL_Server);
    void addSQLQuerysForSearchInAPUSdb(QString query);
    void addSQLQuerysForSearchInEWSDdb(QString query);
    qint64 getDayOffsetByDate(QString dateStr,QString format);
    qint64 getDayOffsetByDateTime(uint unixtime);
    bool buildSQLQueryForSearch(QVector<int> arrayOfDayOffsetForSearch);
    bool buildSQLQueryForLoadDataInDB(Config config);
    uint getCountReadySQLQuerys();
    QVector<QString> getReadySQLQuerysForSearchInAPUSdb();
    QVector<QString> getReadySQLQuerysForSearchInEWSDdb();

};

#endif // SEARCHPARAMETERS_H
