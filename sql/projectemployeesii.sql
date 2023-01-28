
-- 1076. Project Employees II
-- https://leetcode.com/problems/project-employees-ii/




/* Write your T-SQL query statement below */

select
  t.project_id
from (
    select
     p.project_id
     ,rank() over (order by p.nbr_employees desc) as rnk
    from (
        select
          project_id
          ,count(*) as nbr_employees
        from
          project
        group by project_id
    ) as p
  ) as t
where t.rnk = 1
