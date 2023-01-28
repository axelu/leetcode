
-- 2175. The Change in Global Rankings
-- https://leetcode.com/problems/the-change-in-global-rankings/



/* Write your T-SQL query statement below */

with a
as
(
select
  team_id,
  name,
  points,
  rank() over(order by points desc,name) as rnk
from
  teampoints
),
b
as
(
select
  t.team_id,
  t.name,
  t.points,
  p.points_change,
  rank() over(order by (t.points+p.points_change) desc,t.name) as rnk
from
  teampoints t join pointschange p on t.team_id = p.team_id
)
select
  a.team_id,
  a.name,
  a.rnk-b.rnk as rank_diff
from
  a join b on a.team_id = b.team_id
