
-- 2988. Manager of the Largest Department
-- https://leetcode.com/problems/manager-of-the-largest-department/





/* Write your T-SQL query statement below */

-- assume that each department has one and only one manager

-- max
declare @max_employees int;
set @max_employees = (
select max(cnt) from (
select
    count(emp_id) as cnt,
    dep_id
from
    Employees
group by
    dep_id
) t );


with managers as
(
select
    emp_name,
    dep_id
from
    Employees
where
    position = 'Manager'
),
departments as
(
select
    count(emp_id) as cnt,
    dep_id
from
    Employees
group by
    dep_id
)
select
    m.emp_name as manager_name,
    d.dep_id
from
    departments as d join managers as m on d.dep_id = m.dep_id
where
    cnt = @max_employees
order by
    d.dep_id
