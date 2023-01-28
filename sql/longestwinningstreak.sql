
-- 2173. Longest Winning Streak
-- https://leetcode.com/problems/longest-winning-streak/


/* Write your T-SQL query statement below */

-- see also 180. Consecutive Numbers https://leetcode.com/problems/consecutive-numbers/

with players
as
(
select distinct player_id from matches
),
result_rep
as
(
select
  player_id,
  match_day,
  result,
  -- row_number() over (partition by player_id order by match_day),
  -- row_number() over (partition by player_id,result order by match_day),
  (row_number() over (partition by player_id order by match_day) -
     row_number() over (partition by player_id,result order by match_day)) as rep
from
  matches
),
result_rep_ranked
as
(
select
  player_id,
  rep,
  count(*) as cnt,
  rank() over(partition by player_id order by count(*) desc) as rnk
from
  result_rep
where
  result = 'Win'
group by
  player_id,
  rep
)
select distinct
  p.player_id,
  isnull(r.cnt,0) as longest_streak
from
  players p left join result_rep_ranked r on p.player_id = r.player_id and r.rnk = 1
