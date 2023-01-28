
-- 1988. Find Cutoff Score for Each School
-- https://leetcode.com/problems/find-cutoff-score-for-each-school/



/* Write your T-SQL query statement below */

select
  s.school_id,
  isnull((
  select top 1
    score
  from
    exam
  where
    student_count <= s.capacity
  order by
    student_count desc, score asc
  ),-1) as score
from
  schools s
