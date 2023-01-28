
-- 1355. Activity Participants
-- https://leetcode.com/problems/activity-participants/


/* Write your T-SQL query statement below */


with cte (activity,mxrnk,mnrnk)
as
(
select
  t.activity,
  rank() over(order by t.cnt desc) as mxrnk,
  rank() over(order by t.cnt) as mnrnk
from (
    select
      activity,
      count(*) as cnt
    from
      friends
    group by
      activity
  ) t
)
select
  activity
from
  cte
where
  activity not in (select activity from cte where mxrnk = 1) and
  activity not in (select activity from cte where mnrnk = 1)
