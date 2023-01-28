
-- 185. Department Top Three Salaries
-- https://leetcode.com/problems/department-top-three-salaries/


/* Write your T-SQL query statement below */

with cte
as
(
select
  name,
  salary,
  departmentId,
  dense_rank() over(partition by departmentId order by salary desc) as rnk
from employee
)

select
  d.name as Department,
  e.name as Employee,
  e.salary as Salary
from
  cte e join department d on e.departmentId = d.id
where
  e.rnk <= 3

