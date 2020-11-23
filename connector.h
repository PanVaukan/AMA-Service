#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <config.h>
#include <logger.h>
#include <tableinfo.h>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QMap>

#include <QFile>
#include <QTextStream>

class Connector
{
private:
    QSqlDatabase dbEWSD;
    QSqlDatabase dbConnection;
    QSqlDatabase dbSecondaryEWSDConn;
    QSqlDatabase dbAPUS;
    bool isConnectedToDB;
    QString dbDriver;
    QString dbHost;
    QString dbPort;
    QString dbUser;
    QString dbPwd;
    QString dbName;
    QString dbHostAPUS;
    QString dbPortAPUS;
    QString dbUserAPUS;
    QString dbPwdAPUS;
    QString dbNameAPUS;
    QString dbNameForImportData;
    quint32 mysqlAPUS_Thread_ID;
    quint32 mysqlEWSD_Thread_ID;
public:
    Connector();
    void initConnection(Config paramsForConnectionString);
    bool connectToMySQLServer(Config paramsForConnectionString);
    bool SecondaryConnectToMySQLServer(QString switchMySQLDriver);
    bool ReconnectToMySQLServer(Config paramsForConnectionString);
    QSqlDatabase getEWSDConnection();
    QSqlDatabase getAPUSConnection();
    void openConnections();
    quint32 getMySQL_APUS_Thread_ID();
    void setMySQL_APUS_Thread_ID(uint id);
    quint32 getMySQL_EWSD_Thread_ID();
    void setMySQL_EWSD_Thread_ID(uint id);
    QString getDbNameFoImportData();
    void setDbNameForImportData(QString dbNameForImport);
    QString getDbAPUSName();
    QString getDbEWSDName();
    bool createGeneralTablesInDatabase(Config config);
    QMap<QString,TableInfo> getInformationShema(int minDayOffset, int maxDayOffset, QSqlDatabase db);

    bool RunMySQLQuery(Config paramsForConnectionString, QString queryString, bool isTransactionalQuery, QSqlQuery &queryForRun);

    void closeConnections();

};

#endif // CONNECTOR_H
