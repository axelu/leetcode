
-- 1204. Last Person to Fit in the Bus
-- https://leetcode.com/problems/last-person-to-fit-in-the-bus/



/* Write your T-SQL query statement below */

select
  person_name
from
  queue
where
  turn = (
select
  max(t.turn)
from (
select
  turn,
  person_name,
  weight,
  sum(weight) over(order by turn) as total_weight
from
  queue
) t
where total_weight <= 1000
)
