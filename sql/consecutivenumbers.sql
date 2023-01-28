
-- 180. Consecutive Numbers
-- https://leetcode.com/problems/consecutive-numbers/


/* Write your T-SQL query statement below */

select
  distinct num as ConsecutiveNums
  --, count(*)
from (
    select
      l.id,
      l.num,
      -- row_number() over (order by l.id),
      -- row_number() over (partition by l.num order by l.id),
      (row_number() over (order by l.id)-row_number() over (partition by l.num order by l.id)) as rep
    from
      logs l
  ) t
group by num,rep
having count(*) >= 3
