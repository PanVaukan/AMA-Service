#include "datagenerator.h"

DataGenerator::DataGenerator()
{
}

CallInformation DataGenerator::getGeneratedData(int minDayOffset, int maxDayOffset){

        CallInformation callInfo;
        RandomGenerator randomGenerator;

        quint8 generatedAnswer = 0;
        quint64 minPhoneNumber = 80162200000;
        quint64 maxPhoneNumber = 80165599999;

        int minCallDuration = 0;
        int maxCallDuration = 1800;
        quint32 generatedCallDuration = 0;

        QDateTime currentDateTimeUnix = QDateTime::currentDateTime();

//      int minDayOffset = -2000;
//      int maxDayOffset = 0;

        uint minDateTimeUnix = (currentDateTimeUnix.addDays(minDayOffset).toTime_t());
        uint maxDateTimeUnix = (currentDateTimeUnix.addDays(maxDayOffset).toTime_t());
        maxDateTimeUnix = maxDateTimeUnix - 1;

//      QTime midnight(0,0,0);
//      qsrand(midnight.secsTo(QTime::currentTime()));
//      uint generatedDateTimeUnix = qrand() % ((maxDateTimeUnix + 1) - minDateTimeUnix ) + minDateTimeUnix;
//      uint generatedDateTimeUnix = randomGenerator.randomBetween(minDateTimeUnix,maxDateTimeUnix,QDateTime::currentMSecsSinceEpoch());
        uint generatedDateTimeUnix = RandomCpp11Generator::get(minDateTimeUnix,maxDateTimeUnix);

//      QDateTime checkGeneratedDateTimeUnix = QDateTime::fromTime_t(generatedDateTimeUnix);

//      qulonglong generatedPhoneNumberA = qrand()%(maxPhoneNumber-minPhoneNumber + 1) + minPhoneNumber;
//      qulonglong generatedPhoneNumberA = randomGenerator.randomBetween(minPhoneNumber,maxPhoneNumber,QDateTime::currentMSecsSinceEpoch());
        qulonglong generatedPhoneNumberA = RandomCpp11Generator::get(minPhoneNumber,maxPhoneNumber);
//      qulonglong generatedPhoneNumberB = qrand()%(maxPhoneNumber-minPhoneNumber + 1) + minPhoneNumber;
//      qulonglong generatedPhoneNumberB = randomGenerator.randomBetween(minPhoneNumber,maxPhoneNumber,QDateTime::currentMSecsSinceEpoch());
        qulonglong generatedPhoneNumberB = RandomCpp11Generator::get(minPhoneNumber,maxPhoneNumber);


        int randomNumber = qrand();
        int rest = randomNumber % 2;
        if ( rest == 0 ){
             generatedAnswer = 0;
             generatedCallDuration = 0;
        } else {
            generatedAnswer = 1;
//          generatedCallDuration = qrand()%(maxCallDuration-minCallDuration + 1) + minCallDuration;
//          generatedCallDuration = randomGenerator.randomBetween(minCallDuration,maxCallDuration,QDateTime::currentMSecsSinceEpoch());
            generatedCallDuration = RandomCpp11Generator::get(minCallDuration,maxCallDuration);
            if ( generatedCallDuration == 0 ) generatedCallDuration = 1800;
        }

        QString phoneA = QString::number(generatedPhoneNumberA);
        QString phoneB = QString::number(generatedPhoneNumberB);

        callInfo.setAbonFields(phoneA,phoneB,generatedAnswer,generatedCallDuration,generatedDateTimeUnix);

        return callInfo;

}
