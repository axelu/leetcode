
-- 1517. Find Users With Valid E-Mails
-- https://leetcode.com/problems/find-users-with-valid-e-mails/


/* Write your T-SQL query statement below */


-- printable special chars !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ SPACE
-- allowed in left part based on problem description besides A-Za-z0-9: _.-
select *
from users
where
  len(mail) > 13
  and right(mail,13) = '@leetcode.com'
  and left(mail,1) like '[A-Z]'
  and left(mail,len(mail)-13) not like '%[^A-Z0-9_.-]%'
