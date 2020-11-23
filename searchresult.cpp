#include "searchresult.h"

#include <QTextCodec>

SearchResult::SearchResult()
{
}

QVector<CallInformation> SearchResult::getArrayOfSearchResult(){
    return arrayOfSearchResult;
}

void SearchResult::setArrayOfSearchResult(QVector<CallInformation> searchResults){
    arrayOfSearchResult = searchResults;
}

void SearchResult::setNewCallInfo(CallInformation callInfo){
    arrayOfSearchResult.push_back(callInfo);
}

bool SearchResult::compare(CallInformation callInfo1, CallInformation callInfo2){

    if (callInfo1.getDateTimeUnix() < callInfo2.getDateTimeUnix())
         return true;
    else return false;

}

void SearchResult::sortArrayOfSearchResultByDateTimeUnix(){

//  std::sort(arrayOfSearchResult.begin(), arrayOfSearchResult.end(), EntityComp("SORT"));
    std::sort(arrayOfSearchResult.begin(), arrayOfSearchResult.end(), compare );

}

void SearchResult::initUniqueArrayOfSearchResult(){

//   uniqueArrayOfSearchResult.setInsertInOrder(true);

     arrayOfSearchResultIter = arrayOfSearchResult.begin();

     while ( arrayOfSearchResultIter != arrayOfSearchResult.end() ){
             int maxID = uniqueArrayOfSearchResult.size();
             int nextID = maxID + 1;

             CallInformation callInfo;
             callInfo = *arrayOfSearchResultIter;

             QString allDataInOneStr;
             allDataInOneStr = callInfo.getPhoneNumberA();
             allDataInOneStr.append(";");
             allDataInOneStr.append(callInfo.getPhoneNumberB());
             allDataInOneStr.append(";");
             allDataInOneStr.append(QString::number(callInfo.getAnswer()));
             allDataInOneStr.append(";");
             allDataInOneStr.append(QString::number(callInfo.getCallDuration()));
             allDataInOneStr.append(";");
             allDataInOneStr.append(QString::number(callInfo.getDateTimeUnix()));
             allDataInOneStr.append(";");

             uniqueArrayOfSearchResult.insert(allDataInOneStr,nextID);

             arrayOfSearchResultIter++;
     }

}

QVector<CallInformation> SearchResult::getReadySearchResult(){

    QStringList callInfoFields;
    CallInformation callInfo;

    uniqueArrayOfSearchResultIt = uniqueArrayOfSearchResult.begin();

    while ( uniqueArrayOfSearchResultIt != uniqueArrayOfSearchResult.end() ){

            callInfoFields = QString(uniqueArrayOfSearchResultIt.key()).split(";");

            for (int countValues = 0; countValues < callInfoFields.size(); countValues++){

                switch (countValues){

                case 0:
                        callInfo.setPhoneNumberA(callInfoFields.at(countValues));
                        break;
                case 1:
                        callInfo.setPhoneNumberB(callInfoFields.at(countValues));
                        break;
                case 2:
                        callInfo.setAnswer(QString(callInfoFields.at(countValues)).toUInt());
                        break;
                case 3:
                        callInfo.setCallDuration(QString(callInfoFields.at(countValues)).toUInt());
                        break;
                case 4:
                        callInfo.setDateTimeUnix(QString(callInfoFields.at(countValues)).toUInt());
                        break;

                default:

                        break;
                }

            }

            readySearchResult.push_back(callInfo);

            uniqueArrayOfSearchResultIt++;
    }

    this->sortReadySearchResultByDateTimeUnix();

    return readySearchResult;

}

void SearchResult::sortReadySearchResultByDateTimeUnix(){

//   std::sort(readySearchResult.begin(), readySearchResult.end(), EntityComp("SORT"));
     std::sort(readySearchResult.begin(), readySearchResult.end(), compare );

}

QString SearchResult::getResultFileName(SearchParameters searchParameters){

    QTextCodec * codec;
    codec = QTextCodec::codecForName("UTF-8");

    QString resultFileName;
    resultFileName = QApplication::applicationDirPath();
    resultFileName.append(QString("/"));

    if (searchParameters.getSearchParametersForMySQLquery().contains("phoneNumberA")){
        resultFileName.append(QString(QObject::trUtf8("Outgoing_calls")));
        resultFileName.append(QString("_from_number_"));
        resultFileName.append(searchParameters.getSearchValueByKey("phoneNumberA",0));
    }
    if (searchParameters.getSearchParametersForMySQLquery().contains("phoneNumberB")){
        if ( resultFileName.contains("Outgoing_calls")) {
             resultFileName.append("_");
        }
        resultFileName.append(QString("Incoming calls"));
        resultFileName.append(QString("_to_number_"));
        resultFileName.append(searchParameters.getSearchValueByKey("phoneNumberB",0));
    }

    resultFileName.append(QString(".csv"));

    return resultFileName;

}


