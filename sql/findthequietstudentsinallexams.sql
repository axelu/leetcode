
-- 1412. Find the Quiet Students in All Exams
-- https://leetcode.com/problems/find-the-quiet-students-in-all-exams/




/* Write your T-SQL query statement below */

with exam_high_low
as
(
select exam_id, max(score) as high, min(score) as low from exam group by exam_id
),
loud_students -- students that in an exam scored the highest or lowest score
as
(
select distinct
  e.student_id
from
  exam e join exam_high_low ehl on e.exam_id = ehl.exam_id
         join student s on e.student_id = s.student_id
where
  e.score = ehl.low or e.score = ehl.high
)
select
  s.student_id,
  s.student_name
from
  student s
where
  s.student_id not in (select student_id from loud_students) and
  s.student_id in (select distinct student_id from exam)
order by
  s.student_id
