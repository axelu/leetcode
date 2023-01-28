
-- 577. Employee Bonus
-- https://leetcode.com/problems/employee-bonus/
-- resource https://www.sqlshack.com/sql-outer-join-overview-and-examples/


/* Write your T-SQL query statement below */

select
  e.name,
  b.bonus
from employee e left outer join bonus b on
  e.empId = b.empId
where
  b.bonus is null or b.bonus < 1000
