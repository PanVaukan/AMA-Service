#include "loader.h"

Loader::Loader()
{
}

bool Loader::dumpDataFromDataBase(QApplication *application, Config config, QString dateTableName){

    QStringList params;
    params << QString("--host=%1").arg(config.getParameterByKey("dbHostAPUS"));
    params << QString("--port=%2").arg(config.getParameterByKey("dbPortAPUS"));
    params << QString("--user=%3").arg(config.getParameterByKey("dbUserAPUS"));
    params << QString("--password=%4").arg(config.getParameterByKey("dbPwdAPUS"));
    params << QString("--add-drop-table");
//  params << QString("--disable-keys");
//  params << QString("--skip-opt");
    params << config.getParameterByKey("dbNameAPUS");
    params << QString("t").append(dateTableName);

    QString outputFile = config.getParameterByKey("dbDump");
    outputFile.append(QString("t"));
    outputFile.append(dateTableName);
    outputFile.append(QString(".sql"));

    QString program = QString("mysqldump");

    QProcess process(application);
    process.setStandardOutputFile(outputFile);
    process.start(program, params);

    while ( process.state() == QProcess::Running ){

            process.waitForFinished();

    }

    if ( process.exitCode() == process.NormalExit ){

            return true;            
    }
    else {
            return false;
    }
}

bool Loader::loadDataInDataBaseUsingDump(QApplication *application, Config config, QString dateTableName){

    QStringList params;
    params << QString("--host=%1").arg(config.getParameterByKey("dbHost"));
    params << QString("--port=%2").arg(config.getParameterByKey("dbPort"));
    params << QString("--user=%3").arg(config.getParameterByKey("dbUser"));
    params << QString("--password=%4").arg(config.getParameterByKey("dbPwd"));
//  params << QString("--opt");
    params << config.getParameterByKey("dbNameAPUS");
//  params << QString("t").append(dateTableName);

    QString inputFile = config.getParameterByKey("dbDump");
    inputFile.append(QString("t"));
    inputFile.append(dateTableName);
    inputFile.append(QString(".sql"));

    QString program = QString("mysql");

    QProcess process(application);
    process.setStandardInputFile(inputFile);
    process.start(program, params);

    while ( process.state() == QProcess::Running ){

            process.waitForFinished();

    }

    if ( process.exitCode() == process.NormalExit ){

            return true;
    }
    else {
            return false;
    }
}

