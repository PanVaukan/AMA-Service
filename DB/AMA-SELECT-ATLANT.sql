

TRUNCATE TABLE ama.amarecord_small;

INSERT INTO ama.amarecord_small(phoneNumberA,phoneNumberB,datetime_unix,callDuration,answer,offset,idFileName)
SELECT a.phoneNumberA,
REPLACE(a.phoneNumberB,SUBSTRING(a.phoneNumberB,LOCATE('E',a.phoneNumberB),3),'0') phoneNumberB,
a.datetime_unix, MIN(a.callDuration),a.answer,a.offset,a.idFileName
FROM ama.amarecord a, ama.amarecord b
WHERE ( a.phoneNumberB = '80162424242' OR a.phoneNumberB = '424242' )
AND	a.datetime_unix>=unix_timestamp(CONCAT("2017-03-25"," ","00:00:00"))
AND a.datetime_unix<=unix_timestamp(CONCAT("2017-04-04"," ","00:00:00"))
AND a.phoneNumberA = b.phoneNumberA AND a.phoneNumberB = b.phoneNumberB
AND a.datetime_unix = b.datetime_unix 
AND (CAST(a.callDuration AS SIGNED)-CAST(b.callDuration AS SIGNED)) <= 1
GROUP BY a.phoneNumberA,phoneNumberB,a.datetime_unix;


SELECT DISTINCT a.phoneNumberA,
REPLACE(a.phoneNumberB,SUBSTRING(a.phoneNumberB,LOCATE('E',a.phoneNumberB),3),'0') phoneNumberB,
MIN(FROM_UNIXTIME(a.datetime_unix)) min_datetime_unix, a.callDuration, a.answer, a.offset, a.idFileName
FROM ama.amarecord_small a, ama.amarecord_small b
WHERE ( a.phoneNumberB = '80162424242' OR a.phoneNumberB = '424242' )
AND	a.datetime_unix>=unix_timestamp(CONCAT("2017-03-25"," ","00:00:00"))
AND a.datetime_unix<=unix_timestamp(CONCAT("2017-04-04"," ","00:00:00"))
AND a.phoneNumberA = b.phoneNumberA AND a.phoneNumberB = b.phoneNumberB
AND a.datetime_unix = b.datetime_unix 
AND (CAST(a.datetime_unix AS SIGNED)-CAST(b.datetime_unix AS SIGNED)) <= 1
GROUP BY a.phoneNumberA,a.phoneNumberB,a.callDuration
ORDER BY min_datetime_unix;

CREATE TEMPORARY TABLE ama.amarecord_small_res LIKE ama.amarecord_small;

INSERT INTO ama.amarecord_small_res (phoneNumberA,phoneNumberB,datetime_unix,callDuration,answer,offset,idFileName)
SELECT DISTINCT a.phoneNumberA,
REPLACE(a.phoneNumberB,SUBSTRING(a.phoneNumberB,LOCATE('E',a.phoneNumberB),3),'0') phoneNumberB,
MIN(a.datetime_unix) min_datetime_unix, a.callDuration, a.answer, a.offset, a.idFileName
FROM ama.amarecord_small a, ama.amarecord_small b
WHERE ( a.phoneNumberB = '80162424242' OR a.phoneNumberB = '424242' )
AND	a.datetime_unix>=unix_timestamp(CONCAT("2017-03-25"," ","00:00:00"))
AND a.datetime_unix<=unix_timestamp(CONCAT("2017-04-04"," ","00:00:00"))
AND a.phoneNumberA = b.phoneNumberA AND a.phoneNumberB = b.phoneNumberB
AND a.datetime_unix = b.datetime_unix 
AND (CAST(a.datetime_unix AS SIGNED)-CAST(b.datetime_unix AS SIGNED)) <= 1
GROUP BY a.phoneNumberA,a.phoneNumberB,a.callDuration
ORDER BY min_datetime_unix;

SELECT DISTINCT CONCAT(amaF.dateFileName,' && ',amaF.FullPathToFile,' && ',amaF.FileName),
amaR.phoneNumberA,amaR.phoneNumberB,
amaR.callDuration, amaR.offset, FROM_UNIXTIME(amaR.datetime_unix), amaF.ats_name
FROM ama.amarecord_small_res amaR IGNORE INDEX(datetime_unix),ama.amafiles amaF
WHERE ( ( amaR.phoneNumberB = '80162424242' OR amaR.phoneNumberB = '424242' )
AND	amaR.datetime_unix>=unix_timestamp(CONCAT("2017-03-25"," ","00:00:00"))
AND amaR.datetime_unix<=unix_timestamp(CONCAT("2017-04-04"," ","00:00:00")))
-- AND ( amaR.phoneNumberB NOT LIKE "%E%" )
AND (LENGTH(amaF.dateFileName)>0) AND (amaR.idFileName=amaF.Id)
ORDER BY amaR.datetime_unix, amaR.offset;

SELECT FROM_UNIXTIME(asr.datetime_unix),asr.phoneNumberA,asr.phoneNumberB, asr.callDuration
FROM ama.amarecord_small_res asr
ORDER BY asr.datetime_unix;

DROP TEMPORARY TABLE ama.amarecord_small_res;


