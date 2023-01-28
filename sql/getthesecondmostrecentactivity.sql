
-- 1369. Get the Second Most Recent Activity
-- https://leetcode.com/problems/get-the-second-most-recent-activity/



/* Write your T-SQL query statement below */

-- A user cannot perform more than one activity at the same time.
-- assume hence that startDate > endDate between rows marks order

with activity_ranked
as
(
select
  username,
  activity,
  startDate,
  endDate,
  rank() over(partition by username order by enddate desc) as rnk
from
  useractivity
)
select
  username,
  activity,
  startDate,
  endDate
from
  activity_ranked
where
  rnk = 2
union
select
  username,
  activity,
  startDate,
  endDate
from
  activity_ranked
where
  rnk = 1 and
  username not in (select distinct username from activity_ranked where rnk = 2)

