
-- 3252. Premier League Table Ranking II
-- https://leetcode.com/problems/premier-league-table-ranking-ii/




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
),
TeamCount as
(
select count(*) as nbr_of_teams from TeamStats
)
-- select * from TeamRanks order by position, team_name
select
    tr.team_name,
    tr.points,
    tr.position,
    case
        when position <= ceiling(tc.nbr_of_teams * 0.33)
        then 'Tier 1'
        else
            case
                when position <= ceiling(tc.nbr_of_teams * 0.66)
                then 'Tier 2'
                else 'Tier 3'
            end
    end as tier
from
    TeamRanks tr, TeamCount tc
order by tr.points desc, tr.team_name
