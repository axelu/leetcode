
-- 3246. Premier League Table Ranking
-- https://leetcode.com/problems/premier-league-table-ranking/



/* Write your T-SQL query statement below */

with TeamPoints as
(
select
    team_id,
    team_name,
    ((wins * 3) + draws) as points
from
    TeamStats
),
TeamRanks as
(
select
    team_id,
    team_name,
    points,
    RANK() over (order by points desc) as position
from
    TeamPoints
)
select * from TeamRanks order by position, team_name
