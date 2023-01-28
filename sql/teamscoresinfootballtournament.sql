
-- 1212. Team Scores in Football Tournament
-- https://leetcode.com/problems/team-scores-in-football-tournament/



/* Write your T-SQL query statement below */

with match_points
as
(
select
  host_team as team_id,
  case
    when host_goals > guest_goals then 3
    when host_goals = guest_goals then 1 else 0
  end as points
from
  matches
union all
select
  guest_team as team_id,
  case
    when guest_goals > host_goals then 3
    when guest_goals = host_goals then 1 else 0
  end as points
from
  matches
),
team_points
as
(
select
  mp.team_id,
  sum(mp.points) as num_points
from
  match_points mp join teams t on mp.team_id = t.team_id
group by
  mp.team_id
)
select
  t.team_id,
  t.team_name,
  isnull(tp.num_points,0) as num_points
from
  teams t left join team_points tp on t.team_id = tp.team_id
order by
  isnull(tp.num_points,0) desc, t.team_id asc
