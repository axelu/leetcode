
-- 1789. Primary Department for Each Employee
-- https://leetcode.com/problems/primary-department-for-each-employee/



/* Write your T-SQL query statement below */

select
  employee_id,
  department_id
from employee
where employee_id not in (
  select employee_id from employee where primary_flag = 'Y'
)
union
select
  employee_id,
  department_id
from employee
where primary_flag = 'Y'
