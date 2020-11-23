#include "file.h"

File::File()
{
}

QString File::getAbsoluteATS20AMAFilePathByDateFileName(QString pathToAMAFiles,QString dateFilename){

    QString  readyAbsoluteFilePath = NULL;

    readyAbsoluteFilePath = pathToAMAFiles;
  //readyAbsoluteFilePath = secondPathToAMAFiles;
    readyAbsoluteFilePath.append("ATS20");
    readyAbsoluteFilePath.append("\\");
    readyAbsoluteFilePath.append(dateFilename.mid(0,4));
    readyAbsoluteFilePath.append("\\");
    readyAbsoluteFilePath.append(dateFilename.mid(5,2));
    readyAbsoluteFilePath.append(dateFilename.mid(2,2));
    readyAbsoluteFilePath.append("\\");
    readyAbsoluteFilePath.append(dateFilename.mid(8,2));
    readyAbsoluteFilePath.append(".ama");

    return readyAbsoluteFilePath;
}

quint32 File::getFileNameLastHourModifiedByDate(QString date){

    QString   readyFileNameForGetInfo = NULL;
    QString pathToAMAFiles;
    readyFileNameForGetInfo = getAbsoluteATS20AMAFilePathByDateFileName(pathToAMAFiles,date);
    QFileInfo InfoAboutCurrentFile(readyFileNameForGetInfo);
    int hour = InfoAboutCurrentFile.lastModified().time().hour();
    return hour;
}

QDate File::getLastDateModifiedOfAMAFile(QString AMAFileName){

    QFileInfo InfoAboutCurrentAMAFile(AMAFileName);
    return InfoAboutCurrentAMAFile.lastModified().date();

}

QString File::getStringDateOfCreateOfAMAFile(QString AMAFileName, QString format){

    QFileInfo InfoAboutCurrentAMAFile(AMAFileName);
    return InfoAboutCurrentAMAFile.created().date().toString(format);

}

QString File::getLastStringDateModifiedOfAMAFile(QString AMAFileName, QString format){

    QFileInfo InfoAboutCurrentAMAFile(AMAFileName);
    return InfoAboutCurrentAMAFile.lastModified().date().toString(format);

}

QString File::getFileNameFromFullPathToAMAFile(QString AMAFileName){

    QFileInfo InfoAboutCurrentAMAFile(AMAFileName);
    return InfoAboutCurrentAMAFile.fileName();
}

QString File::getBaseNameFromFullPathToAMAFile(QString AMAFileName){

    QFileInfo InfoAboutCurrentAMAFile(AMAFileName);
    QString baseName = InfoAboutCurrentAMAFile.baseName();
    QString completeSuffix = InfoAboutCurrentAMAFile.completeSuffix();

    int posOfStrTARIF = InfoAboutCurrentAMAFile.fileName().indexOf("tarif.",0,Qt::CaseInsensitive);

    if ( posOfStrTARIF < 0 ){

        posOfStrTARIF = InfoAboutCurrentAMAFile.fileName().indexOf("TARIF.",0,Qt::CaseInsensitive);

    }

    if ( posOfStrTARIF >=0 ){

    QString dateFileName = "";
    QString fileName = QString(InfoAboutCurrentAMAFile.fileName());
    QString letter = "";

    int thirdPosOfDot = getIndexPositionSubstr(fileName,".",3);
    int fourthPosOfDot = getIndexPositionSubstr(fileName,".",4);

    dateFileName = fileName.mid(posOfStrTARIF+6,thirdPosOfDot-posOfStrTARIF-6);
    if ( fourthPosOfDot > 0) {
         letter = fileName.mid(thirdPosOfDot+1,fourthPosOfDot-thirdPosOfDot-1);
    }

    if ( letter.length() != 0 ){
         letter = getNextLetterByCodeLetter(letter.toInt());
    }
         QString readyDateFileName = "20" + dateFileName.mid(0,4) + dateFileName.mid(5,2);
         return  readyDateFileName + letter + ".ama";
    }

    if ( baseName.mid(0,1) == "B" || baseName.mid(0,1) == "P" ) {
       int lengthBaseName = baseName.length();
       baseName = baseName.mid(1,lengthBaseName-1);
    }

    return baseName + "." + completeSuffix;

}

