

DELETE vpn_tmp.t_correct.* FROM vpn_tmp.t_correct, vpn_tmp.t_dot
WHERE ( vpn_tmp.t_correct.ID_DOT = vpn_tmp.t_dot.ID_DOT )
AND vpn_tmp.t_dot.ID_DOT IN (SELECT td.ID_DOT FROM vpn_tmp.t_dot td
INNER JOIN vpn_tmp.t_dog td1 ON ( td.ID_DOG = td1.ID_DOG )
WHERE td1.AB_CODE = 2200015);