bool Loader::loadDataInDataBaseUsingCSV(Config config, Connector connection, QString csvFileName){

     QString useDB = "USE " + config.getParameters().value("dbName");

     QSqlQuery *query = new QSqlQuery(connection.getEWSDConnection());

     QString queryStrPartOneForLoadData = "LOAD DATA LOCAL INFILE ";
     QString queryStrPartTwoForLoadDataInGeneralTable = " IGNORE INTO TABLE amarecordtemp1 CHARACTER SET utf8 FIELDS TERMINATED BY \';\' LINES TERMINATED BY \'\\n' ";
     queryStrPartTwoForLoadDataInGeneralTable.append("(ats_id,answer,callDuration,dateOfCall,datetime_unix,phoneNumberA,phoneNumberB,offset,IdFileName)");

     QString INSERT_SELECT_QUERY_STR_TMP = "INSERT INTO amarecordtemp2 (ats_id,answer,callDuration,dateOfCall,datetime_unix,phoneNumberA,phoneNumberB,";
     INSERT_SELECT_QUERY_STR_TMP.append("offset,IdFileName) ");
     INSERT_SELECT_QUERY_STR_TMP.append(" SELECT ats_id,answer,callDuration,dateOfCall,datetime_unix,phoneNumberA,phoneNumberB,");
     INSERT_SELECT_QUERY_STR_TMP.append(" offset,IdFileName ");
     INSERT_SELECT_QUERY_STR_TMP.append(" FROM amarecordtemp1");

     QString readySQLQuery = queryStrPartOneForLoadData + "\'" + csvFileName + "\'" + queryStrPartTwoForLoadDataInGeneralTable;

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

     QString createDayEWSDTablePartOne = "CREATE TABLE IF NOT EXISTS amarecord_";
     QString createDayEWSDTablePartTwo = "( ats_id tinyint(3) UNSIGNED NOT NULL DEFAULT 0,\n";
     createDayEWSDTablePartTwo.append(" answer tinyint(1) NOT NULL DEFAULT 0,\n");
     createDayEWSDTablePartTwo.append(" callDuration smallint(5) UNSIGNED NOT NULL DEFAULT 0,\n");
//   createDayEWSDTablePartTwo.append(" dateOfCall date NOT NULL DEFAULT \'0000-00-00\',\n");
     createDayEWSDTablePartTwo.append(" datetime_unix int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayEWSDTablePartTwo.append(" phoneNumberA varchar(22) NOT NULL DEFAULT \'-\',\n");
     createDayEWSDTablePartTwo.append(" phoneNumberB varchar(22) NOT NULL DEFAULT \'-\',\n");
     createDayEWSDTablePartTwo.append(" offset int(11) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayEWSDTablePartTwo.append(" idFileName int(11) UNSIGNED NOT NULL DEFAULT 0 )\n");
     createDayEWSDTablePartTwo.append(" ENGINE = MYISAM\n");
     createDayEWSDTablePartTwo.append(" CHARACTER SET utf8\n");
     createDayEWSDTablePartTwo.append(" COLLATE utf8_general_ci");

     QString createDayEWSDTable = createDayEWSDTablePartOne;
     File file;
     QString dateFileName = file.getDateFileNameByFullPathAMAFile(csvFileName,"yyyyMMdd");
     createDayEWSDTable.append(dateFileName);
     createDayEWSDTable.append("\n");
     createDayEWSDTable.append(createDayEWSDTablePartTwo);

     QString createDayAPUSTable = "CREATE TABLE IF NOT EXISTS tYYYYMMDD\n";
     createDayAPUSTable.append("( o_id SMALLINT(5) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" a_id INT(10) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" category TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" nabor VARCHAR(20) NOT NULL DEFAULT \'-\',\n");
     createDayAPUSTable.append(" k_nabor MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" `t` time NOT NULL DEFAULT \'00:00:00\',\n");
     createDayAPUSTable.append(" dlit MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" nach MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" on_id TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" in_id TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" serv_name TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" serv_type TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" options SMALLINT(5) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" k TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,\n");
     createDayAPUSTable.append(" f_id INT(10) UNSIGNED NOT NULL DEFAULT 0)\n");
     createDayAPUSTable.append(" ENGINE = MYISAM\n");
     createDayAPUSTable.append(" CHARACTER SET utf8\n");
     createDayAPUSTable.append(" COLLATE utf8_general_ci\n");

     QString createIndex_datetime_unix = "CREATE INDEX datetime_unix ON amarecord(datetime_unix) USING BTREE";
     QString createIndex_idFileName = "CREATE INDEX idFileName ON amarecord(idFileName) USING BTREE";
     QString createIndex_PhoneA_PhoneB = "CREATE INDEX PhoneA_PhoneB ON amarecord";
     createIndex_PhoneA_PhoneB.append(" (PhoneNumberA,PhoneNumberB,answer,callDuration,offset,idFileName,datetime_unix) USING BTREE");
     QString createIndex_PhoneB = "CREATE INDEX PhoneB ON amarecord";
     createIndex_PhoneB.append(" (PhoneNumberB,answer,callDuration,offset,idFileName,datetime_unix) USING BTREE");

     QString createIndex_ab_id = "CREATE INDEX ab_id ON tYYYYMMDD(ab_id) USING BTREE";
     QString createIndex_nabor = "CREATE INDEX nabor ON tYYYYMMDD(nabor) USING BTREE";
     QString createIndex_t = "CREATE INDEX t on tYYYYMMDD(t) USING BTREE";
     QString createIndex_dlit = "CREATE INDEX dlit on tYYYYMMDD(t) USING BTREE";

     QString createIndexStr = "";

     QString createTempTableAMADublicates = "CREATE TEMPORARY TABLE IF NOT EXISTS AMADublicates ENGINE=MYISAM\n";
     createTempTableAMADublicates.append(" (SELECT CONCAT(amaR.phoneNumberA,\";\",amaR.phoneNumberB,\";\",amaR.callduration,\";\",\n");
     createTempTableAMADublicates.append("amaR.datetime_unix,\";\",FROM_UNIXTIME(amaR.datetime_unix)) ALL_INFO,\n");
     createTempTableAMADublicates.append("COUNT(CONCAT(amaR.phoneNumberA,\";\",amaR.phoneNumberB,\";\",amaR.callduration\n");
     createTempTableAMADublicates.append(",\";\",amaR.datetime_unix,\";\",FROM_UNIXTIME(amaR.datetime_unix))) Cnt\n");
     createTempTableAMADublicates.append(" FROM amarecordtemp2 amaR\n");
     createTempTableAMADublicates.append(" USE INDEX (PhoneA_PhoneB)\n");
     createTempTableAMADublicates.append(" USE INDEX(datetime_unix), amafiles amaF\n");
     createTempTableAMADublicates.append(" WHERE (LENGTH(amaF.dateFileName)>0) AND (amaR.idFileName=amaF.Id)\n");
     createTempTableAMADublicates.append(" GROUP BY CONCAT(amaR.phoneNumberA,\";\",amaR.phoneNumberB,\";\",amaR.callduration,\";\",amaR.datetime_unix,\";\",FROM_UNIXTIME(amaR.datetime_unix))\n");
     createTempTableAMADublicates.append(" HAVING Cnt>15\n");
     createTempTableAMADublicates.append(" ORDER BY amaR.datetime_unix)");


     QString createTempTableAMARecordsDublicates = "CREATE TEMPORARY TABLE IF NOT EXISTS AMARecordsDublicates\n";
     createTempTableAMARecordsDublicates.append("( phoneNumberA char(24) DEFAULT \"\",\n");
     createTempTableAMARecordsDublicates.append(" phoneNumberB char(24) DEFAULT \"\",\n");
     createTempTableAMARecordsDublicates.append(" callDuration smallint(5) DEFAULT 0\n,");
     createTempTableAMARecordsDublicates.append(" datetime_unix int(11) UNSIGNED DEFAULT 0,\n");
     createTempTableAMARecordsDublicates.append(" INDEX datetime_unix (datetime_unix),\n");
     createTempTableAMARecordsDublicates.append(" INDEX PhoneA_PhoneB_Temporary (phoneNumberA, phoneNumberB, callDuration, datetime_unix)\n");
     createTempTableAMARecordsDublicates.append(" )");
     createTempTableAMARecordsDublicates.append(" ENGINE=MYISAM\n");
     createTempTableAMARecordsDublicates.append(" (SELECT SUBSTR(amaDubl.ALL_INFO, 1, LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",1))) PhoneNumberA,\n");
     createTempTableAMARecordsDublicates.append(" SUBSTR(amaDubl.ALL_INFO, LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",1))+2,");
     createTempTableAMARecordsDublicates.append(" LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",2))-LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",1))-1) PhoneNumberB,\n");
     createTempTableAMARecordsDublicates.append(" SUBSTR(amaDubl.ALL_INFO, LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",2))+2,");
     createTempTableAMARecordsDublicates.append(" LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",3))-LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",2))-1) callDuration,\n");
     createTempTableAMARecordsDublicates.append(" SUBSTR(amaDubl.ALL_INFO, LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",3))+2,");
     createTempTableAMARecordsDublicates.append(" LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",4))-LENGTH(SUBSTRING_INDEX(amaDubl.ALL_INFO,\";\",3))-1) datetime_unix\n");
     createTempTableAMARecordsDublicates.append(" FROM AMADublicates amaDubl)");


     QString createTempTableAMARecordsForCheck = "CREATE TEMPORARY TABLE IF NOT EXISTS AMARecordsForCheck\n";
     createTempTableAMARecordsForCheck.append("( phoneNumberA char(24) DEFAULT \"\",\n");
     createTempTableAMARecordsForCheck.append(" phoneNumberB char(24) DEFAULT \"\",\n");
     createTempTableAMARecordsForCheck.append(" callDuration smallint(5) DEFAULT 0,\n");
     createTempTableAMARecordsForCheck.append(" offset int(11) UNSIGNED DEFAULT 0,\n");
     createTempTableAMARecordsForCheck.append(" datetime_unix int(11) UNSIGNED DEFAULT 0,\n");
     createTempTableAMARecordsForCheck.append(" INDEX datetime_unix (datetime_unix),\n");
     createTempTableAMARecordsForCheck.append(" INDEX PhoneA_PhoneB_Temporary (phoneNumberA, phoneNumberB, callDuration, offset, datetime_unix)\n");
     createTempTableAMARecordsForCheck.append(")");
     createTempTableAMARecordsForCheck.append(" ENGINE=MYISAM\n");
     createTempTableAMARecordsForCheck.append(" (SELECT a.phoneNumberA, a.phoneNumberB, a.callDuration, a.datetime_unix, a.offset\n");
     createTempTableAMARecordsForCheck.append(" FROM amarecordtemp2 a USE INDEX (PhoneA_PhoneB),\n");
     createTempTableAMARecordsForCheck.append(" AMARecordsDublicates amaRecDubl\n");
     createTempTableAMARecordsForCheck.append(" WHERE ( a.phoneNumberA = amaRecDubl.PhoneNumberA )\n");
     createTempTableAMARecordsForCheck.append(" AND ( a.phoneNumberB = amaRecDubl.PhoneNumberB)\n");
     createTempTableAMARecordsForCheck.append(" AND ( a.callDuration = amaRecDubl.callDuration )\n");
     createTempTableAMARecordsForCheck.append(" AND ( a.datetime_unix = amaRecDubl.datetime_unix )");
     createTempTableAMARecordsForCheck.append(")");


     QString createTempTableNotRemoveableAMARecords = "CREATE TEMPORARY TABLE IF NOT EXISTS notRemoveableAMARecords\n";
     createTempTableNotRemoveableAMARecords.append("( phoneNumberA char(24) DEFAULT \"\",\n");
     createTempTableNotRemoveableAMARecords.append(" phoneNumberB char(24) DEFAULT \"\",\n");
     createTempTableNotRemoveableAMARecords.append(" callDuration smallint(5) DEFAULT 0,\n");
     createTempTableNotRemoveableAMARecords.append(" datetime_unix int(11) UNSIGNED DEFAULT 0,\n");
     createTempTableNotRemoveableAMARecords.append(" offset int(11) UNSIGNED DEFAULT 0,\n");
     createTempTableNotRemoveableAMARecords.append(" INDEX datetime_unix (datetime_unix),\n");
     createTempTableNotRemoveableAMARecords.append(" INDEX PhoneA_PhoneB_Temporary (phoneNumberA, phoneNumberB, callDuration, offset, datetime_unix)\n");
     createTempTableNotRemoveableAMARecords.append(")");
     createTempTableNotRemoveableAMARecords.append(" ENGINE=MYISAM\n");
     createTempTableNotRemoveableAMARecords.append(" (SELECT AMARecForCheck.phoneNumberA, AMARecForCheck.phoneNumberB, AMARecForCheck.callDuration,\n");
     createTempTableNotRemoveableAMARecords.append(" AMARecForCheck.datetime_unix, MIN(AMARecForCheck.offset) CorrectOffset\n");
     createTempTableNotRemoveableAMARecords.append(" FROM AMARecordsForCheck AMARecForCheck\n");
     createTempTableNotRemoveableAMARecords.append(" GROUP BY 1,2,3,4\n");
     createTempTableNotRemoveableAMARecords.append(" ORDER BY CorrectOffset)\n");


     QString deleteRemoveableDublicateAMARecords = "DELETE amarecordtemp2 FROM amarecordtemp2\n";
     deleteRemoveableDublicateAMARecords.append(" INNER JOIN notRemoveableAMARecords\n");
     deleteRemoveableDublicateAMARecords.append(" ON ( notRemoveableAMARecords.phoneNumberA = amarecordtemp2.phoneNumberA\n");
     deleteRemoveableDublicateAMARecords.append(" AND  notRemoveableAMARecords.phoneNumberB = amarecordtemp2.phoneNumberB\n");
     deleteRemoveableDublicateAMARecords.append(" AND  notRemoveableAMARecords.callDuration = amarecordtemp2.callDuration\n");
     deleteRemoveableDublicateAMARecords.append(" AND  notRemoveableAMARecords.datetime_unix = amarecordtemp2.datetime_unix )\n");
     deleteRemoveableDublicateAMARecords.append(" WHERE amarecordtemp2.offset != notRemoveableAMARecords.CorrectOffset");

     QString dropTemporaryTableAMADublicates = "DROP TEMPORARY TABLE AMADublicates";
     QString dropTemporaryTableAMARecordsDublicates = "DROP TEMPORARY TABLE AMARecordsDublicates";
     QString dropTemporaryTableAMARecordsForCheck = "DROP TEMPORARY TABLE AMARecordsForCheck";
     QString dropTemporaryTableNotRemoveableAMARecords = "DROP TEMPORARY TABLE notRemoveableAMARecords";

     QString INSERT_SELECT_QUERY_STR_FINAL = "INSERT IGNORE INTO amarecord (ats_id,answer,callDuration,dateOfCall,datetime_unix,phoneNumberA,phoneNumberB,";
     INSERT_SELECT_QUERY_STR_FINAL.append("offset,IdFileName) ");
     INSERT_SELECT_QUERY_STR_FINAL.append("SELECT a2.ats_id,a2.answer,a2.callDuration,a2.dateOfCall,a2.datetime_unix,a2.phoneNumberA,a2.phoneNumberB,");
     INSERT_SELECT_QUERY_STR_FINAL.append("a2.offset,a2.IdFileName ");
     INSERT_SELECT_QUERY_STR_FINAL.append("FROM amarecordtemp2 a2 ");
 //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 //  INSERT_SELECT_QUERY_STR.append(" LEFT JOIN amarecordtemp2 a2 ");
 //  INSERT_SELECT_QUERY_STR.append(" ON a1.id=a2.id ");
 //  INSERT_SELECT_QUERY_STR.append(" WHERE a2.id IS NULL ");
 //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

     QString INSERT_SELECT_QUERY_STR_FOR_DAY_TABLE;

     QString TRUNCATE_amarecordtemp1_table_str = "TRUNCATE TABLE amarecordtemp1";
     QString TRUNCATE_amarecordtemp2_table_str = "TRUNCATE TABLE amarecordtemp2";

     QString queryStrForGetLastInfo = "SELECT table_rows FROM information_schema.tables ";
     queryStrForGetLastInfo.append(" WHERE table_schema=");
     queryStrForGetLastInfo.append("\'");
     queryStrForGetLastInfo.append(connection.getDbEWSDName());
     queryStrForGetLastInfo.append("\'");
     queryStrForGetLastInfo.append(" AND table_name = 'amarecord'");

     QString SET_OFFLINE_STATE_DB = "UPDATE statedb SET name = \'OFFLINE\'";
     QString SET_ONLINE_STATE_DB = "UPDATE statedb SET name = \'ONLINE\'";

     if (!(connection.RunMySQLQuery(config,useDB,true,*query)))
     {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
     }

     if (!(connection.RunMySQLQuery(config,createOneBigEWSDTable,true,*query)))
     {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
     }

     if (!(connection.RunMySQLQuery(config,createDayEWSDTable,true,*query)))
     {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
     }


     if (!(connection.RunMySQLQuery(config,"SELECT CONNECTION_ID()",false,*query)))
     {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to execute query:" << query->lastError();

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
      }
      else
      {
              if (query->next())
                  connection.setMySQL_EWSD_Thread_ID(query->value(0).toInt());
      }


      if (!(connection.RunMySQLQuery(config,SET_OFFLINE_STATE_DB,false,*query)))
      {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to execute query:" << query->lastError();

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
      }

      if (!(connection.RunMySQLQuery(config,queryStrForGetLastInfo,false,*query)))
      {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
             //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
             //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
       }
       else
       {
             if (query->next())
             {
                 quint64 ulonglongNumber = query->value(0).toULongLong();
                 quint64 cntRecInDBBeforeLoadDataInFile = ulonglongNumber;
             }
       }

       if (!(connection.RunMySQLQuery(config,useDB,true,*query)))
       {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
       }

       if (!(connection.RunMySQLQuery(config,TRUNCATE_amarecordtemp1_table_str,false,*query)))
       {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
       }

         //****************************************************************************************************************
         // Начало критической секции:
       if ( !(connection.RunMySQLQuery(config,readySQLQuery,true,*query)))
       {
            QString lastError = query->lastError().text();
            qDebug() << "Unable to exec query:" << query->lastError();
          //MessageBox (NULL, "Невозможно импортировать CSV Файл в MySQL Server\nИмпорт CSV файлов остановлен",
          //        "Ошибка", MB_OK|MB_ICONERROR);

            delete query;   // иначе память не может быть прочитана после выполнения delete!
          //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

            return 0;
       }

       if (!(connection.RunMySQLQuery(config,TRUNCATE_amarecordtemp2_table_str,false,*query)))
       {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
       }


       if (!(connection.RunMySQLQuery(config,INSERT_SELECT_QUERY_STR_TMP,true,*query)))
       {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
       }


       if (!(connection.RunMySQLQuery(config,createTempTableAMADublicates,true,*query)))
       {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
       }

       if (!(connection.RunMySQLQuery(config,createTempTableAMARecordsDublicates,true,*query)))
       {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
       }

       if (!(connection.RunMySQLQuery(config,createTempTableAMARecordsForCheck,true,*query)))
       {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
       }

       if (!(connection.RunMySQLQuery(config,createTempTableNotRemoveableAMARecords,true,*query)))
       {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
        }

        if (!(connection.RunMySQLQuery(config,deleteRemoveableDublicateAMARecords,true,*query)))
        {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
        }


        if (!(connection.RunMySQLQuery(config,dropTemporaryTableAMADublicates,true,*query)))
        {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
        }

        if (!(connection.RunMySQLQuery(config,dropTemporaryTableAMARecordsDublicates,true,*query)))
        {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
        }

        if (!(connection.RunMySQLQuery(config,dropTemporaryTableAMARecordsForCheck,true,*query)))
        {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
        }


        if (!(connection.RunMySQLQuery(config,dropTemporaryTableNotRemoveableAMARecords,true,*query)))
        {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка очистки временной таблицы\nОчистка временной таблицы остановлена",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
        }

        if ( connection.getDbNameFoImportData() == "EWSD"){

        if (!(connection.RunMySQLQuery(config,INSERT_SELECT_QUERY_STR_FINAL,true,*query)))
        {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Ошибка перемещения данных с временной таблицы в основную\nИмпорт CSV файлов остановлен",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
        }


        INSERT_SELECT_QUERY_STR_FOR_DAY_TABLE = INSERT_SELECT_QUERY_STR_FINAL;
        INSERT_SELECT_QUERY_STR_FOR_DAY_TABLE.replace("INSERT IGNORE INTO amarecord",QString("INSERT IGNORE INTO amarecord_") + dateFileName);
        INSERT_SELECT_QUERY_STR_FOR_DAY_TABLE.replace("a2.dateOfCall,","");
        INSERT_SELECT_QUERY_STR_FOR_DAY_TABLE.replace("dateOfCall,","");


        if (!(connection.RunMySQLQuery(config,INSERT_SELECT_QUERY_STR_FOR_DAY_TABLE,false,*query)))
        {
             QString lastError = query->lastError().text();
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
        }

        if (config.getParameterByKey("dbCreateAnIndexAtTheBeginning") == "yes" ){

        createIndexStr = createIndex_datetime_unix;
        createIndexStr.replace("amarecord",QString("amarecord_") + dateFileName);


        if (!(connection.RunMySQLQuery(config,createIndexStr,false,*query)))
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

        createIndexStr = createIndex_idFileName;
        createIndexStr.replace("amarecord",QString("amarecord_") + dateFileName);


        if (!(connection.RunMySQLQuery(config,createIndexStr,false,*query)))
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

        createIndexStr = createIndex_PhoneA_PhoneB;
        createIndexStr.replace("amarecord",QString("amarecord_") + dateFileName);

        if (!(connection.RunMySQLQuery(config,createIndexStr,false,*query)))
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

        createIndexStr = createIndex_PhoneB;
        createIndexStr.replace("amarecord",QString("amarecord_") + dateFileName);


        if (!(connection.RunMySQLQuery(config,createIndexStr,false,*query)))
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

        }
        else if ( connection.getDbNameFoImportData() == "APUS"){

        query = new QSqlQuery(connection.getAPUSConnection());

        useDB = "USE " + config.getParameters().value("dbNameAPUS");

        QString INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query = "";

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.append("INSERT INTO ");

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.append(connection.getDbAPUSName());

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.append(".tYYYYMMDD (a_id,nabor,t,dlit) \n");

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.append("SELECT SUBSTRING(a.phoneNumberA,3,9), SUBSTRING(a.phoneNumberB,5,7),\n");

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.append("TIME(FROM_UNIXTIME(a.datetime_unix)), a.callDuration\n");

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.append(" FROM ");

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.append(connection.getDbEWSDName());

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.append(".amarecordtemp2 a");

        INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query.replace("YYYYMMDD",dateFileName);

        createDayAPUSTable.replace("YYYYMMDD",dateFileName);

        createIndex_ab_id.replace("YYYYMMDD",dateFileName);

        createIndex_nabor.replace("YYYYMMDD",dateFileName);

        createIndex_t.replace("YYYYMMDD",dateFileName);

        createIndex_dlit.replace("YYYYMMDD",dateFileName);

        if (!(connection.RunMySQLQuery(config,createOneBigAPUSTable,true,*query)))
        {

                 QString lastError = query->lastError().text();
                 qDebug() << "Unable to exec query:" << query->lastError();
               //MessageBox (NULL, "Ошибка перемещения данных с временной таблицы в основную\nИмпорт CSV файлов остановлен",
               //         "Ошибка", MB_OK|MB_ICONERROR);

                 delete query;   // иначе память не может быть прочитана после выполнения delete!
               //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

                 return 0;

        }

        if (!(connection.RunMySQLQuery(config,createDayAPUSTable,true,*query)))
        {

                 QString lastError = query->lastError().text();
                 Logger logger;
                 logger.writeLog(lastError,"");

                 qDebug() << "Unable to exec query:" << query->lastError();
               //MessageBox (NULL, "Ошибка перемещения данных с временной таблицы в основную\nИмпорт CSV файлов остановлен",
               //         "Ошибка", MB_OK|MB_ICONERROR);

                 delete query;   // иначе память не может быть прочитана после выполнения delete!
               //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

                 return 0;

        }

        if (!(connection.RunMySQLQuery(config,INSERT_INTO_AMA_SELECT_FROM_CS_DayTable_Query,false,*query)))
        {
                 QString lastError = query->lastError().text();
                 qDebug() << "Unable to exec query:" << query->lastError();
               //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
               //         "Ошибка", MB_OK|MB_ICONERROR);

                 delete query;   // иначе память не может быть прочитана после выполнения delete!
               //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

                 return 0;
        }

        if (config.getParameterByKey("dbCreateAnIndexAtTheBeginning") == "yes" ){

        if (!(connection.RunMySQLQuery(config,createIndex_ab_id,false,*query)))
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

         if (!(connection.RunMySQLQuery(config,createIndex_nabor,false,*query)))
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

         if (!(connection.RunMySQLQuery(config,createIndex_t,false,*query)))
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

         if (!(connection.RunMySQLQuery(config,createIndex_dlit,false,*query)))
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

         }


         if (!(connection.RunMySQLQuery(config,queryStrForGetLastInfo,false,*query)))
         {
             qDebug() << "Unable to exec query:" << query->lastError();
           //MessageBox (NULL, "Не удалось прочитать количество строк в служебной таблице",
           //         "Ошибка", MB_OK|MB_ICONERROR);

             delete query;   // иначе память не может быть прочитана после выполнения delete!
           //в противном случае придется создать обьект в стеке QSqlQuery query(db) , а не в куче (new)

             return 0;
         }
         else
         {
             if (query->next())
             {
                 quint64 ulonglongNumber = query->value(0).toULongLong();
                 quint64 cntRecInDBAfterLoadDataInFile = ulonglongNumber;
             }
         }

         return true;

}

bool Loader::loadArrayDataInDB(Config config, Connector connection, QVector<QString> csvFileNames){

         QVector<QString>::iterator csvFileNamesIterator;
         csvFileNamesIterator = csvFileNames.begin();

         while ( csvFileNamesIterator != csvFileNames.end() ){

                 QString currentCSVFileName = *csvFileNamesIterator;

                 this->loadDataInDataBaseUsingCSV(config,connection,currentCSVFileName);

                 csvFileNamesIterator++;

         }

         return true;

}

