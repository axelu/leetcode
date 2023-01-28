
-- 1141. User Activity for the Past 30 Days I
-- https://leetcode.com/problems/user-activity-for-the-past-30-days-i/




/* Write your T-SQL query statement below */

select
  activity_date as day
  ,count(distinct user_id) as active_users
from
  activity
where
  -- activity_date >= dateadd(day,-29,'2019-07-27') and activity_date <= '2019-07-27'
  activity_date between dateadd(day,-29,'2019-07-27') and '2019-07-27'
group by
  activity_date
