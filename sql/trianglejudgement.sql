
-- 610. Triangle Judgement
-- https://leetcode.com/problems/triangle-judgement/


/* Write your T-SQL query statement below */


select
  x,y,z,
  case
    when (x+y<=z or x+z<=y or y+z<=x) then 'No'
    else 'Yes'
  end as triangle
from triangle
