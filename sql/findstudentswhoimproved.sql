
-- 3421. Find Students Who Improved
-- https://leetcode.com/problems/find-students-who-improved/






/* Write your T-SQL query statement below */

with student_subject_first as
(
select student_id, [subject], MIN(exam_date) as min_date from Scores group by student_id, [subject]
),
student_subject_fscore as
(
select
    s.student_id,
    s.[subject],
    s.score as first_score
from
    Scores s join student_subject_first f on s.student_id = f.student_id and s.subject = f.subject and s.exam_date = f.min_date

),
student_subject_last as
(
select student_id, [subject], MAX(exam_date) as max_date from Scores group by student_id, [subject]
),
student_subject_lscore as
(
select
    s.student_id,
    s.[subject],
    s.score as latest_score
from
    Scores s join student_subject_last l on s.student_id = l.student_id and s.subject = l.subject and s.exam_date = l.max_date

)

select
    f.student_id,
    f.subject,
    f.first_score,
    l.latest_score
from
    student_subject_fscore f join student_subject_lscore l on f.student_id = l.student_id and f.subject = l.subject
where
    f.first_score < l.latest_score
order by
    student_id, subject
