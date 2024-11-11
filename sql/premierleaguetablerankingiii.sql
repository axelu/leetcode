
-- 3322. Premier League Table Ranking III
-- https://leetcode.com/problems/premier-league-table-ranking-iii/





with cte as
(
select
    season_id,
    team_id,
    team_name,
    ((wins * 3) + draws) as points,
    goals_for - goals_against as goal_difference
from
    SeasonStats
)
select
    season_id,
    team_id,
    team_name,
    points,
    goal_difference,
    -- RANK() over (partition by season_id order by points desc, goal_difference desc, team_name) as [rank]
    RANK() over (partition by season_id order by points desc, goal_difference desc, team_name) as [position]
from
    cte
order by
    season_id, position, team_name
