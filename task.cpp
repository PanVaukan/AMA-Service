#include "task.h"

Task::Task(){

}

void Task::resetArraysForImport(){

    tableNamesForImport.clear();
    arrayOfDayOffsetForImportTable.clear();

}

void Task::resetArraysForAddIndex(){

    tableNamesForAddIndex.clear();
    arrayOfDayOffsetForAddIndex.clear();

}

void Task::resetArraysForSearch(){

    tableNamesForSearch.clear();
    arrayOfDayOffsetForSearch.clear();

}

QVector<QString> Task::getTableNamesForImport(){
    return tableNamesForImport;
}

QVector<QString> Task::getTableNamesForAddIndex(){
    return tableNamesForAddIndex;
}

QVector<QString> Task::getTableNamesForSearch(){
    return tableNamesForSearch;
}

void Task::setTableNamesForImport(QVector<QString> tableNames){

    this->tableNamesForImport = tableNames;

}

void Task::setTableNamesForAddIndex(QVector<QString> tableNames){

    this->tableNamesForAddIndex = tableNames;

}

void Task::setTableNamesForSearch(QVector<QString> tableNames){

    this->tableNamesForSearch = tableNames;

}

void Task::preparationTableNamesForImportInEWSD_db(int minDayOffset, int maxDayOffset){

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Connector dbConnection;
    dbConnection.initConnection(config);

    bool connectionToMySQLServerIsOK = false;
    while (!connectionToMySQLServerIsOK){
            connectionToMySQLServerIsOK = dbConnection.connectToMySQLServer(config);
    }

    QMap<QString,TableInfo> fullTableInfoFromAPUSServer;
    QMap<QString,TableInfo> fullTableInfoFromEWSDServer;

    QMap<QString,TableInfo>::iterator fullTableInfoIterator;

    QMap<QString,quint64> shortTableInfoFromAPUSServer;
    QMap<QString,quint64> shortTableInfoFromEWSDServer;

    QMap<QString,quint64>::iterator shortTableInfoAPUSIterator;
    QMap<QString,quint64>::iterator shortTableInfoEWSDIterator;

    QVector<QString> tableNamesForImportInDB;

    fullTableInfoFromAPUSServer = dbConnection.getInformationShema(minDayOffset,maxDayOffset,dbConnection.getAPUSConnection());
    fullTableInfoFromEWSDServer = dbConnection.getInformationShema(minDayOffset,maxDayOffset,dbConnection.getEWSDConnection());

    fullTableInfoIterator = fullTableInfoFromAPUSServer.begin();

    while ( fullTableInfoIterator != fullTableInfoFromAPUSServer.end() ){
            TableInfo tableInfo = *fullTableInfoIterator;
            shortTableInfoFromAPUSServer.insert(tableInfo.getTableName(),tableInfo.getTableRows());
            ++fullTableInfoIterator;
    }

    fullTableInfoIterator = fullTableInfoFromEWSDServer.begin();

    while ( fullTableInfoIterator != fullTableInfoFromEWSDServer.end() ) {
            TableInfo tableInfo = *fullTableInfoIterator;
            shortTableInfoFromEWSDServer.insert(tableInfo.getTableName(),tableInfo.getTableRows());
            ++fullTableInfoIterator;
    }

    shortTableInfoAPUSIterator = shortTableInfoFromAPUSServer.begin();
    shortTableInfoEWSDIterator = shortTableInfoFromEWSDServer.begin();

    while ( shortTableInfoAPUSIterator != shortTableInfoFromAPUSServer.end() ) {

            if ( !(shortTableInfoFromEWSDServer.contains(shortTableInfoAPUSIterator.key()))){
                    tableNamesForImportInDB.push_back(shortTableInfoAPUSIterator.key());
            } else {

                    quint64 coutRowsFromApusTable = *shortTableInfoAPUSIterator;

                    shortTableInfoEWSDIterator = shortTableInfoFromEWSDServer.find(shortTableInfoAPUSIterator.key());

                    quint64 coutRowsFromEWSDTable  = *shortTableInfoEWSDIterator;

                    if ( coutRowsFromApusTable != coutRowsFromEWSDTable ){

                        tableNamesForImportInDB.push_back(shortTableInfoAPUSIterator.key());

                    }

            }

            ++shortTableInfoAPUSIterator;
    }

    this->setTableNamesForImport(tableNamesForImportInDB);

    this->setArrayOfDateOffsetForImportTable();

}


