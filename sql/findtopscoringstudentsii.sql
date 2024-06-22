
-- 3188. Find Top Scoring Students II
-- https://leetcode.com/problems/find-top-scoring-students-ii/



/* Write your T-SQL query statement below */

-- test case dictates at least on enrollment record for each student

with student_major as
(
select
    s.student_id,
    c.course_id,
    c.mandatory
from
    students as s join courses as c on s.major = c.major
),
student_enrollment as
(
select
    sm.student_id,
    sm.course_id,
    sm.mandatory,
    e.semester,
    e.grade,
    e.GPA
from
    student_major as sm left join enrollments as e on sm.student_id = e.student_id and sm.course_id = e.course_id
),
-- select * from student_enrollment
mandatory_result as
(
select distinct
    student_id
from
    student_enrollment
where
    mandatory = 'yes' and (grade is null or grade <> 'A')
),
-- select * from mandatory_result
elective_count as
(
select
    s.student_id,
    (select count(*)
    from student_enrollment as se
    where se.student_id = s.student_id and se.mandatory = 'no' and (se.grade = 'A' or se.grade = 'B')) as cnt
from
    students as s
),
avg_gpa as
(
select
    student_id,
    AVG(GPA) as gpa_avg
from
    enrollments
group by
    student_id
)
-- select * from courses where major = 'Mechanical Engineering'
-- select * from student_enrollment where student_id = 6
-- select * from avg_gpa
-- select student_id from mandatory_result
-- select student_id, cnt from elective_count -- where cnt < 2
-- select student_id from avg_gpa where gpa_avg < 2.5

select
    s.student_id
from
    students as s
where
    s.student_id not in (select student_id from mandatory_result) and
    s.student_id not in (select student_id from elective_count count where cnt < 2) and
    s.student_id not in (select student_id from avg_gpa where gpa_avg < 2.5)
order by
    s.student_id

