
-- 2480. Form a Chemical Bond
-- https://leetcode.com/problems/form-a-chemical-bond/


/* Write your T-SQL query statement below */


select
  e.symbol as metal,
  t.symbol as nonmetal
from
  elements e, elements t
where
  e.type = 'Metal' and t.type = 'Nonmetal'
