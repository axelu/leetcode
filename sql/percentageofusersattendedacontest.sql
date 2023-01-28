
-- 1633. Percentage of Users Attended a Contest
-- https://leetcode.com/problems/percentage-of-users-attended-a-contest/



/* Write your T-SQL query statement below */

declare @tot_users int;
set @tot_users = (select count(*) from users);

select
  contest_id,
  round(cast(count(*) as decimal)/@tot_users*100,2) as percentage
from
  register
group by contest_id
order by percentage desc, contest_id
