
-- 534. Game Play Analysis III
-- https://leetcode.com/problems/game-play-analysis-iii/



/* Write your T-SQL query statement below */

select
  a.player_id,
  a.event_date,
  sum(games_played) over (partition by a.player_id order by a.event_date) as games_played_so_far
from
  activity a
