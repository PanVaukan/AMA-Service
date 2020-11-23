#include "connector.h"

Connector::Connector()
{
    this->isConnectedToDB = false;
}

void Connector::initConnection(Config paramsForConnectionString){

    dbDriver = paramsForConnectionString.getParameters().value("dbDriver");
    dbHost = paramsForConnectionString.getParameters().value("dbHost");
    dbPort = paramsForConnectionString.getParameters().value("dbPort");
    dbUser = paramsForConnectionString.getParameters().value("dbUser");
    dbPwd = paramsForConnectionString.getParameters().value("dbPwd");
    dbName = paramsForConnectionString.getParameters().value("dbName");
    dbHostAPUS = paramsForConnectionString.getParameters().value("dbHostAPUS");
    dbPortAPUS = paramsForConnectionString.getParameters().value("dbPortAPUS");
    dbUserAPUS = paramsForConnectionString.getParameters().value("dbUserAPUS");
    dbPwdAPUS = paramsForConnectionString.getParameters().value("dbPwdAPUS");
    dbNameAPUS = paramsForConnectionString.getParameters().value("dbNameAPUS");

}

bool Connector::connectToMySQLServer(Config paramsForConnectionString){

    if ( dbEWSD.open())
    {
        /*
        QString connection;
        connection = dbEWSD.connectionName();
        dbEWSD.close();
        dbEWSD = QSqlDatabase();
        dbEWSD.removeDatabase(connection);
        */

        QSqlDatabase theDatabase = QSqlDatabase::database( "Connection-To-MySQLServer-5.5" );
        theDatabase.close();
        QSqlDatabase::removeDatabase( "Connection-To-MySQLServer-5.5" );

    }

    if ( dbAPUS.open())
    {
        /*
        QString connection;
        connection = dbAPUS.connectionName();
        dbAPUS.close();
        dbAPUS = QSqlDatabase();
        dbAPUS.removeDatabase(connection);
        */

        QSqlDatabase theDatabase = QSqlDatabase::database( "Connection-To-MySQLServer-5-APUS" );
        theDatabase.close();
        QSqlDatabase::removeDatabase( "Connection-To-MySQLServer-5-APUS" );

    }

    if ( paramsForConnectionString.getParameters().value("dbDriver") == "MySQL_Qt_Driver")
    {
        dbEWSD = QSqlDatabase::addDatabase("QMYSQL","Connection-To-MySQLServer-5.5");
        dbEWSD.setHostName(dbHost);
        dbEWSD.setPort(dbPort.toInt());
        dbEWSD.setUserName(dbUser);
        dbEWSD.setPassword(dbPwd);
        dbEWSD.setDatabaseName(dbName);
      //db.setConnectOptions("protocol=memory;shared-memory-base-name=MySQL-SharedMemory;");
        dbEWSD.setConnectOptions("MYSQL_OPT_RECONNECT=1;");

        dbAPUS = QSqlDatabase::addDatabase("QMYSQL","Connection-To-MySQLServer-5-APUS");
        dbAPUS.setHostName(dbHostAPUS);
        dbAPUS.setPort(dbPortAPUS.toInt());
        dbAPUS.setUserName(dbUserAPUS);
        dbAPUS.setPassword(dbPwdAPUS);
        dbAPUS.setDatabaseName(dbNameAPUS);
      //dbAPUS.setConnectOptions("protocol=memory;shared-memory-base-name=MySQL-SharedMemory;");
        dbAPUS.setConnectOptions("MYSQL_OPT_RECONNECT=1;");

    }

    else if ( paramsForConnectionString.getParameters().value("dbDriver") == "MySQL_ODBC_Driver")
    {

        dbEWSD=QSqlDatabase::addDatabase("QODBC","Connection-To-MySQLServer-5.5");
        QString connectStr=QObject::tr("DRIVER={MySQL ODBC 3.51 Driver};Server=%1;"
                                   "Port=%2;Option=16384;Stmt=;Database=%3;Uid=%4;Pwd=%5;MYSQL_OPT_RECONNECT=1")
            .arg(dbHost).arg(dbPort).arg(dbName).arg(dbUser).arg(dbPwd);
        dbEWSD.setDatabaseName(connectStr);

        dbAPUS=QSqlDatabase::addDatabase("QODBC","Connection-To-MySQLServer-5.5-APUS");
        QString connectStrAPUS=QObject::tr("DRIVER={MySQL ODBC 3.51 Driver};Server=%1;"
                                   "Port=%2;Option=16384;Stmt=;Database=%3;Uid=%4;Pwd=%5;MYSQL_OPT_RECONNECT=1")
            .arg(dbHostAPUS).arg(dbPortAPUS).arg(dbNameAPUS).arg(dbUserAPUS).arg(dbPwdAPUS);
        dbAPUS.setDatabaseName(connectStrAPUS);

    }

    if ((!dbEWSD.open()) && (!dbAPUS.open()))
    {
        isConnectedToDB = false;
        QString lastErrorFromAPUS = dbAPUS.lastError().text();
        QString lastErrorFromEWSD = dbEWSD.lastError().text();
     // MessageBox (hwnd, "Не удалось подключиться к MySQL Server!\n AMA - планировщик временно не будет функционировать!",
     // "Ошибка!", MB_OK|MB_ICONINFORMATION);

        return false;
    }
     else
    {
       isConnectedToDB = true;
       QSqlQuery *queryForGetEWSDInfo = new QSqlQuery(dbEWSD);

       Logger logger;
       logger.writeLog(QString("Программа успешно подключилась к MySQL Server"),QString(""));

       if (!(RunMySQLQuery(paramsForConnectionString,"SELECT CONNECTION_ID()",false,*queryForGetEWSDInfo)))
       {
             qDebug() << "Unable to execute queryForGetInfo:" << queryForGetEWSDInfo->lastError();

             delete queryForGetEWSDInfo;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery queryLoadDataInFile(db) , а не в куче (new)

       }
       else
       {
              if (queryForGetEWSDInfo->next())
                  mysqlEWSD_Thread_ID = queryForGetEWSDInfo->value(0).toInt();
       }


         QSqlQuery *queryForGetAPUSInfo = new QSqlQuery(dbAPUS);

         if (!(RunMySQLQuery(paramsForConnectionString,"SELECT CONNECTION_ID()",false,*queryForGetAPUSInfo)))
         {
               qDebug() << "Unable to execute queryForGetInfo:" << queryForGetAPUSInfo->lastError();

               delete queryForGetAPUSInfo;   // иначе память не может быть прочитана после выполнения delete!
             //в противном случае придется создать обьект в стеке QSqlQuery queryLoadDataInFile(db) , а не в куче (new)

         }
         else
         {
               if (queryForGetAPUSInfo->next())
                   mysqlAPUS_Thread_ID = queryForGetAPUSInfo->value(0).toInt();
         }


         delete queryForGetAPUSInfo;
         delete queryForGetEWSDInfo;

     } //end else

     return true;

}

