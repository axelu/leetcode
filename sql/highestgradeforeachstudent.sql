
-- 1112. Highest Grade For Each Student
-- https://leetcode.com/problems/highest-grade-for-each-student/

/* Write your T-SQL query statement below */

with cte (student_id,course_id,grade,rnk)
as
(
select
  e.student_id,
  e.course_id,
  e.grade,
  rank() over(partition by e.student_id order by e.grade desc,course_id) as rnk
from
  enrollments e
)
select student_id,course_id,grade from cte where rnk = 1 order by student_id
