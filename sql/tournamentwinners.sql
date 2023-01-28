
-- 1194. Tournament Winners
-- https://leetcode.com/problems/tournament-winners/



/* Write your T-SQL query statement below */

with playerscores
as
(
select
  m.first_player as player_id,
  p.group_id,
  m.first_score as score
from
  matches m join players p on m.first_player = p.player_id
union all
select
  m.second_player,
  p.group_id,
  m.second_score
from
  matches m join players p on m.second_player = p.player_id
),

playerscorestotal
as
(
select
  player_id,
  group_id,
  sum(score) over(partition by player_id) as total
from
  playerscores
),

playerranks
as
(
select
  player_id,
  group_id,
  rank() over(partition by group_id order by total desc,player_id) as rnk
from
  playerscorestotal
)

select distinct
  group_id,
  player_id
from
  playerranks
where
  rnk = 1
