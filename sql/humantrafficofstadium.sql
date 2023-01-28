
-- 601. Human Traffic of Stadium
-- https://leetcode.com/problems/human-traffic-of-stadium/



/* Write your T-SQL query statement below */

with cte
as
(
select
  id,
  visit_date,
  people,
  lead(people,2) over(order by id) as f2,
  lead(people,1) over(order by id) as f1,
  lag(people,2) over(order by id) as b2,
  lag(people,1) over(order by id) as b1
from
  stadium
)

select
  id,
  visit_date,
  people
from
  cte
where
  people >= 100 and
  ( (f2 >= 100 and f1 >= 100) or
    (f1 >= 100 and b1 >= 100) or
    (b2 >= 100 and b1 >= 100) )

