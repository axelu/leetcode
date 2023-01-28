
-- 1841. League Statistics
-- https://leetcode.com/problems/league-statistics/



/* Write your T-SQL query statement below */

with match_stats
as
(
select
  home_team_id as team_id,
  case
    when home_team_goals > away_team_goals then 3
    when home_team_goals = away_team_goals then 1 else 0
  end as points,
  home_team_goals as goal_for,
  away_team_goals as goal_against
from
  matches
union all
select
  away_team_id as team_id,
  case
    when away_team_goals > home_team_goals then 3
    when away_team_goals = home_team_goals then 1 else 0
  end,
  away_team_goals,
  home_team_goals
from
  matches
),
team_stats
as
(
select
  ms.team_id,
  count(*) as matches_played,
  sum(ms.points) as points,
  sum(ms.goal_for) as goal_for,
  sum(ms.goal_against) as goal_against,
  sum(ms.goal_for) - sum(ms.goal_against) as goal_diff
from
  match_stats ms join teams t on ms.team_id = t.team_id
group by
  ms.team_id
)
select
  -- t.team_id,
  t.team_name,
  ts.matches_played as matches_played,
  ts.points as points,
  ts.goal_for as goal_for,
  ts.goal_against as goal_against,
  ts.goal_diff as goal_diff
from
  teams t join team_stats ts on t.team_id = ts.team_id
order by
  ts.points desc, ts.goal_diff desc, t.team_name
