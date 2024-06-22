
-- 3182. Find Top Scoring Students
-- https://leetcode.com/problems/find-top-scoring-students/





/* Write your T-SQL query statement below */

-- assume a course earns 1 or more credits

with req_courses as
(
select
    s.student_id,
    s.major,
    c.course_id,
    c.credits
from
    students as s join courses as c on s.major = c.major
),
req_credits as
(
select
    student_id,
    sum(credits) as req_credits_total
from
    req_courses
group by
    student_id
),
credits as
(
select
    s.student_id,
    s.course_id,
    CASE
        when e.grade is null or e.grade <> 'A'
        then 0
        else s.credits
    END as credits_received
from
    req_courses as s left join enrollments as e on s.student_id = e.student_id and s.course_id = e.course_id
),
credits_earned as
(
select
    student_id,
    sum(credits_received) as credits_received_total
from
    credits
group by
    student_id
)
select
    l.student_id
from
    req_credits as l join credits_earned as r on l.student_id = r.student_id and l.req_credits_total = r.credits_received_total
order by
    l.student_id
