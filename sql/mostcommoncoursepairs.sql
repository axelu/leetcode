
-- 3764. Most Common Course Pairs
-- https://leetcode.com/problems/most-common-course-pairs/



/* Write your T-SQL query statement below */

with courses as
(
select distinct
    course_id,
    course_name
from
    course_completions
),
cte_top_performers as
(
select
    user_id,
    count(course_id) as courses_completed,
    avg(course_rating) as average_rating
from
    course_completions
group by
    user_id
having
    count(course_id) >= 5 and
    avg(course_rating) >= 4
),
cte_top_performers_course_transitions as
(
select
    cc.user_id,
    cc.course_id,
    -- cc.completion_date,
    lead(cc.course_id) over(partition by cc.user_id order by cc.completion_date) as next_course_id
from
    course_completions as cc
    join cte_top_performers as tp on cc.user_id = tp.user_id
-- order by
--     cc.user_id,
--     cc.completion_date
),
cte_course_transition_counts as
(
select
    course_id,
    next_course_id,
    count(*) as transition_count
from
    cte_top_performers_course_transitions
where
    next_course_id is not null
group by
    course_id, next_course_id
)
select
    fc.course_name as first_course,
    sc.course_name as second_course,
    ct.transition_count
from
    cte_course_transition_counts ct
    join courses fc on ct.course_id = fc.course_id
    join courses sc on ct.next_course_id = sc.course_id
order by
    ct.transition_count desc, fc.course_name, sc.course_name
