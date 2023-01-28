
-- 1978. Employees Whose Manager Left the Company
-- https://leetcode.com/problems/employees-whose-manager-left-the-company/




/* Write your T-SQL query statement below */

select
  e.employee_id
from
  employees e
where
  e.salary < 30000
  and e.manager_id is not null
  and e.manager_id not in (
          select employee_id from employees
      )
order by
  e.employee_id
