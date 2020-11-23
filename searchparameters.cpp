#include "searchparameters.h"

SearchParameters::SearchParameters()
{
    this->answer = 0;
    this->callDuration = 0;
    this->phoneNumberA = "";
    this->phoneNumberB = "";
    this->startSearchDateTime = QDateTime(QDateTime::currentDateTime()).addDays(-31).toTime_t();
    this->endSearchDateTime = QDateTime(QDateTime::currentDateTime()).addDays(0).toTime_t();
    this->readySQLQuerysForSearchInAPUSdb.clear();
    this->readySQLQuerysForSearchInEWSDdb.clear();
}

QString SearchParameters::getMySQLServerHostName(){
    return MySQLServerHostName;
}

void SearchParameters::setMySQLServerHostName(QString host){
    MySQLServerHostName = host;
}

bool SearchParameters::getSelectAllData(){
    return selectAllData;
}

void SearchParameters::setSelectAllData(bool selectAll){
    selectAllData = selectAll;
}

bool SearchParameters::getAnswer(){
    return answer;
}

void SearchParameters::setAnswer(uint answer_){
    answer = answer_;
}

quint32 SearchParameters::getCallDuration(){
    return callDuration;
}

void SearchParameters::setCallDuration(uint callDuration_){
    callDuration = callDuration_;
}

QString SearchParameters::getPhoneNumberA(){
    return phoneNumberA;
}

void SearchParameters::setPhoneNumberA(QString phoneNumberA_){
    phoneNumberA = phoneNumberA_;
}

QString SearchParameters::getPhoneNumberB(){
    return phoneNumberB;
}

void SearchParameters::setPhoneNumberB(QString phoneNumberB_){
    phoneNumberB = phoneNumberB_;
}

quint32 SearchParameters::getStartSearchDateTime(){
    return startSearchDateTime;
}

void SearchParameters::setStartSearchDateTime(uint startSearchDateTime_){
    startSearchDateTime = startSearchDateTime_;
}

quint32 SearchParameters::getEndSearchDateTime(){
    return endSearchDateTime;
}

void SearchParameters::setEndSearchDateTime(uint endSearchDateTime_){
    endSearchDateTime = endSearchDateTime_;
}

void SearchParameters::addNewSearchParameter(QString key, QString value){

//  searchParametersForMySQLquery.setInsertInOrder(true);
    searchParametersForMySQLquery[key].append(value);

}

QMap<QString, QStringList> SearchParameters::getSearchParametersForMySQLquery(){
    return searchParametersForMySQLquery;
}

QStringList SearchParameters::getSearchValuesByKey(QString key){
    return searchParametersForMySQLquery.value(key);
}

QString SearchParameters::getSearchValueByKey(QString key, int item){
    return searchParametersForMySQLquery.value(key).at(item);
}

QString SearchParameters::addSearchParametersToSQLQuery(QString MySQL_Server){

    QString allSearchParameters;

    QString key;
    QStringList value;

    int countValuesInCollection = 0;
    searchParamsMapCurrentIterator = searchParametersForMySQLquery.begin();

    while ( searchParamsMapCurrentIterator != searchParametersForMySQLquery.end() ){

    key = searchParamsMapCurrentIterator.key();
    value = searchParamsMapCurrentIterator.value();
    countValuesInCollection = value.size();

    for (int countValues = 0; countValues < countValuesInCollection; countValues++)
    {

            if ( value.at(countValues) != "NoSearch" )
            {
                if ( key == "answer" && MySQL_Server.indexOf("APUS",0,Qt::CaseInsensitive)>=0 )
                {
                   // ÁÅÇÐÀÇËÈ×ÍÎ ; C ÎÒÂÅÒÎÌ ; ÁÅÇ ÎÒÂÅÒÀ

                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("dlit>0"));
                }
//              else
                if ( key == "answer" && MySQL_Server.indexOf("EWSD",0,Qt::CaseInsensitive)>=0 )
                {
                   // ÁÅÇÐÀÇËÈ×ÍÎ ; C ÎÒÂÅÒÎÌ ; ÁÅÇ ÎÒÂÅÒÀ

                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("answer="));
                    allSearchParameters.append(value.at(countValues));

                }
//              else
                if ( key == "phoneNumberA" && MySQL_Server.indexOf("APUS",0,Qt::CaseInsensitive)>=0 )
                {
                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("a_id LIKE\'"));
                    allSearchParameters.append(value.at(countValues));
                    allSearchParameters.append(QString("\'"));
                }
//              else
                if ( key == "phoneNumberA" && MySQL_Server.indexOf("EWSD",0,Qt::CaseInsensitive)>=0 )
                {
                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("phoneNumberA=\'"));
                    allSearchParameters.append(value.at(countValues));
                    allSearchParameters.append(QString("\'"));
                }