bool Connector::SecondaryConnectToMySQLServer(QString switchMySQLDriver){

        /*
        db = QSqlDatabase::addDatabase("QMYSQL","Connection-To-MySQLServer-5.5-Secondary");
        db.setHostName(dbHost);
        db.setPort(dbPort.toInt());
        db.setUserName(dbUser);
        db.setPassword(dbPwd);
        db.setDatabaseName(dbName);
      //db.setConnectOptions("protocol=memory;shared-memory-base-name=MySQL-SharedMemory;");
        db.setConnectOptions("MYSQL_OPT_RECONNECT=1;");
        */

        if (dbSecondaryEWSDConn.open())
        {
            QSqlDatabase theDatabase2 = QSqlDatabase::database( "Connection-To-MySQLServer-5.5-Secondary" );
            theDatabase2.close();
            QSqlDatabase::removeDatabase( "Connection-To-MySQLServer-5.5-Secondary" );
        }

            dbSecondaryEWSDConn=QSqlDatabase::addDatabase("QODBC","Connection-To-MySQLServer-5.5-Secondary");
            QString connectStr=QObject::tr("DRIVER={MySQL ODBC 3.51 Driver};Server=%1;"
                                       "Port=%2;Option=16384;Stmt=;Database=%3;Uid=%4;Pwd=%5;MYSQL_OPT_RECONNECT=1")
                .arg(dbHost).arg(dbPort).arg(dbName).arg(dbUser).arg(dbPwd);

            dbSecondaryEWSDConn.setDatabaseName(connectStr);


        if(!dbSecondaryEWSDConn.open())
        {
           isConnectedToDB = false;
          //MessageBox (hwnd, "Не удалось подключиться к MySQL Server!\nОпция быстрого поиска по AMA файлам не будет функционировать!",
          // "Ошибка!", MB_OK|MB_ICONINFORMATION);
           return false;
        }
         else
        {
           return true;
        }

}

