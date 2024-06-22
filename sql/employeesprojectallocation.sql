
-- 3057. Employees Project Allocation
-- https://leetcode.com/problems/employees-project-allocation/


/* Write your T-SQL query statement below */

with employee_workload as
(
select
    e.employee_id,
    e.team,
    ISNULL(p.workload, 0) as project_workload
from
    -- Employees as e left join Project as p on e.employee_id = p.employee_id
    Employees as e join Project as p on e.employee_id = p.employee_id -- only count employees who are allocated to projects
),
team_workload as
(
select
    team,
    cast(sum(project_workload) as decimal) / count(employee_id) as avg_workload
from
    employee_workload
group by
    team
)
select
    ew.employee_id,
    p.project_id,
    e.name as employee_name,
    ew.project_workload
from
    employee_workload as ew
        join team_workload as tw on ew.team = tw.team and ew.project_workload > tw.avg_workload
        join Employees as e on ew.employee_id = e.employee_id
        join Project as p on ew.employee_id = p.employee_id
order by
    ew.employee_id, p.project_id

