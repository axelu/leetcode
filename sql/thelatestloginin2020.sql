
-- 1890. The Latest Login in 2020
-- https://leetcode.com/problems/the-latest-login-in-2020/


/* Write your T-SQL query statement below */

select
  user_id,
  max(time_stamp) as last_stamp
from logins
where datepart(year,time_stamp) = 2020
group by user_id
