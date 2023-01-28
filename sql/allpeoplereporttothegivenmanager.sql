
-- 1270. All People Report to the Given Manager
-- https://leetcode.com/problems/all-people-report-to-the-given-manager/



/* Write your T-SQL query statement below */

WITH cte AS (
    SELECT
        employee_id--,
        --employee_name,
        --manager_id
    FROM
        employees
    WHERE manager_id = 1 and employee_id <> 1
    UNION ALL
    SELECT
        e.employee_id--,
        --e.employee_name,
        --e.manager_id
    FROM
        employees e
        INNER JOIN cte o
            ON o.employee_id = e.manager_id
    where e.manager_id <> 1
)
SELECT employee_id FROM cte;
