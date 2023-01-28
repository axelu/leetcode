
-- 612. Shortest Distance in a Plane
-- https://leetcode.com/problems/shortest-distance-in-a-plane/




/* Write your T-SQL query statement below */

with a
as
(
select x,y,row_number() over(order by (select null)) as rownbr from point2d
),
b
as
(
select
  a.x as x1,
  a.y as y1,
  t.x as x2,
  t.y as y2,
  round(sqrt(cast((t.x-a.x)*(t.x-a.x)+(t.y-a.y)*(t.y-a.y) as decimal)),2) as distance
from a, a as t
where a.rownbr < t.rownbr
)
select min(distance) as shortest from b
