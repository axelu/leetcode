
-- 2668. Find Latest Salaries
-- https://leetcode.com/problems/find-latest-salaries/




/* Write your T-SQL query statement below */

with cte (emp_id,salary)
as
(
    select
      emp_id,
      max(salary) as salary
    from
      Salary
    group by
      emp_id
)
select distinct
  s.emp_id,
  s.firstname,
  s.lastname,
  (select cte.salary from cte where s.emp_id = cte.emp_id) as salary,
  s.department_id
from
  salary s
order by
  s.emp_id