//              else
                if ( key == "phoneNumberB" && MySQL_Server.indexOf("APUS",0,Qt::CaseInsensitive)>=0 )
                {
                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                          allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("nabor=\'"));
                    allSearchParameters.append(value.at(countValues));
                    allSearchParameters.append(QString("\'"));
                }
//              else
                if ( key == "phoneNumberB" && MySQL_Server.indexOf("EWSD",0,Qt::CaseInsensitive)>=0 )
                {
                    if (!allSearchParameters.endsWith("AND"))
                      if (!allSearchParameters.endsWith("("))
                        if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("phoneNumberB=\'"));
                    allSearchParameters.append(value.at(countValues));
                    allSearchParameters.append(QString("\'"));
                }
//              else
                if ( key == "startSearchDateTimeForMySQL" && MySQL_Server.indexOf("EWSD",0,Qt::CaseInsensitive)>=0 )
                {
                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("datetime_unix>="));
                    allSearchParameters.append(value.at(countValues));
                }
//              else
                if ( key == "endSearchDateTimeForMySQL" && MySQL_Server.indexOf("EWSD",0,Qt::CaseInsensitive)>=0 )
                {
                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("datetime_unix<="));
                    allSearchParameters.append(value.at(countValues));
                }
//              else
                if ( key == "minCallDuration" && MySQL_Server.indexOf("APUS",0,Qt::CaseInsensitive)>=0 )
                {
                     if (!allSearchParameters.endsWith("AND"))
                        if (!allSearchParameters.endsWith("("))
                          if (!allSearchParameters.isEmpty())
                          allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("dlit>="));
                    allSearchParameters.append(value.at(countValues));

                }
//              else
                if ( key == "maxCallDuration" && MySQL_Server.indexOf("APUS",0,Qt::CaseInsensitive)>=0 )
                {
                     if (!allSearchParameters.endsWith("AND"))
                        if (!allSearchParameters.endsWith("("))
                          if (!allSearchParameters.isEmpty())
                          allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("dlit<="));
                    allSearchParameters.append(value.at(countValues));

                }
//              else
                if ( key == "minCallDuration" && MySQL_Server.indexOf("EWSD",0,Qt::CaseInsensitive)>=0 )
                {
                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("callDuration>="));
                    allSearchParameters.append(value.at(countValues));

                }
//              else
                if ( key == "maxCallDuration" && MySQL_Server.indexOf("EWSD",0,Qt::CaseInsensitive)>=0 )
                {
                    if (!allSearchParameters.endsWith("AND"))
                       if (!allSearchParameters.endsWith("("))
                         if (!allSearchParameters.isEmpty())
                         allSearchParameters.append(QString(" AND "));

                    allSearchParameters.append(QString("callDuration<="));
                    allSearchParameters.append(value.at(countValues));

                }
            }
          }
                    ++searchParamsMapCurrentIterator;
    }

    return allSearchParameters;
}

void SearchParameters::addSQLQuerysForSearchInAPUSdb(QString query){
    readySQLQuerysForSearchInAPUSdb.push_back(query);
}

void SearchParameters::addSQLQuerysForSearchInEWSDdb(QString query){
    readySQLQuerysForSearchInEWSDdb.push_back(query);
}


qint64 SearchParameters::getDayOffsetByDate(QString dateStr, QString format){

    QDate date = QDate(QDate::fromString(dateStr,format));
    QDate currentDate = QDate(QDate::currentDate());
    qint64 dayOffset = (-1) * date.daysTo(currentDate);

    return dayOffset;

}

