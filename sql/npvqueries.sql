
-- 1421. NPV Queries
-- https://leetcode.com/problems/npv-queries/



/* Write your T-SQL query statement below */

select q.id,
  q.year,
  isnull(n.npv,0) as npv
from queries q
  left outer join npv n on q.id = n.id and q.year = n.year
