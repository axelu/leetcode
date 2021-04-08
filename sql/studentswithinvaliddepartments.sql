


-- 1350. Students With Invalid Departments
-- https://leetcode.com/problems/students-with-invalid-departments/


/* Write your T-SQL query statement below */

--select * from Departments
--select * from Students

select   s.id,
         s.name
from     Students as s
where    s.department_id not in(select id from Departments);