void Task::preparationTableNamesForAddIndex(int minDayOffset, int maxDayOffset, QString dbName){

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Connector dbConnection;
    dbConnection.initConnection(config);

    bool connectionToMySQLServerIsOK = false;
    while (!connectionToMySQLServerIsOK){
            connectionToMySQLServerIsOK = dbConnection.connectToMySQLServer(config);
    }

    QMap<QString,TableInfo> fullTableInfoFromEWSDServerDB;

    QMap<QString,TableInfo>::iterator fullTableInfoIterator;

    QMap<QString,quint64> shortTableInfoFromEWSDServerDB;

    QMap<QString,quint64>::iterator shortTableInfoIterator;

    QVector<QString> tableNamesForAddIndex;

    if ( dbName == "ama" ){

    fullTableInfoFromEWSDServerDB = dbConnection.getInformationShema(minDayOffset,maxDayOffset,dbConnection.getEWSDConnection());

    } else if ( dbName == "cs" ){

    fullTableInfoFromEWSDServerDB = dbConnection.getInformationShema(minDayOffset,maxDayOffset,dbConnection.getEWSDConnection());

    }

    fullTableInfoIterator = fullTableInfoFromEWSDServerDB.begin();

    while ( fullTableInfoIterator != fullTableInfoFromEWSDServerDB.end() ) {
            TableInfo tableInfo = *fullTableInfoIterator;
            shortTableInfoFromEWSDServerDB.insert(tableInfo.getTableName(),tableInfo.getTableRows());
            ++fullTableInfoIterator;
    }

    shortTableInfoIterator = shortTableInfoFromEWSDServerDB.begin();

    while ( shortTableInfoIterator != shortTableInfoFromEWSDServerDB.end() ) {

            tableNamesForAddIndex.push_back(shortTableInfoIterator.key());

            ++shortTableInfoIterator;

    }

    this->setTableNamesForAddIndex(tableNamesForAddIndex);

    this->setArrayOfDateOffsetForAddIndex();

}


void Task::preparationTableNamesForSearchInDB(int minDayOffset, int maxDayOffset){

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Connector dbConnection;
    dbConnection.initConnection(config);

    bool connectionToMySQLServerIsOK = false;
    while (!connectionToMySQLServerIsOK){
            connectionToMySQLServerIsOK = dbConnection.connectToMySQLServer(config);
    }

    QMap<QString,TableInfo> fullTableInfoFromEWSDServer;

    QMap<QString,TableInfo>::iterator fullTableInfoIterator;

    QMap<QString,quint64> shortTableInfoFromEWSDServer;

    QMap<QString,quint64>::iterator shortTableInfoEWSDIterator;

    QVector<QString> tableNamesForSearchInDB;

    fullTableInfoFromEWSDServer = dbConnection.getInformationShema(minDayOffset,maxDayOffset,dbConnection.getEWSDConnection());

    fullTableInfoIterator = fullTableInfoFromEWSDServer.begin();

    while ( fullTableInfoIterator != fullTableInfoFromEWSDServer.end() ) {
            TableInfo tableInfo = *fullTableInfoIterator;
            shortTableInfoFromEWSDServer.insert(tableInfo.getTableName(),tableInfo.getTableRows());
            ++fullTableInfoIterator;
    }

    shortTableInfoEWSDIterator = shortTableInfoFromEWSDServer.begin();

    while ( shortTableInfoEWSDIterator != shortTableInfoFromEWSDServer.end() ) {

            tableNamesForSearchInDB.push_back(shortTableInfoEWSDIterator.key());

            ++shortTableInfoEWSDIterator;

    }

    this->setTableNamesForSearch(tableNamesForSearchInDB);

    this->setArrayOfDateOffsetForSearch();

//  dbConnection.closeConnections();

}


