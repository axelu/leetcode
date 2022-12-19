
-- 613. Shortest Distance in a Line
-- https://leetcode.com/problems/shortest-distance-in-a-line/


/* Write your T-SQL query statement below */

with xpre (x,pre)
as (
select
  x,
  lag(x,1) over(order by x) as pre
from point
)

select
  min(x-pre) as shortest
from xpre
where pre is not null
