
-- 3617. Find Students with Study Spiral Pattern
-- https://leetcode.com/problems/find-students-with-study-spiral-pattern/



/* Write your T-SQL query statement below */

-- student must have at least studied a given subject 2 times
with student_session_cnt as
(
select
    student_id,
    [subject],
    count(session_id) as session_cnt
from
    study_sessions
group by
    student_id, [subject]
having
    count(session_id) >= 2
),
-- student must have at least studied 3 different subjects
student_cycle as
(
select
    student_id,
    count(*) as cycle_length
from
    student_session_cnt
group by
    student_id
having
    count(*) >= 3
),
-- prior session days diff <= 2
student_sessions_day_diff as
(
select
    ss.student_id,
    ss.subject,
    ss.session_date,
    CASE
        when LAG(ss.session_date) over(partition by ss.student_id order by ss.session_date) is null
        then 0
        else DATEDIFF(day, LAG(ss.session_date) over(partition by ss.student_id order by ss.session_date), ss.session_date)
    END as prior_session_diff
from
    study_sessions ss join student_session_cnt ssc on (ss.student_id = ssc.student_id and ss.subject = ssc.subject)
where
    ss.student_id in (select student_id from student_cycle)
),
student_sessions_day_check as
(
select
    student_id,
    max(prior_session_diff) as max_session_diff
from
    student_sessions_day_diff
group by
    student_id
having
    max(prior_session_diff) <= 2
),
-- we must check the pattern now
student_prior_subject as
(
select
    ss.student_id,
    ss.subject,
    LAG(ss.subject,sc.cycle_length) over(partition by ss.student_id order by ss.session_date) as prior_subject
from
    study_sessions ss join student_cycle sc on ss.student_id = sc.student_id
where
    ss.student_id in (select student_id from student_sessions_day_check)
),
student_prior_subject_match as
(
select
    student_id,
    CASE
        when prior_subject is null
        then 0
        else
            CASE
                when subject <> prior_subject
                then 1
                else 0
            END
    END as pattern_match
from
    student_prior_subject
),
student_prior_subject_check as
(
select
    student_id,
    max(pattern_match) as match_score
from
    student_prior_subject_match
group by
    student_id
having
    max(pattern_match) = 0
),
student_study_hours as
(
select
    ss.student_id,
    sum(ss.hours_studied) as hours_studied
from
    study_sessions ss join student_session_cnt ssc on (ss.student_id = ssc.student_id and ss.subject = ssc.subject)
where
    ss.student_id in (select student_id from student_prior_subject_check)
group by
    ss.student_id
)
-- putting it all together
select
    ssh.student_id,
    s.student_name,
    s.major,
    sc.cycle_length,
    ssh.hours_studied as total_study_hours
from
    student_study_hours ssh join students s on ssh.student_id = s.student_id
        join student_cycle sc on ssh.student_id = sc.student_id
order by
    sc.cycle_length desc, ssh.hours_studied desc