QVector<int> Task::getArrayOfDayOffsetForImportTable(){
    return arrayOfDayOffsetForImportTable;
}

QVector<int> Task::getArrayOfDayOffsetForAddIndex(){
    return arrayOfDayOffsetForAddIndex;
}

QVector<int> Task::getArrayOfDayOffsetForSearch(){
    return arrayOfDayOffsetForSearch;
}

void Task::setArrayOfDateOffsetForImportTable(){

    QVector<int> arrayOfDateOffset;
    QVector<QString> tableNames = this->getTableNamesForImport();

    if ( tableNames.size() !=0 ){

    for ( int i = 0; i < tableNames.size(); i++ ){

        QString tableName = tableNames.at(i);
        QDate dateFromTableName = QDate().fromString(tableName.right(8),"yyyyMMdd");
        QDate dateNow = QDate().currentDate();
        int coutDaysToCurrentDate = dateFromTableName.daysTo(dateNow);
        coutDaysToCurrentDate =  (-1) * coutDaysToCurrentDate;
        arrayOfDateOffset.push_back(coutDaysToCurrentDate);

    }

    }

    arrayOfDayOffsetForImportTable = arrayOfDateOffset;

}


void Task::setArrayOfDateOffsetForAddIndex(){

    QVector<int> arrayOfDateOffset;
    QVector<QString> tableNames = this->getTableNamesForAddIndex();

    if ( tableNames.size() !=0 ){

    for ( int i = 0; i < tableNames.size(); i++ ){

        QString tableName = tableNames.at(i);
        QDate dateFromTableName = QDate().fromString(tableName.right(8),"yyyyMMdd");
        QDate dateNow = QDate().currentDate();
        int coutDaysToCurrentDate = dateFromTableName.daysTo(dateNow);
        coutDaysToCurrentDate =  (-1) * coutDaysToCurrentDate;
        arrayOfDateOffset.push_back(coutDaysToCurrentDate);

    }

    }

    arrayOfDayOffsetForAddIndex = arrayOfDateOffset;

}

void Task::setArrayOfDateOffsetForSearch(){

    QVector<int> arrayOfDateOffset;
    QVector<QString> tableNames = this->getTableNamesForSearch();

    if ( tableNames.size() !=0 ){

    for ( int i = 0; i < tableNames.size(); i++ ){

        QString tableName = tableNames.at(i);
        QDate dateFromTableName = QDate().fromString(tableName.right(8),"yyyyMMdd");
        QDate dateNow = QDate().currentDate();
        int coutDaysToCurrentDate = dateFromTableName.daysTo(dateNow);
        coutDaysToCurrentDate =  (-1) * coutDaysToCurrentDate;
        arrayOfDateOffset.push_back(coutDaysToCurrentDate);

    }

    }

    arrayOfDayOffsetForSearch = arrayOfDateOffset;

}

int Task::loadTablesFromDataBase(QApplication *application, int minDayOffset, int maxDayOffset){

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Loader loader;

    for ( int i = minDayOffset; i <= maxDayOffset; i++ ){

        QString currStrDate = QDate::currentDate().addDays(i).toString("yyyyMMdd");
        loader.dumpDataFromDataBase(application,config,currStrDate);

    }

    return 0;

}

int Task::loadTablesInDataBase(QApplication *application, int minDayOffset, int maxDayOffset){

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Loader loader;

    for ( int i = minDayOffset; i <= maxDayOffset; i++ ){

        QString currStrDate = QDate::currentDate().addDays(i).toString("yyyyMMdd");

        QString uploadedFile = config.getParameterByKey("dbDump");
                uploadedFile.append("t");
                uploadedFile.append(currStrDate);
                uploadedFile.append(".sql");

        if ( QFile(uploadedFile).exists() ){
        if ( loader.loadDataInDataBaseUsingDump(application,config,currStrDate) ){

                if ( QFile(uploadedFile).exists() ){
                     QFile(uploadedFile).remove();
                }
        }
        }
    }

    return 0;

}