QString File::getDateFileNameByFullPathAMAFile(QString fileName, QString format){

    QString ats_name;
    QString baseFileName;
    QString dateFileName;

    if ( fileName.indexOf("ATS",0 ) >=0){
        ats_name = fileName.mid(fileName.indexOf("ATS",0),5);
    } else if ( fileName.indexOf("BarEWSD",0) >=0 ){
        ats_name = fileName.mid(fileName.indexOf("BarEWSD",0),7);
    } else if ( fileName.indexOf("PinEWSD",0) >= 0){
        ats_name = fileName.mid(fileName.indexOf("PinEWSD",0),7);
    }

    baseFileName = getBaseNameFromFullPathToAMAFile(fileName);

    if ( fileName.indexOf("ATS20",0)>0 )
    {
        QString yyyy = fileName.mid(fileName.indexOf("ATS20",0)+6,4);
        QString MM = fileName.mid(fileName.indexOf("ATS20",0)+11,2);
        QString dd = fileName.mid(fileName.indexOf("ATS20",0)+16,2);
        dateFileName = yyyy+MM+dd;
    }

    if ( fileName.indexOf("ATS20",0)>0 )
    {
        dateFileName = QDate::fromString(dateFileName,"yyyyMMdd").toString(format);
    }
    else
        dateFileName = QDate::fromString(baseFileName.mid(0,8),"yyyyMMdd").toString(format);

    return dateFileName;

}

QString File::getLetterFromBaseName(QString baseName){

    if ( baseName.length() !=0 && baseName != "BARAN" && baseName != "TARIF"  ) {
        QString checkedSymbol = baseName.right(1);
        QRegExp regExpr("\\D");
        if (regExpr.exactMatch(checkedSymbol))
        return checkedSymbol;
        else return "";
    }   else return "";
}

int File::getCodeOfLetter(QString letter){

    return QString(letter).at(0).toLatin1();
}

QString File::getNextLetterByCodeLetter(int numberFromFileName){

    int codeOfLetterA = QString("A").at(0).toLatin1();
//  int codeOfLetterB = QString("B").at(0).toAscii();
//  QChar Letter = QChar(codeOfLetterA+numberFromFileName-1);
    return QString(QChar(codeOfLetterA+numberFromFileName-1));

}

int File::getIndexPositionSubstr(QString str, QString substr, int indexNumber){

    if ( indexNumber <= 1 ) {
      return str.indexOf( substr,0,Qt::CaseInsensitive );
    } else if ( str.indexOf( substr,0,Qt::CaseInsensitive ) >=0 ) {
      int currIndex = 0;
      int currIndexOf = 0;
          while ( ( currIndex != indexNumber )  ) {
             currIndexOf = str.indexOf( substr,currIndexOf+1,Qt::CaseInsensitive );
             if ( currIndexOf < 0 ) {
                 return currIndexOf;
             }
             currIndex++;
          }
      return currIndexOf;
    } else return -1;

}

int File::countSubDirsByAbsolutePath(QString rootDir){

    QDirIterator it(rootDir, QDirIterator::Subdirectories);
    int count = 0;
    while(it.hasNext()) {
        count++;
    }

    return count;

}

bool File::isRootAMAStationDir(QString absolutePath){

    QString completeBaseName = QFileInfo(absolutePath).completeBaseName();
    QStringList atsDirNames = QStringList();
    atsDirNames << "ATS20" << "ATS21" << "ATS40" << "ATS46" << "BarEWSD" << "PinEWSD";
    if ( atsDirNames.contains(completeBaseName,Qt::CaseInsensitive) )
    return true;
    else return false;
}

bool File::isAMAFile(QString absolutePath){

    // QFileInfo fileInfo = QFileInfo(absolutePath);
    // if ( ( absolutePath.indexOf("ama",0,Qt::CaseInsensitive)>=0 ) && ( absolutePath.indexOf("AMA._ok_",0,Qt::CaseInsensitive)<0 ) )

    if ( ( absolutePath.indexOf("ok") >=0 ) || ( absolutePath.indexOf("OK") >= 0 ) ) return false;

    if ((( absolutePath.indexOf(".ama") > 0 ) || ( absolutePath.indexOf(".AMA") > 0 ) ) && ( absolutePath.indexOf("ok") < 0 ) && ( absolutePath.indexOf("OK") < 0 ))
       return true;
       else return false;

}

bool File::isBrestATS(QString absolutePath){

    if ( ( absolutePath.indexOf("BarEWSD",0,Qt::CaseInsensitive) < 0 ) && ( absolutePath.indexOf("PinEWSD",0,Qt::CaseInsensitive) < 0 )  ){
        return true;
    }
    else { return false; }
}

bool File::isATSFolder(QString absolutePath, QString atsName){

    if (  absolutePath.indexOf(atsName,0,Qt::CaseInsensitive) >= 0 ){
        return true;
    }
    else { return false; }
}

QString File::getPathBySubDir(QString absolutePath, QString subDir){

    if ( subDir != ""){
      QString path = absolutePath.mid(0,absolutePath.indexOf(subDir,0,Qt::CaseInsensitive)+subDir.length());
      if (QDir(path).exists())
      return path;
      else return "";
    } else return "";

}

QString File::getAtsName(QString fileName){

    int posATSStr = fileName.indexOf("ATS");
    if ( posATSStr>=0 )
        return fileName.mid(posATSStr,5);
    else {
    int posATSStr = fileName.indexOf("EWSD");
    return fileName.mid(posATSStr-3,7);
}

}



