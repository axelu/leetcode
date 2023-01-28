
-- 1075. Project Employees I
-- https://leetcode.com/problems/project-employees-i/



/* Write your T-SQL query statement below */

select
  t.project_id,
  round(cast(sum(t.experience_years) as decimal)/count(*),2) as average_years
from (
    select
      p.project_id,
      e.employee_id,
      e.experience_years
    from
      project as p inner join employee as e on p.employee_id = e.employee_id
  ) as t
group by t.project_id
