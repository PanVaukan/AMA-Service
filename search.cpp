#include "search.h"

Search::Search()
{
}

QVector<CallInformation> Search::selectCallRecordsInMySQLServer(Connector currentDbConnection, SearchParameters searchParameters, Config config){

    QVector<CallInformation> searchResults;

//  int countQuerys = searchParameters.getCountReadySQLQuerys();

    Logger logger;
    QString startSearchAt = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    logger.writeLog(startSearchAt,"");

    if ( searchParameters.getMySQLServerHostName() == "APUS-AND-EWSD" || searchParameters.getMySQLServerHostName() == "APUS" ) {

    QSqlQuery *queryForSearchInAPUSServer = new QSqlQuery(currentDbConnection.getEWSDConnection());
    QVector<QString> sqlAPUSQuerys = searchParameters.getReadySQLQuerysForSearchInAPUSdb();
    QVector<QString>::iterator iterAPUS = sqlAPUSQuerys.begin();

    while ( iterAPUS != sqlAPUSQuerys.end() ){
        QString currentSQLQuery = *iterAPUS;

        if ( !(queryForSearchInAPUSServer->exec(currentSQLQuery))){

               QString strError = queryForSearchInAPUSServer->lastError().text();
               Logger logger;
               logger.writeLog(strError,"");
               logger.writeLog(currentSQLQuery,"");

        }
        else {  // if ( queryForSearchInAPUSServer->size() > 0 )
                while (queryForSearchInAPUSServer->next()){

                    CallInformation callInfo;
                    QString phoneNumberA = queryForSearchInAPUSServer->value(0).toString();
                    QString phoneNumberB = queryForSearchInAPUSServer->value(1).toString();
                    quint8 answer = queryForSearchInAPUSServer->value(2).toUInt();
                    QString dateTimeStr = queryForSearchInAPUSServer->value(3).toString();
                    uint datetime_unix = QDateTime(QDateTime::fromString(dateTimeStr,Qt::ISODate)).toTime_t();
                    quint32 callDuration = queryForSearchInAPUSServer->value(4).toInt();
                    callInfo.setAbonFields(phoneNumberA,phoneNumberB,answer,callDuration,datetime_unix);
                    searchResults.push_back(callInfo);

                }

        }

        ++iterAPUS;
    }

        delete queryForSearchInAPUSServer;
}

    if ( searchParameters.getMySQLServerHostName() == "APUS-AND-EWSD" || searchParameters.getMySQLServerHostName() == "EWSD" ) {

    QSqlQuery *queryForSearchInEWSDServer = new QSqlQuery(currentDbConnection.getEWSDConnection());
    QVector<QString> sqlEWSDQuerys = searchParameters.getReadySQLQuerysForSearchInEWSDdb();
    QVector<QString>::iterator iterEWSD = sqlEWSDQuerys.begin();

    while ( iterEWSD != sqlEWSDQuerys.end() ){
        QString currentSQLQuery = *iterEWSD;

        if ( !(queryForSearchInEWSDServer->exec(currentSQLQuery))){

               QString strError = queryForSearchInEWSDServer->lastError().text();
               Logger logger;
               logger.writeLog(strError,"");
               logger.writeLog(currentSQLQuery,"");

        }
        else {  // if ( queryForSearchInEWSDServer->size() > 0 )
                while (queryForSearchInEWSDServer->next()){

                    CallInformation callInfo;
                    QString phoneNumberA = queryForSearchInEWSDServer->value(0).toString();
                    QString phoneNumberB = queryForSearchInEWSDServer->value(1).toString();
                    quint8 answer = queryForSearchInEWSDServer->value(2).toUInt();
                    //QString dateTimeStr = queryForSearchInEWSDServer->value(3).toString();
                    //uint datetime_unix = QDateTime(QDateTime::fromString(dateTimeStr,Qt::ISODate)).toTime_t();
                    uint datetime_unix = queryForSearchInEWSDServer->value(3).toUInt();
                    quint32 callDuration = queryForSearchInEWSDServer->value(4).toInt();
                    callInfo.setAbonFields(phoneNumberA,phoneNumberB,answer,callDuration,datetime_unix);
                    searchResults.push_back(callInfo);

                }
        }

        ++iterEWSD;
    }

        delete queryForSearchInEWSDServer;
}

//      currentDbConnection.RunMySQLQuery()

    QString endSearchAt = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");
    logger.writeLog(endSearchAt,"");

    return searchResults;
}