int Task::manualTableSynchronization(QApplication *application){

        for ( int i = 0; i < arrayOfDayOffsetForImportTable.size(); i++ ){

            int dayOffset = arrayOfDayOffsetForImportTable.at(i);
            this->loadTablesFromDataBase(application,dayOffset,dayOffset);
            this->loadTablesInDataBase(application,dayOffset,dayOffset);

        }

        return 0;

}

int Task::addGeneralKeysInEWSDBigTable(){

    QString update_state_db_offline = "UPDATE stateDB SET name=\'OFFLINE\'";

    QString createIndex_datetime_unix = "CREATE INDEX datetime_unix ON amarecord(datetime_unix) USING BTREE";
    QString createIndex_idFileName = "CREATE INDEX idFileName ON amarecord(idFileName) USING BTREE";
    QString createIndex_PhoneA_PhoneB = "CREATE INDEX PhoneA_PhoneB ON amarecord";
    createIndex_PhoneA_PhoneB.append("(PhoneNumberA,PhoneNumberB,answer,callDuaration,offset,idFileName,datetime_unix)");
    createIndex_PhoneA_PhoneB.append("USING BTREE");
    QString createIndex_PhoneB = "CREATE INDEX PhoneB ON amarecord";
    createIndex_PhoneB.append("(PhoneNumberB,answer,callDuaration,offset,idFileName,datetime_unix)");
    createIndex_PhoneB.append("USING BTREE");

    QString update_state_db_online = "UPDATE stateDB SET name=\'OFFLINE\'";

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Connector dbConnection;
    dbConnection.initConnection(config);

    bool connectionToMySQLServerIsOK = false;
    while (!connectionToMySQLServerIsOK){
            connectionToMySQLServerIsOK = dbConnection.connectToMySQLServer(config);
    }

    QString useDB = "USE " + config.getParameters().value("dbName");

    QSqlQuery *query = new QSqlQuery(dbConnection.getEWSDConnection());

    if (!(dbConnection.RunMySQLQuery(config,useDB,true,*query)))
    {
        qDebug() << "Unable to exec query:" << query->lastError();
      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete query;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return 0;
    }

    if (!(dbConnection.RunMySQLQuery(config,update_state_db_offline,true,*query)))
    {
        QString lastError = query->lastError().text();
        if ( lastError.indexOf("Duplicate key name") < 0 ) {

        qDebug() << "Unable to exec query:" << query->lastError();
      //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete query;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return 0;
    }

    }

    if (!(dbConnection.RunMySQLQuery(config,createIndex_datetime_unix,true,*query)))
    {
        QString lastError = query->lastError().text();
        if ( lastError.indexOf("Duplicate key name") < 0 ) {

        qDebug() << "Unable to exec query:" << query->lastError();
      //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete query;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return 0;
    }

    }

    if (!(dbConnection.RunMySQLQuery(config,createIndex_idFileName,true,*query)))
    {
        QString lastError = query->lastError().text();
        if ( lastError.indexOf("Duplicate key name") < 0 ) {

        qDebug() << "Unable to exec query:" << query->lastError();
      //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete query;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return 0;
    }

    }

    if (!(dbConnection.RunMySQLQuery(config,createIndex_PhoneA_PhoneB,true,*query)))
    {
        QString lastError = query->lastError().text();
        if ( lastError.indexOf("Duplicate key name") < 0 ) {

        qDebug() << "Unable to exec query:" << query->lastError();
      //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete query;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return 0;
    }

    }

    if (!(dbConnection.RunMySQLQuery(config,createIndex_PhoneB,true,*query)))
    {
         QString lastError = query->lastError().text();
         if ( lastError.indexOf("Duplicate key name") < 0 ) {

         qDebug() << "Unable to exec query:" << query->lastError();
       //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
       //         "Ошибка", MB_OK|MB_ICONERROR);

         delete query;   // иначе память не может быть прочитана после выполнения delete!
       //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

         return 0;
    }

    }

    if (!(dbConnection.RunMySQLQuery(config,update_state_db_online,true,*query)))
    {
         QString lastError = query->lastError().text();
         if ( lastError.indexOf("Duplicate key name") < 0 ) {

         qDebug() << "Unable to exec query:" << query->lastError();
       //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
       //         "Ошибка", MB_OK|MB_ICONERROR);

         delete query;   // иначе память не может быть прочитана после выполнения delete!
       //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

         return 0;
    }

    }

    delete query;

    return 0;
}

