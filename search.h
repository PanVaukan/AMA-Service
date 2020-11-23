#ifndef SEARCH_H
#define SEARCH_H

#include <config.h>
#include <callinformation.h>
#include <connector.h>
#include <logger.h>
#include <searchparameters.h>

#include <QVector>

class Search
{
public:
    Search();
    QVector<CallInformation> selectCallRecordsInMySQLServer(Connector currentDbConnection, SearchParameters searchParameters, Config config);
};

#endif // SEARCH_H
