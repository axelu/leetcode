
-- 3436. Find Valid Emails
-- https://leetcode.com/problems/find-valid-emails/




/* Write your T-SQL query statement below */


select
    user_id,
    email
from
    Users
where
    len(email) >= 7 and
    substring(email, len(email) - 3, 4) = '.com' and
    ( CHARINDEX('@', email, 1) > 1 and CHARINDEX('@', email, CHARINDEX('@', email, 1)+1) = 0 ) and
    substring(email, CHARINDEX('@', email, 1)+1, 1) LIKE '[a-zA-Z]' and
    substring(email, 1, CHARINDEX('@', email, 1)-1) NOT LIKE '%[^a-zA-Z0-9_]%'
