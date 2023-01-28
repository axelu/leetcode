
-- 1077. Project Employees III
-- https://leetcode.com/problems/project-employees-iii/


/* Write your T-SQL query statement below */

select
  t.project_id,
  t.employee_id
from
(
select
  p.project_id,
  p.employee_id,
  e.experience_years,
  rank() over(partition by p.project_id order by experience_years desc) as rnk
from
  project p inner join employee e on p.employee_id = e.employee_id
) t
where
  t.rnk = 1
