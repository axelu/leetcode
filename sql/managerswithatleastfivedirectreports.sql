
-- 570. Managers with at Least 5 Direct Reports
-- https://leetcode.com/problems/managers-with-at-least-5-direct-reports/



/* Write your T-SQL query statement below */

with cte
as
(
select
  managerId
from
  employee
where
  managerId is not null
group by
  managerId
having
  count(*) >= 5
)
select
  e.name
from
  employee e join cte on e.id = cte.managerId
