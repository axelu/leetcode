
-- 580. Count Student Number in Departments
-- https://leetcode.com/problems/count-student-number-in-departments/



/* Write your T-SQL query statement below */

with cte
as
(
select
  s.dept_id,
  count(*) as student_number
from
  student s
group by
  s.dept_id
)
select
  d.dept_name,
  isnull(cte.student_number,0) as student_number
from
  department d left join cte on d.dept_id = cte.dept_id
order by
  cte.student_number desc, d.dept_name