qint64 SearchParameters::getDayOffsetByDateTime(uint unixtime){

    QDateTime dateTime = QDateTime(QDateTime::fromTime_t(unixtime));
    QDateTime currentDateTime = QDateTime(QDateTime::currentDateTime());

    qint64 dayOffset = (-1) * dateTime.daysTo(currentDateTime);

    return dayOffset;

}

bool SearchParameters::buildSQLQueryForSearch(QVector<int> arrayOfDayOffsetForSearch){

    if (searchParametersForMySQLquery.size() == 0) {
          return false;
      } else {

      QString mysqlQueryForSearchInEWSD;
      QString mysqlQueryForSearchInAPUS;

      mysqlQueryForSearchInAPUS.clear();
      mysqlQueryForSearchInEWSD.clear();

      QStringList startCountDayTempList = this->getSearchValuesByKey("startSearchDateTimeForMySQL");
      QString startCountDayStr = startCountDayTempList.at(0);
      int startCountDayNumber = startCountDayStr.toInt();
      QDateTime startDateTime = QDateTime(QDateTime::fromTime_t(startCountDayNumber));

      QStringList endCountDayTempList = this->getSearchValuesByKey("endSearchDateTimeForMySQL");
      QString endCountDayStr = endCountDayTempList.at(0);
      int endCountDayNumber = endCountDayStr.toInt();
      QDateTime endDateTime = QDateTime(QDateTime::fromTime_t(endCountDayNumber));

      QDateTime currDateTime = QDateTime(QDateTime::currentDateTime());

      int startCountDay = 0;
      startCountDay = startDateTime.daysTo(currDateTime);
      //startCountDay = config.getParameters().value("countDaysAgoFrom").toInt();

      int endCountDay  = 0;
      endCountDay = endDateTime.daysTo(currDateTime);
      //endCountDay = config.getParameters().value("countDaysAgoTo").toInt();

      if ( this->getSearchValueByKey("selectInSmallAPUSTables",0) == "true" ){

      QString apusSearchParameters = this->addSearchParametersToSQLQuery("APUS");        

      for ( int i = 0; i < arrayOfDayOffsetForSearch.size(); i++ ){

          QDateTime dateTime = QDateTime(QDateTime::currentDateTime()).addDays(arrayOfDayOffsetForSearch.at(i));

          mysqlQueryForSearchInAPUS = "SELECT IF( LENGTH(a_id)=7, CONCAT(\"8016\",a_id), CONCAT(\"80\",a_id)) phoneNumberA,";
          mysqlQueryForSearchInAPUS.append(" nabor phoneNumberB,");
          mysqlQueryForSearchInAPUS.append(" IF ( dlit > 0, 1 , 0 ) answer,");
          mysqlQueryForSearchInAPUS.append(" CONCAT(");
          mysqlQueryForSearchInAPUS.append("\'");
          mysqlQueryForSearchInAPUS.append(dateTime.toString("yyyy-MM-dd"));
          mysqlQueryForSearchInAPUS.append("\',\'T\'");
          mysqlQueryForSearchInAPUS.append(", t ) dateTimeOfCall, dlit callDuration");
          mysqlQueryForSearchInAPUS.append(" FROM cs.t");
          mysqlQueryForSearchInAPUS.append(dateTime.toString("yyyyMMdd"));
        //mysqlQueryForSearchInAPUS.append("\n");

          if ( this->getSearchValueByKey("selectALL",0) == "false" ){

              mysqlQueryForSearchInAPUS.append(" WHERE ( ");
              mysqlQueryForSearchInAPUS.append(apusSearchParameters);
              mysqlQueryForSearchInAPUS.append(" ) ");
          }

          mysqlQueryForSearchInAPUS.append(" ORDER BY t ");

          readySQLQuerysForSearchInAPUSdb.push_back(mysqlQueryForSearchInAPUS);

          apusDBTables.push_back(QString("t")+dateTime.toString("yyyyMMdd"));

      }

      }

      if ( this->getSearchValueByKey("selectInSingleBigEWSDTable",0) == "true" ){

          QString ewsdSearchParameters = this->addSearchParametersToSQLQuery("EWSD");

          mysqlQueryForSearchInEWSD = " SELECT DISTINCT amaR.phoneNumberA, amaR.phoneNumberB, amaR.answer,";
          mysqlQueryForSearchInEWSD.append(QString("\n"));
  //      mysqlQueryForSearchInEWSD.append(QString(" DATE_FORMAT(FROM_UNIXTIME(datetime_unix),'\%T \%d-\%m-\%Y') dateTimeUnix,"));
          mysqlQueryForSearchInEWSD.append(QString(" amaR.datetime_unix, amaR.callDuration"));
          mysqlQueryForSearchInEWSD.append(QString(" FROM amarecord amaR"));
          mysqlQueryForSearchInEWSD.append(QString("\n"));
          mysqlQueryForSearchInEWSD.append(QString(" USE INDEX(PhoneA_PhoneB) USE INDEX(PhoneB)"));
          mysqlQueryForSearchInEWSD.append(QString(",amafiles amaF"));
          mysqlQueryForSearchInEWSD.append(QString("\n"));
          mysqlQueryForSearchInEWSD.append(QString(" WHERE ( "));
          mysqlQueryForSearchInEWSD.append(ewsdSearchParameters);
          mysqlQueryForSearchInEWSD.append(QString(" ) "));
          mysqlQueryForSearchInEWSD.append(QString(" AND (LENGTH(amaF.dateFileName)>0) AND (amaR.idFileName=amaF.Id)"));
          mysqlQueryForSearchInEWSD.append(QString(" AND amaF.FullPathToFile LIKE \"%ATS%\""));
          mysqlQueryForSearchInEWSD.append(QString("\n"));
          mysqlQueryForSearchInEWSD.append(QString(" ORDER BY datetime_unix "));

          readySQLQuerysForSearchInEWSDdb.push_back(mysqlQueryForSearchInEWSD);

          ewsdDBTables.push_back(QString("amarecord"));

          }

      if ( this->getSearchValueByKey("selectInSmallEWSDTables",0) == "true" ){

      QString ewsdSearchParameters = this->addSearchParametersToSQLQuery("EWSD");

          for ( int i = 0; i < arrayOfDayOffsetForSearch.size(); i++ ){

          QDateTime dateTime = QDateTime(QDateTime::currentDateTime()).addDays(arrayOfDayOffsetForSearch.at(i));
          mysqlQueryForSearchInEWSD = " SELECT DISTINCT phoneNumberA, phoneNumberB, answer,";
          mysqlQueryForSearchInEWSD.append(QString("\n"));
  //      mysqlQueryForSearchInEWSD.append(QString(" DATE_FORMAT(FROM_UNIXTIME(datetime_unix),'\%T \%d-\%m-\%Y') dateTimeUnix,"));
          mysqlQueryForSearchInEWSD.append(QString(" datetime_unix, callDuration"));
          mysqlQueryForSearchInEWSD.append(QString(" FROM amarecord_"));
          mysqlQueryForSearchInEWSD.append(dateTime.toString("yyyyMMdd"));
          mysqlQueryForSearchInEWSD.append(QString("\n"));
          mysqlQueryForSearchInEWSD.append(QString(" USE INDEX(PhoneA_PhoneB) USE INDEX(PhoneB)"));
          mysqlQueryForSearchInEWSD.append(QString("\n"));

          if ( this->getSearchValueByKey("selectALL",0) == "false" ){

          mysqlQueryForSearchInEWSD.append(QString(" WHERE ( "));
          mysqlQueryForSearchInEWSD.append(ewsdSearchParameters);
          mysqlQueryForSearchInEWSD.append(QString(" ) "));

          }

          mysqlQueryForSearchInEWSD.append(QString(" ORDER BY datetime_unix "));

          readySQLQuerysForSearchInEWSDdb.push_back(mysqlQueryForSearchInEWSD);

          ewsdDBTables.push_back(QString("amarecord_")+dateTime.toString("yyyyMMdd"));

          }

          }

  }
          return true;

}


bool SearchParameters::buildSQLQueryForLoadDataInDB(Config config){
    return true;
}

uint SearchParameters::getCountReadySQLQuerys(){
    return readySQLQuerysForSearchInAPUSdb.size();
}

QVector<QString> SearchParameters::getReadySQLQuerysForSearchInAPUSdb(){
    return readySQLQuerysForSearchInAPUSdb;
}

QVector<QString> SearchParameters::getReadySQLQuerysForSearchInEWSDdb(){
    return readySQLQuerysForSearchInEWSDdb;
}