int Task::addGeneralKeysAfterImportTablesInApusDatabase(){

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Connector dbConnection;
    dbConnection.initConnection(config);

    bool connectionToMySQLServerIsOK = false;
    while (!connectionToMySQLServerIsOK){
            connectionToMySQLServerIsOK = dbConnection.connectToMySQLServer(config);
    }

    dbConnection.createGeneralTablesInDatabase(config);

    QString useDB = "USE " + config.getParameters().value("dbNameAPUS");

    QSqlQuery *query = new QSqlQuery(dbConnection.getEWSDConnection());

    if (!(dbConnection.RunMySQLQuery(config,useDB,true,*query)))
    {
        qDebug() << "Unable to exec query:" << query->lastError();
      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete query;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return 0;
    }

    /*

    for (int i = -9; i <= -2; i++ ){

        arrayOfDayOffsetForAddIndex.push_back(i);

    }

    */


    for ( int i = 0; i < arrayOfDayOffsetForAddIndex.size(); i++ ){

        QString createIndex_ab_id = "CREATE INDEX a_id ON cs.t";
        int dayOffset = arrayOfDayOffsetForAddIndex.at(i);
        QString currStrDate = QDate::currentDate().addDays(dayOffset).toString("yyyyMMdd");
        createIndex_ab_id.append(currStrDate);
        createIndex_ab_id.append("(a_id)");
        createIndex_ab_id.append(" USING BTREE");

        QString createIndex_nabor = "CREATE INDEX nabor ON cs.t";
        createIndex_nabor.append(currStrDate);
        createIndex_nabor.append("(nabor)");
        createIndex_nabor.append(" USING BTREE");

        QString createIndex_a_id_nabor = "CREATE INDEX a_id_nabor ON cs.t";
        createIndex_a_id_nabor.append(currStrDate);
        createIndex_a_id_nabor.append("(a_id,nabor)");
        createIndex_a_id_nabor.append(" USING BTREE");

        QString createIndex_t = "CREATE INDEX t ON cs.t";
        createIndex_t.append(currStrDate);
        createIndex_t.append("(t)");
        createIndex_t.append(" USING BTREE");

        QString createIndex_dlit = "CREATE INDEX dlit ON cs.t";
        createIndex_dlit.append(currStrDate);
        createIndex_dlit.append("(dlit)");
        createIndex_dlit.append(" USING BTREE");

        if (!(dbConnection.RunMySQLQuery(config,createIndex_ab_id,true,*query)))
        {
            QString lastError = query->lastError().text();
            if ( lastError.indexOf("Duplicate key name") < 0 ) {

            qDebug() << "Unable to exec query:" << query->lastError();
          //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
          //         "Ошибка", MB_OK|MB_ICONERROR);

            delete query;   // иначе память не может быть прочитана после выполнения delete!
          //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

            return 0;
        }

        }

        if (!(dbConnection.RunMySQLQuery(config,createIndex_nabor,true,*query)))
        {
            QString lastError = query->lastError().text();
            if ( lastError.indexOf("Duplicate key name") < 0 ) {

            qDebug() << "Unable to exec query:" << query->lastError();
          //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
          //         "Ошибка", MB_OK|MB_ICONERROR);

            delete query;   // иначе память не может быть прочитана после выполнения delete!
          //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

            return 0;
        }

        }

        if (!(dbConnection.RunMySQLQuery(config,createIndex_a_id_nabor,true,*query)))
        {
            QString lastError = query->lastError().text();
            if ( lastError.indexOf("Duplicate key name") < 0 ) {

            qDebug() << "Unable to exec query:" << query->lastError();
          //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
          //         "Ошибка", MB_OK|MB_ICONERROR);

            delete query;   // иначе память не может быть прочитана после выполнения delete!
          //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

            return 0;
        }

        }

        if (!(dbConnection.RunMySQLQuery(config,createIndex_t,true,*query)))
        {
            QString lastError = query->lastError().text();
            if ( lastError.indexOf("Duplicate key name") < 0 ) {

            qDebug() << "Unable to exec query:" << query->lastError();
          //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
          //         "Ошибка", MB_OK|MB_ICONERROR);

            delete query;   // иначе память не может быть прочитана после выполнения delete!
          //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

            return 0;
        }

        }

        if (!(dbConnection.RunMySQLQuery(config,createIndex_dlit,true,*query)))
        {
            QString lastError = query->lastError().text();
            if ( lastError.indexOf("Duplicate key name") < 0 ) {

            qDebug() << "Unable to exec query:" << query->lastError();
          //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
          //         "Ошибка", MB_OK|MB_ICONERROR);

            delete query;   // иначе память не может быть прочитана после выполнения delete!
          //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

            return 0;
        }

        }

    }

    delete query;

    return 0;

}

