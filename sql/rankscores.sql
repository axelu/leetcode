
-- 178. Rank Scores
-- https://leetcode.com/problems/rank-scores/



/* Write your T-SQL query statement below */

select
  score,
  dense_rank() over(order by score desc) as [rank]
from
  scores
order by
  score desc
