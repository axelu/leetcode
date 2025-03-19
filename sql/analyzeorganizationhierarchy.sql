
-- 3482. Analyze Organization Hierarchy
-- https://leetcode.com/problems/analyze-organization-hierarchy/




/* Write your T-SQL query statement below */

-- https://learn.microsoft.com/en-us/sql/t-sql/queries/with-common-table-expression-transact-sql?view=sql-server-ver16
-- https://stackoverflow.com/questions/24394601/recursive-sum-in-tree-structure
-- recursive cte with children count and sum

/*
WITH DirectReports(Name, EmployeeID, EmployeeLevel, Sort)
AS (SELECT CONVERT(VARCHAR(255), e.employee_name),
        e.employee_id,
        1,
        CONVERT(VARCHAR(255), e.employee_name)
    FROM Employees AS e
    WHERE e.manager_id IS NULL
    UNION ALL
    SELECT CONVERT(VARCHAR(255), REPLICATE ('|    ' , EmployeeLevel) + e.employee_name),
        e.employee_id,
        EmployeeLevel + 1,
        CONVERT (VARCHAR(255), RTRIM(Sort) + '|    ' + employee_name)
    FROM Employees AS e
    JOIN DirectReports AS d ON e.manager_id = d.EmployeeID
    )
SELECT EmployeeID, Name, EmployeeLevel
FROM DirectReports
ORDER BY Sort
*/


with directreports as -- recursive cte
(
select employee_id, manager_id, 1 as hierarchy_level from Employees where manager_id is NULL
union all
select e.employee_id, e.manager_id, hierarchy_level + 1
from Employees e inner join directreports d on e.manager_id = d.employee_id
),
C as
(
  -- anchor
  select e.employee_id,
         e.salary,
         1 as team_size,
         e.employee_id as root_id
  from Employees e
  union all
  select e.employee_id,
         e.salary,
         1,
         C.root_id
  from Employees e
    inner join C
      on e.manager_id = C.employee_id
)
select e.employee_id,
       e.employee_name,
       d.hierarchy_level as [level],
       S.team_size - 1 as team_size,
       S.budget
from Employees e
  inner join (
             select root_id,
                    sum(team_size) as team_size,
                    sum(salary) as budget
             from C
             group by root_id
             ) as S
    on e.employee_id = S.root_id
  inner join directreports d
    on e.employee_id = d.employee_id
order by
      d.hierarchy_level, S.budget desc, e.employee_name



OPTION (MAXRECURSION 0);
