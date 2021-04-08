


-- 1378. Replace Employee ID With The Unique Identifier
-- https://leetcode.com/problems/replace-employee-id-with-the-unique-identifier/



/* Write your T-SQL query statement below */




SELECT eu.unique_id, e.name
FROM Employees e
     FULL OUTER JOIN EmployeeUNI eu ON e.id = eu.id;
