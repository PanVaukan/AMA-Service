
UPDATE vpn_tmp.t_abon ta, vpn_tmp.t_abon ta1
SET ta.T_ABON_NE_DATE = ta1.T_ABON_NE_DATE, ta.T_ABON_NAME = ta1.T_ABON_NAME,
    ta.T_ABON_NOTE = ta1.T_ABON_NOTE, ta.T_ABON_USER_ID = ta1.T_ABON_USER_ID 
WHERE ta.AB_CODE = 2212488 AND ta1.AB_CODE = 388;

