
-- 184. Department Highest Salary
-- https://leetcode.com/problems/department-highest-salary/



/* Write your T-SQL query statement below */

select
  d.name as Department,
  e.name as Employee,
  e.salary as Salary
from (
    select
      id,
      name,
      salary,
      departmentId,
      rank() over(partition by departmentId order by salary desc) as rnk
    from
      employee
  ) e inner join department d on e.departmentId = d.id
where
  e.rnk = 1
