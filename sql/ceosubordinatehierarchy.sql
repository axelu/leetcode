
-- 3236. CEO Subordinate Hierarchy
-- https://leetcode.com/problems/ceo-subordinate-hierarchy/




/* Write your T-SQL query statement below */


-- https://learn.microsoft.com/en-us/sql/t-sql/queries/with-common-table-expression-transact-sql?view=sql-server-ver16

with ceo as
(
select employee_id, salary from Employees where manager_id is NULL
),
emps as
(
select
    e.employee_id,
    e.employee_name,
    e.manager_id,
    e.salary - c.salary as salary_difference
from
    Employees e, ceo c
),
directreports as -- recursive cte
(
select employee_id, employee_name, manager_id, salary_difference, 0 as hierarchy_level from emps where manager_id is NULL
union all
select e.employee_id, e.employee_name, e.manager_id, e.salary_difference, hierarchy_level + 1
from emps e inner join directreports d on e.manager_id = d.employee_id
)
select
    employee_id as subordinate_id,
    employee_name as subordinate_name,
    hierarchy_level,
    salary_difference
from
    directreports
where
    hierarchy_level > 0
order by
    hierarchy_level, employee_id
