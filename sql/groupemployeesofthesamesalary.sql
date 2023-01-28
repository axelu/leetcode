
-- 1875. Group Employees of the Same Salary
-- https://leetcode.com/problems/group-employees-of-the-same-salary/


/* Write your T-SQL query statement below */

select
  e.employee_id,
  e.name,
  e.salary,
  t.team_id
from
  employees e inner join (
    select
      salary,
      rank() over(order by salary) as team_id
    from
      employees
    group by
      salary
    having
      count(*) > 1
  ) t on e.salary = t.salary
order by
  t.team_id,e.employee_id
