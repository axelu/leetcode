
-- 1280. Students and Examinations
-- https://leetcode.com/problems/students-and-examinations/



/* Write your T-SQL query statement below */


select
  l.student_id,
  l.student_name,
  l.subject_name,
  isnull(e.subject_name,0) as attended_exams
from (
    select students.student_id, students.student_name, subjects.subject_name from students,subjects
  ) l left outer join examinations e on (l.student_id = e.student_id and l.subject_name = e.subject_name)
where e.subject_name is null

union

select
  e.student_id,
  s.student_name,
  e.subject_name,
  count(*)
from examinations e, students s
where
  e.student_id = s.student_id
group by e.student_id,s.student_name,e.subject_name

order by student_id, subject_name