bool Connector::ReconnectToMySQLServer(Config paramsForConnectionString){

        while (!isConnectedToDB)
        {
            this->connectToMySQLServer(paramsForConnectionString);
            // ConnectToMySQLServer();
        }

        if (!isConnectedToDB)
        this->isConnectedToDB = this->SecondaryConnectToMySQLServer("MySQL_ODBC_Driver");

        return true;

}


QSqlDatabase Connector::getAPUSConnection(){

    if (!dbAPUS.isOpen()) { dbAPUS.open();}
    return this->dbAPUS;

}

QSqlDatabase Connector::getEWSDConnection(){

    if (!dbEWSD.isOpen()) { dbEWSD.open();}
    return this->dbEWSD;

}

void Connector::openConnections(){

    if (!(dbAPUS.isOpen())) {dbAPUS.open();}
    if (!(dbEWSD.isOpen())) {dbEWSD.open();}

}

quint32 Connector::getMySQL_APUS_Thread_ID(){
    return mysqlAPUS_Thread_ID;
}

void Connector::setMySQL_APUS_Thread_ID(uint id){
    mysqlAPUS_Thread_ID = id;
}

quint32 Connector::getMySQL_EWSD_Thread_ID(){
    return mysqlEWSD_Thread_ID;
}

void Connector::setMySQL_EWSD_Thread_ID(uint id){
    mysqlEWSD_Thread_ID = id;
}

QString Connector::getDbNameFoImportData(){
    return dbNameForImportData;
}

void Connector::setDbNameForImportData(QString dbNameForImport){
    dbNameForImportData = dbNameForImport;
}

QString Connector::getDbAPUSName(){
    return dbNameAPUS;
}

QString Connector::getDbEWSDName(){
    return dbName;
}

