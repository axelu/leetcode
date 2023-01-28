
-- 1731. The Number of Employees Which Report to Each Employee
-- https://leetcode.com/problems/the-number-of-employees-which-report-to-each-employee/



/* Write your T-SQL query statement below */


select
  l.employee_id
  ,l.name
  ,count(*) as reports_count
  ,round(avg(cast(r.age as decimal)),0) as average_age
from
  employees as l left outer join employees as r on l.employee_id = r.reports_to
where r.employee_id is not null
group by l.employee_id,l.name
order by l.employee_id
