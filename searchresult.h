#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <callinformation.h>
#include <searchparameters.h>
#include <QApplication>
#include <algorithm>
#include <QString>
#include <QMap>
#include <QVector>

class SearchResult
{
private:
    QVector<CallInformation> arrayOfSearchResult;
    QVector<CallInformation>::iterator arrayOfSearchResultIter;
    QMap<QString,int> uniqueArrayOfSearchResult;
    QMap<QString,int>::iterator uniqueArrayOfSearchResultIt;
    QVector<CallInformation> readySearchResult;
    QVector<CallInformation>::iterator readySearchResultIt;
public:
    SearchResult();
    QVector<CallInformation> getArrayOfSearchResult();
    void setArrayOfSearchResult(QVector<CallInformation> searchResults);
    void setNewCallInfo(CallInformation callInfo);
    bool static compare(CallInformation callInfo1, CallInformation callInfo2 );
    void sortArrayOfSearchResultByDateTimeUnix();
    void initUniqueArrayOfSearchResult();
    QVector<CallInformation> getReadySearchResult();
    void sortReadySearchResultByDateTimeUnix();
    QString getResultFileName(SearchParameters searchParameters);





};

#endif // SEARCHRESULT_H