bool Connector::createGeneralTablesInDatabase(Config config){

    QString useDB = "USE " + config.getParameters().value("dbName");

    QSqlQuery *queryEWSD = new QSqlQuery(this->getEWSDConnection());

    QString createEWSDDataBaseStr = "CREATE DATABASE IF NOT EXISTS ama\n";
    createEWSDDataBaseStr.append(" CHARACTER SET utf8\n");
    createEWSDDataBaseStr.append(" COLLATE utf8_general_ci");
    QString createAPUSDataBaseStr = "CREATE DATABASE IF NOT EXISTS cs";
    createAPUSDataBaseStr.append(" CHARACTER SET utf8\n");
    createAPUSDataBaseStr.append(" COLLATE utf8_general_ci");

    QString createStateDBStr = "CREATE TABLE IF NOT EXISTS statedb \n";
    createStateDBStr.append(" ( Id int(11) NOT NULL AUTO_INCREMENT,\n");
    createStateDBStr.append(" name varchar(255) NOT NULL DEFAULT \'\',\n");
    createStateDBStr.append(" message varchar(255) NOT NULL DEFAULT \'\',\n");
    createStateDBStr.append(" lasttimestamp timestamp NOT NULL DEFAULT \'0000-00-00 00:00:00\',\n");
    createStateDBStr.append(" currtimestamp timestamp NOT NULL DEFAULT \'0000-00-00 00:00:00\' ON UPDATE CURRENT_TIMESTAMP,\n");
    createStateDBStr.append(" PRIMARY KEY (Id))\n");
    createStateDBStr.append(" ENGINE = MYISAM\n");
    createStateDBStr.append(" CHARACTER SET utf8\n");
    createStateDBStr.append(" COLLATE utf8_general_ci");

    QString createOneBigEWSDTable = "CREATE TABLE IF NOT EXISTS amarecord\n";
    createOneBigEWSDTable.append("( ats_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigEWSDTable.append(" answer tinyint(1) NOT NULL DEFAULT 0,\n");
    createOneBigEWSDTable.append(" callDuration smallint(5) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigEWSDTable.append(" dateOfCall date NOT NULL DEFAULT \'0000-00-00\',\n");
    createOneBigEWSDTable.append(" datetime_unix int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigEWSDTable.append(" phoneNumberA varchar(22) NOT NULL DEFAULT \'-\',\n");
    createOneBigEWSDTable.append(" phoneNumberB varchar(22) NOT NULL DEFAULT \'-\',\n");
    createOneBigEWSDTable.append(" offset int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigEWSDTable.append(" idFileName int(11) UNSIGNED NOT NULL DEFAULT 0 )\n");
    createOneBigEWSDTable.append(" ENGINE = MYISAM\n");
    createOneBigEWSDTable.append(" CHARACTER SET utf8\n");
    createOneBigEWSDTable.append(" COLLATE utf8_general_ci");

    QString createAMARecordTemp1Table = "CREATE TABLE IF NOT EXISTS ama.amarecordtemp1\n";
    createAMARecordTemp1Table.append(" (id bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT,\n");
    createAMARecordTemp1Table.append(" ats_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp1Table.append(" answer tinyint(1) NOT NULL DEFAULT 0,\n");
    createAMARecordTemp1Table.append(" callDuration smallint(5) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp1Table.append(" dateOfCall date NOT NULL DEFAULT \'0000-00-00\',\n");
    createAMARecordTemp1Table.append(" datetime_unix int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp1Table.append(" phoneNumberA varchar(22) NOT NULL DEFAULT \'-\',\n");
    createAMARecordTemp1Table.append(" phoneNumberB varchar(22) NOT NULL DEFAULT \'-\',\n");
    createAMARecordTemp1Table.append(" offset int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp1Table.append(" idFileName int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp1Table.append(" PRIMARY KEY (id),\n");
    createAMARecordTemp1Table.append(" KEY datetime_unix (datetime_unix) USING BTREE,\n");
    createAMARecordTemp1Table.append(" KEY idFileName (idFileName) USING BTREE,\n");
    createAMARecordTemp1Table.append(" KEY PhoneA_PhoneB\n");
    createAMARecordTemp1Table.append(" (PhoneNumberA,PhoneNumberB,answer,callDuration,offset,\n");
    createAMARecordTemp1Table.append(" idFileName,datetime_unix) USING BTREE,\n");
    createAMARecordTemp1Table.append(" KEY PhoneB");
    createAMARecordTemp1Table.append(" (PhoneNumberB,answer,callDuration,offset,\n");
    createAMARecordTemp1Table.append(" idFileName,datetime_unix) USING BTREE)\n");
    createAMARecordTemp1Table.append(" ENGINE = MYISAM\n");
    createAMARecordTemp1Table.append(" CHARACTER SET utf8\n");
    createAMARecordTemp1Table.append(" COLLATE utf8_general_ci");

    QString createAMARecordTemp2Table = "CREATE TABLE IF NOT EXISTS ama.amarecordtemp2\n";
    createAMARecordTemp2Table.append(" (id bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT,\n");
    createAMARecordTemp2Table.append(" ats_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp2Table.append(" answer tinyint(1) NOT NULL DEFAULT 0,\n");
    createAMARecordTemp2Table.append(" callDuration smallint(5) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp2Table.append(" dateOfCall date NOT NULL DEFAULT \'0000-00-00\',\n");
    createAMARecordTemp2Table.append(" datetime_unix int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp2Table.append(" phoneNumberA varchar(22) NOT NULL DEFAULT \'-\',\n");
    createAMARecordTemp2Table.append(" phoneNumberB varchar(22) NOT NULL DEFAULT \'-\',\n");
    createAMARecordTemp2Table.append(" offset int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp2Table.append(" idFileName int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMARecordTemp2Table.append(" PRIMARY KEY (id),\n");
    createAMARecordTemp2Table.append(" KEY datetime_unix (datetime_unix) USING BTREE,\n");
    createAMARecordTemp2Table.append(" KEY idFileName (idFileName) USING BTREE,\n");
    createAMARecordTemp2Table.append(" KEY PhoneA_PhoneB");
    createAMARecordTemp2Table.append(" (PhoneNumberA,PhoneNumberB,answer,callDuration,offset,\n");
    createAMARecordTemp2Table.append(" idFileName,datetime_unix) USING BTREE,\n");
    createAMARecordTemp2Table.append(" KEY PhoneB");
    createAMARecordTemp2Table.append(" (PhoneNumberB,answer,callDuration,offset,\n");
    createAMARecordTemp2Table.append(" idFileName,datetime_unix) USING BTREE)\n");
    createAMARecordTemp2Table.append(" ENGINE = MYISAM\n");
    createAMARecordTemp2Table.append(" CHARACTER SET utf8\n");
    createAMARecordTemp2Table.append(" COLLATE utf8_general_ci");

    QString createPatternTable = "CREATE TABLE IF NOT EXISTS pattern\n";
    createPatternTable.append(" ( Id tinyint(3) UNSIGNED NOT NULL AUTO_INCREMENT,\n");
    createPatternTable.append(" ats_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createPatternTable.append(" name varchar(64) NOT NULL DEFAULT \'\',\n");
    createPatternTable.append(" dayname_pattern varchar(64) NOT NULL DEFAULT \'\',\n");
    createPatternTable.append(" monthname_pattern varchar(64) NOT NULL DEFAULT \'\',\n");
    createPatternTable.append(" yearname_pattern varchar(64) NOT NULL DEFAULT \'\',\n");
    createPatternTable.append(" foldername_pattern varchar(64) NOT NULL DEFAULT \'\',\n");
    createPatternTable.append(" subfoldername_pattern varchar(64) NOT NULL DEFAULT '',");
    createPatternTable.append(" filename_pattern varchar(64) NOT NULL DEFAULT \'\',\n");
    createPatternTable.append(" PRIMARY KEY (Id))");
    createPatternTable.append(" ENGINE = MYISAM");
    createPatternTable.append(" CHARACTER SET utf8\n");
    createPatternTable.append(" COLLATE utf8_general_ci");

    QString createAMAStorageTable = "CREATE TABLE IF NOT EXISTS amastorage\n";
    createAMAStorageTable.append(" ( Id smallint(5) UNSIGNED NOT NULL AUTO_INCREMENT,\n");
    createAMAStorageTable.append(" ats_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAStorageTable.append(" pattern_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAStorageTable.append(" path varchar(512) NOT NULL DEFAULT \'\',\n");
    createAMAStorageTable.append(" PRIMARY KEY (Id))\n");
    createAMAStorageTable.append(" ENGINE = MYISAM");
    createAMAStorageTable.append(" CHARACTER SET utf8\n");
    createAMAStorageTable.append(" COLLATE utf8_general_ci");

    QString createAMAFilesTable = "CREATE TABLE IF NOT EXISTS ama.amafiles\n";
    createAMAFilesTable.append(" ( id int(11) UNSIGNED NOT NULL AUTO_INCREMENT,\n");
    createAMAFilesTable.append(" ats_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" ats_name varchar(16) NOT NULL DEFAULT \'\',\n");
    createAMAFilesTable.append(" dateFileName varchar(10) NOT NULL DEFAULT \'\',\n");
    createAMAFilesTable.append(" FileName varchar(16) NOT NULL DEFAULT \'\',\n");
    createAMAFilesTable.append(" FullPathToFile varchar(128) NOT NULL DEFAULT \'\',\n");
    createAMAFilesTable.append(" inDB tinyint(1) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" offset_0_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" offset_3_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" offset_6_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" offset_9_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" offset_12_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" offset_15_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" offset_18_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" offset_21_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" cntRec_0_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" cntRec_3_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" cntRec_6_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" cntRec_9_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" cntRec_12_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" cntRec_15_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" cntRec_18_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" cntRec_21_hour int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" firstCopyTime datetime DEFAULT NULL,\n");
    createAMAFilesTable.append(" lastCopyTime datetime DEFAULT NULL,\n");
    createAMAFilesTable.append(" currentOffset int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" lastAppendDataTime datetime DEFAULT NULL,\n");
    createAMAFilesTable.append(" lastCountInsertedRows int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" getlastError tinyint(1) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" closed tinyint(1) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMAFilesTable.append(" PRIMARY KEY (id))\n");
    createAMAFilesTable.append(" ENGINE = MYISAM\n");
    createAMAFilesTable.append(" CHARACTER SET utf8\n");
    createAMAFilesTable.append(" COLLATE utf8_general_ci\n");

    QString createCSVFilesTable = "CREATE TABLE IF NOT EXISTS ama.csvfiles\n";
    createCSVFilesTable.append(" ( id int(11) UNSIGNED NOT NULL AUTO_INCREMENT,\n");
    createCSVFilesTable.append(" ats_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createCSVFilesTable.append(" dateFileName varchar(10) DEFAULT NULL,\n");
    createCSVFilesTable.append(" FullPathToFile varchar(128) NOT NULL DEFAULT '',\n");
    createCSVFilesTable.append(" lastFileSize int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
    createCSVFilesTable.append(" closed tinyint(1) UNSIGNED NOT NULL DEFAULT 0,\n");
    createCSVFilesTable.append(" PRIMARY KEY (id))\n");
    createCSVFilesTable.append(" ENGINE = MYISAM\n");
    createCSVFilesTable.append(" CHARACTER SET utf8\n");
    createCSVFilesTable.append(" COLLATE utf8_general_ci\n");

    QString createAMASearchTaskTable = "CREATE TABLE IF NOT EXISTS ama.searchtask\n";
    createAMASearchTaskTable.append(" ( id int(11) NOT NULL AUTO_INCREMENT,\n");
    createAMASearchTaskTable.append(" user_id int(11) UNSIGNED DEFAULT 0,\n");
    createAMASearchTaskTable.append(" name varchar(32) NOT NULL DEFAULT \'\',\n");
    createAMASearchTaskTable.append(" answer tinyint(1) UNSIGNED DEFAULT 0,\n");
    createAMASearchTaskTable.append(" callduration smallint(5) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMASearchTaskTable.append(" phoneNumberA varchar(32) DEFAULT \'-\',\n");
    createAMASearchTaskTable.append(" phoneNumberB varchar(32) DEFAULT \'-\',\n");
    createAMASearchTaskTable.append(" firstSearchDate date DEFAULT \'0000-00-00\',\n");
    createAMASearchTaskTable.append(" lastSearchDate date DEFAULT \'0000-00-00\',\n");
    createAMASearchTaskTable.append(" countFilesForSearch smallint(5) UNSIGNED NOT NULL DEFAULT 0,\n");
    createAMASearchTaskTable.append(" countFoundedCalls int(11) UNSIGNED DEFAULT 0,\n");
    createAMASearchTaskTable.append(" startSearchDateTime datetime DEFAULT \'0000-00-00 00:00:00\',\n");
    createAMASearchTaskTable.append(" finishSearchDateTime datetime DEFAULT \'0000-00-00 00:00:00\',\n");
    createAMASearchTaskTable.append(" PRIMARY KEY (id))\n");
    createAMASearchTaskTable.append(" ENGINE = MYISAM\n");
    createAMASearchTaskTable.append(" CHARACTER SET utf8\n");
    createAMASearchTaskTable.append(" COLLATE utf8_general_ci\n");

    QString createAMAUserTable = "CREATE TABLE IF NOT EXISTS ama.amauser\n";
    createAMAUserTable.append(" ( id int(11) UNSIGNED NOT NULL AUTO_INCREMENT,\n");
    createAMAUserTable.append(" name varchar(32) NOT NULL DEFAULT \'\',\n");
    createAMAUserTable.append(" password varchar(32) NOT NULL DEFAULT \'\',\n");
    createAMAUserTable.append(" lastLogOn datetime DEFAULT \'0000-00-00 00:00:00\',\n");
    createAMAUserTable.append(" enableLogin tinyint(3) UNSIGNED DEFAULT NULL,\n");
    createAMAUserTable.append(" limit_Select smallint(5) UNSIGNED DEFAULT NULL,\n");
    createAMAUserTable.append(" codeRegion tinyint(3) UNSIGNED DEFAULT NULL,\n");
    createAMAUserTable.append(" showMessage tinyint(1) UNSIGNED DEFAULT NULL,\n");
    createAMAUserTable.append(" message text DEFAULT NULL,\n");
    createAMAUserTable.append(" currentVersion varchar(16) DEFAULT NULL,\n");
    createAMAUserTable.append(" comment varchar(128) DEFAULT NULL,\n");
    createAMAUserTable.append(" date datetime DEFAULT \'0000-00-00 00:00:00\',\n");
    createAMAUserTable.append(" PRIMARY KEY (id))\n");
    createAMAUserTable.append(" ENGINE = MYISAM\n");
    createAMAUserTable.append(" CHARACTER SET utf8\n");
    createAMAUserTable.append(" COLLATE utf8_general_ci\n");

    QString createOneBigAPUSTable = "CREATE TABLE IF NOT EXISTS tYYYYMMDD\n";
    createOneBigAPUSTable.append("( o_id SMALLINT(5) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" a_id INT(10) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" category TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" nabor VARCHAR(20) NOT NULL DEFAULT \'-\',\n");
    createOneBigAPUSTable.append(" k_nabor MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" `t` time NOT NULL DEFAULT \'00:00:00\',\n");
    createOneBigAPUSTable.append(" dlit MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" nach MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" on_id TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" in_id TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" serv_name TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" serv_type TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" options SMALLINT(5) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" k TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
    createOneBigAPUSTable.append(" f_id INT(10) UNSIGNED NOT NULL DEFAULT 0)\n");
    createOneBigAPUSTable.append(" ENGINE = MYISAM\n");
    createOneBigAPUSTable.append(" CHARACTER SET utf8\n");
    createOneBigAPUSTable.append(" COLLATE utf8_general_ci\n");


    if (!(this->RunMySQLQuery(config,createEWSDDataBaseStr,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString lastError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }


    if (!(this->RunMySQLQuery(config,useDB,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createStateDBStr,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createOneBigEWSDTable,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createAMARecordTemp1Table,true,*queryEWSD)))
    {

        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createAMARecordTemp2Table,true,*queryEWSD)))
    {

        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createPatternTable,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }


    if (!(this->RunMySQLQuery(config,createAMAStorageTable,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createAMAFilesTable,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createCSVFilesTable,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createAMAUserTable,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createAMASearchTaskTable,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createAPUSDataBaseStr,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    useDB = "USE " + config.getParameters().value("dbNameAPUS");

    if (!(this->RunMySQLQuery(config,useDB,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    if (!(this->RunMySQLQuery(config,createOneBigAPUSTable,true,*queryEWSD)))
    {
        qDebug() << "Unable to exec query:" << queryEWSD->lastError();
        QString strError = queryEWSD->lastError().text();

      //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
      //         "Ошибка", MB_OK|MB_ICONERROR);

        delete queryEWSD;   // иначе память не может быть прочитана после выполнения delete!
      //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

        return false;
    }

    delete queryEWSD;

    return true;

}

QMap<QString,TableInfo> Connector::getInformationShema(int minDayOffset, int maxDayOffset, QSqlDatabase db){

    QString sqlQueryStr;
    TableInfo tableInfo;
    QMap<QString,TableInfo> tableInfoCollection;

    if (!(db.isOpen())){
          db.open();
    }

    QSqlQuery *queryForSearchInMySQLServer = new QSqlQuery(db);

    sqlQueryStr = "SELECT t.TABLE_SCHEMA, t.TABLE_NAME, t.TABLE_COLLATION, t.TABLE_ROWS,\n";
    sqlQueryStr.append(" t.CREATE_TIME, t.UPDATE_TIME, t.CHECK_TIME\n");
    sqlQueryStr.append(" FROM information_schema.TABLES t\n");
    sqlQueryStr.append(" WHERE t.TABLE_SCHEMA = \'cs\' AND t.TABLE_NAME LIKE \'t%\' \n");
    sqlQueryStr.append(" AND t.TABLE_NAME IN\n");
    sqlQueryStr.append(" ( ");

    for ( int i = minDayOffset; i <= maxDayOffset; i++ ) {

        QDateTime dateTime = QDateTime(QDateTime::currentDateTime()).addDays(i);
        QString tableNameStr = "t";
        tableNameStr.append(dateTime.toString("yyyyMMdd"));

        sqlQueryStr.append("\'");
        sqlQueryStr.append(tableNameStr);
        sqlQueryStr.append("\'");

        if ( i != maxDayOffset ){
            sqlQueryStr.append(",");
        } else {
            sqlQueryStr.append(" )");
        }

    }

    sqlQueryStr.append("\n");
    sqlQueryStr.append(" ORDER BY t.TABLE_NAME");

//  if ( queryForSearchInMySQLServer->isValid() ){
    if ( !(queryForSearchInMySQLServer->exec(sqlQueryStr))){
        QString strError = queryForSearchInMySQLServer->lastError().text();
        strError = "";

    }
    else {  // if ( queryForSearchInAPUSServer->size() > 0 )

            while (queryForSearchInMySQLServer->next()){

                TableInfo tableInfo;
                tableInfo.setTableShema(queryForSearchInMySQLServer->value(0).toString());
                tableInfo.setTableName(queryForSearchInMySQLServer->value(1).toString());
                tableInfo.setTableCollation(queryForSearchInMySQLServer->value(2).toString());
                tableInfo.setTableRows(queryForSearchInMySQLServer->value(3).toULongLong());
                tableInfo.setCreateTime(queryForSearchInMySQLServer->value(4).toString());
                tableInfo.setUpdateTime(queryForSearchInMySQLServer->value(5).toString());
                tableInfo.setCheckTime(queryForSearchInMySQLServer->value(6).toString());

                tableInfoCollection.insert(tableInfo.getTableName(),tableInfo);

            }
    }

//  }

    delete queryForSearchInMySQLServer;

    return tableInfoCollection;
}

bool Connector::RunMySQLQuery(Config paramsForConnectionString, QString queryString, bool isTransactionalQuery, QSqlQuery &queryForRun){

    //QSqlQuery queryForRun(db);
    //QSqlQuery *queryForRun = &queryOut;
      QString dateTimeStr = NULL;
      QString readyQueryString = queryString;
      QString sqlError = NULL;
    //QString qs;

      if (!(queryForRun.exec(readyQueryString)))
      {
          QString lastError = queryForRun.lastError().text();

          if ( lastError.indexOf("Duplicate key name") >= 0 ) {
              return true;
          }

          qDebug() << "Unable to execute queryForRun:" << queryForRun.lastError();

          sqlError = queryForRun.lastError().text();

          Logger logger;
          logger.writeLog(sqlError,"");

          /*

          bool isValid = queryForRun.isValid(); // -> returns false
          bool isSelect = queryForRun.isSelect(); // -> returns true
          bool isActive = queryForRun.isActive(); // -> returns true
          bool isFirst = queryForRun.first(); // -> returns false
          bool isLast = queryForRun.last(); // -> returns false
          bool isPrevious = queryForRun.previous(); // -> returns false

          */

          if (isTransactionalQuery)
          {

              /*
              QString connection;
              connection = db.connectionName();
              db.close();
              db = QSqlDatabase();
              db.removeDatabase(connection);
              */

              /*
              {
              //  The correct way to do it:
                  QSqlDatabase db = QSqlDatabase::database("sales");
                  QSqlQuery query("SELECT NAME, DOB FROM EMPLOYEES", db);
              }
              // Both "db" and "query" are destroyed because they are out of scope
              QSqlDatabase::removeDatabase("sales"); // correct

              */

              /*
              //Warning: There should be no open queries on the database connection when this function is called, otherwise a resource leak will occur
              qs.append(QSqlDatabase::database().connectionName());
              QSqlDatabase::removeDatabase(qs);
              */

              /*
              delete queryForRun;
              QSqlDatabase theDatabase = QSqlDatabase::database( "Connection-To-MySQLServer-5.5" );
              theDatabase.close();
              QSqlDatabase::removeDatabase( "Connection-To-MySQLServer-5.5" );
              */

              /*
              QSqlDatabase theDatabase2 = QSqlDatabase::database( "Connection-To-MySQLServer-5.5-Secondary" );
              theDatabase2.close();
              QSqlDatabase::removeDatabase( "Connection-To-MySQLServer-5.5-Secondary" );
              */

              Logger logger;
              logger.writeLog(QString("Внимание! Программа остановлена и ее нужно перезапустить\n"),QString(""));
              logger.writeLog(QString("Причина: потеря соединения во время импорта в базу данных\n"),QString(""));
              logger.writeLog(QString("Задание: проверить и починить все таблицы базы данных \'ama\'"),QString(""));

              return false;
          }
          else
              if ( (!(isTransactionalQuery)) && ((sqlError.indexOf("Lost connection to MySQL server during query"),0,Qt::CaseInsensitive)>=0))
              {
                  isConnectedToDB = false;
                  while (sqlError.indexOf("Lost connection to MySQL server during query",0,Qt::CaseInsensitive)>=0)
                  {
                      ReconnectToMySQLServer(paramsForConnectionString);

                      if (!(queryForRun.exec(readyQueryString)))
                      {
                          sqlError = queryForRun.lastError().text();
                          isConnectedToDB = false;

                          if ((sqlError.indexOf("Lost connection to MySQL server during query",0,Qt::CaseInsensitive)>=0))
                          {
                             return false;
                          }
                      }
                  }
                  isConnectedToDB = true;
              }
              else
              {
                  isConnectedToDB = false;
                  return false;
              }
      }
      else
      {
            //queryOut = *queryForRun;
              return true;
      }

      return true;
}

void Connector::closeConnections(){

    if ( dbAPUS.isOpen() ){
         dbAPUS.close();
    }

    if ( dbEWSD.isOpen() ){
         dbEWSD.close();
    }
}