int Task::generateCallInformationInDB(int minDayOffset, int maxDayOffset, uint allowedCountRecords){

    QVector<CallInformation> callInfoCollection;
    QMultiMap<QDate,CallInformation> callInfoWithDateCollection;

    DataGenerator dataGenerater;
    CallInformation callInfoForCollector;
    CallInformationCollector callInfoCollector;
    FileWriter fileWriter;
    Loader loader;

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Connector dbConnection;
    dbConnection.initConnection(config);

    bool connectionToMySQLServerIsOK = false;
    while (!connectionToMySQLServerIsOK){
            connectionToMySQLServerIsOK = dbConnection.connectToMySQLServer(config);
    }

    dbConnection.createGeneralTablesInDatabase(config);

    dbConnection.setDbNameForImportData("APUS");

    QTime time = QTime::currentTime();
    qsrand((unsigned int)time.msec());

    for ( int i = minDayOffset; i <= maxDayOffset; i++ ) {

    for ( uint j = 0; j < allowedCountRecords; j++ ) {

    if ( j == allowedCountRecords - 1 ) { continue; }

    callInfoForCollector = dataGenerater.getGeneratedData(i,i+1);
    callInfoCollector.addNewCallInformationIntoCollection(callInfoForCollector);

    if ( (( j != 0 ) && ( j % ( allowedCountRecords / 10 )  == 0 )) || ( j == ( allowedCountRecords - 1 ) ) ){

    callInfoCollector.setCallInformationWithDateCollection();
    callInfoCollector.setDateFileNames();

    callInfoCollection = callInfoCollector.getCollection();
    callInfoWithDateCollection = callInfoCollector.getCallInformationWithDateCollection();

    QString csvDirectory = QApplication::applicationDirPath();
    callInfoCollector.setFileNames(csvDirectory,".csv");

    fileWriter.writeCSVFilesForLoadDataInMySQLServer(csvDirectory,callInfoWithDateCollection,false);
    loader.loadArrayDataInDB(config,dbConnection,callInfoCollector.getFileNames());

    QString csvFile = QApplication::applicationDirPath()+"/test_"+QString::number(j+1/10)+".unl";
    fileWriter.writeCSVFile(csvFile,callInfoCollection,false);

    callInfoCollector.clearCallInformationCollection();
    callInfoCollector.clearCallInformationWithDateCollection();
    callInfoCollector.clearDateFileNames();
    callInfoCollector.clearFileNames();

    }

    }

    }

    /*

    dbConnection.setDbNameForImportData("EWSD");

    for ( int i = minDayOffset; i <= maxDayOffset; i++ ) {

    for ( uint j = 0; j < allowedCountRecords; j++ ) {

    if ( j == allowedCountRecords - 1 ) { continue; }

    callInfoForCollector = dataGenerater.getGeneratedData(i,i+1);
    callInfoCollector.addNewCallInformationIntoCollection(callInfoForCollector);

    if ( (( j != 0 ) && ( j % ( allowedCountRecords / 10 )  == 0 )) || ( j == ( allowedCountRecords - 1 ) ) ){

    callInfoCollector.setCallInformationWithDateCollection();
    callInfoCollector.setDateFileNames();

    callInfoCollection = callInfoCollector.getCollection();
    callInfoWithDateCollection = callInfoCollector.getCallInformationWithDateCollection();

    QString csvDirectory = QApplication::applicationDirPath();
    callInfoCollector.setFileNames(csvDirectory,".csv");

    fileWriter.writeCSVFilesForLoadDataInMySQLServer(csvDirectory,callInfoWithDateCollection,false);
    loader.loadArrayDataInDB(config,dbConnection,callInfoCollector.getFileNames());

    QString csvFile = QApplication::applicationDirPath()+"/test_"+QString::number(j+1/10)+".unl";
    fileWriter.writeCSVFile(csvFile,callInfoCollection,false);

    callInfoCollector.clearCallInformationCollection();
    callInfoCollector.clearCallInformationWithDateCollection();
    callInfoCollector.clearDateFileNames();
    callInfoCollector.clearFileNames();

    }

    }

    }

    */

    return 0;

}

