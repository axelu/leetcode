
-- 2339. All the Matches of the League
-- https://leetcode.com/problems/all-the-matches-of-the-league/


/* Write your T-SQL query statement below */

with
opponent (team_name)
as
(
    select team_name
    from teams
)

select a.team_name as home_team,
  b.team_name as away_team
from teams a, opponent b
where a.team_name <> b.team_name
