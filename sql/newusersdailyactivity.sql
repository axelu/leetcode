
-- 1107. New Users Daily Count
-- https://leetcode.com/problems/new-users-daily-count/



/* Write your T-SQL query statement below */

with rankedlogins
as
(
select distinct
  user_id,
  activity_date,
  rank() over(partition by user_id order by activity_date) as rnk
from
  traffic
where
  activity = 'login'
)
select
  activity_date as login_date,
  count(*) as user_count
from
  rankedlogins
where
  activity_date >= dateadd(day,-90,'2019-06-30') and
  rnk = 1
group by
  activity_date
