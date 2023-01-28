
-- 1459. Rectangles Area
-- https://leetcode.com/problems/rectangles-area/




/* Write your T-SQL query statement below */

select
  p1.id as p1,
  p2.id as p2,
  abs(p1.x_value - p2.x_value) * abs(p1.y_value - p2.y_value) as area
from
  points p1, points p2
where
  p1.id < p2.id and
  p1.x_value <> p2.x_value and
  p1.y_value <> p2.y_value
order by
  abs(p1.x_value - p2.x_value) * abs(p1.y_value - p2.y_value) desc, p1.id, p2.id