int Task::generateCallInformationForDB(QString databaseName){

    return 0;

}

int Task::searchInformationInDB(){

    XMLReader xmlReader;
    xmlReader.readXML(QString(""));

    Config config;
    config.setParameters(xmlReader.getConfigParameters());

    Connector dbSearchConnector;
    dbSearchConnector.initConnection(config);
    bool connectionToMySQLServerIsOK = false;
    while (!connectionToMySQLServerIsOK){
            connectionToMySQLServerIsOK = dbSearchConnector.connectToMySQLServer(config);
    }


    FileWriter fileWriter;
    SearchParameters searchParameters;

    searchParameters.setMySQLServerHostName("APUS-AND-EWSD");
    searchParameters.addNewSearchParameter("selectALL","false");
    searchParameters.addNewSearchParameter("selectInSmallAPUSTables","true");
    searchParameters.addNewSearchParameter("selectInSingleBigEWSDTable","false");
    searchParameters.addNewSearchParameter("selectInSmallEWSDTables","true");

    searchParameters.addNewSearchParameter("phoneNumberB","475117");

    QString startSearchDateForMySQL = "2014-01-01";
    QString startSearchTimeForMySQL =  "00:00:00";

    QString endSearchDateForMySQL = "2018-09-01";
    QString endSearchTimeForMySQL =  "23:59:59";

    quint32 datetimeForMySQL = 0;
    datetimeForMySQL = QDateTime::fromString(startSearchDateForMySQL + QString("T") + startSearchTimeForMySQL,Qt::ISODate).toTime_t();
    searchParameters.addNewSearchParameter("startSearchDateTimeForMySQL",QString::number(datetimeForMySQL ));

    datetimeForMySQL = QDateTime::fromString(endSearchDateForMySQL + QString("T") + endSearchTimeForMySQL,Qt::ISODate).toTime_t();
    searchParameters.addNewSearchParameter("endSearchDateTimeForMySQL",QString::number(datetimeForMySQL ));

    int startSearchDateOffset = searchParameters.getDayOffsetByDate(startSearchDateForMySQL,"yyyy-MM-dd");
    int endSearchDateOffset = searchParameters.getDayOffsetByDate(endSearchDateForMySQL,"yyyy-MM-dd");

    this->preparationTableNamesForSearchInDB(startSearchDateOffset, endSearchDateOffset);
    searchParameters.buildSQLQueryForSearch(this->getArrayOfDayOffsetForSearch());

    Search search;
    SearchResult searchResult;

    connectionToMySQLServerIsOK = false;
    while (!connectionToMySQLServerIsOK){
            connectionToMySQLServerIsOK = dbSearchConnector.connectToMySQLServer(config);
    }

    searchResult.setArrayOfSearchResult(search.selectCallRecordsInMySQLServer(dbSearchConnector,searchParameters,config));
    searchResult.sortArrayOfSearchResultByDateTimeUnix();
    searchResult.initUniqueArrayOfSearchResult();

    QVector<CallInformation> readyResult = searchResult.getReadySearchResult();

    QString resultFile = searchResult.getResultFileName(searchParameters);
    fileWriter.writeCSVFile(resultFile,readyResult,true);

    return 0;

}
