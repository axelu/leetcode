
-- 2854. Rolling Average Steps
-- https://leetcode.com/problems/rolling-average-steps/





/* Write your T-SQL query statement below */

with steps_threedays as
(
select
    o.user_id,
    o.steps_date,
    steps_count,
    (select s.steps_count from Steps s where s.user_id = o.user_id and s.steps_date = DATEADD(dd, -1, o.steps_date)) as pre_count,
    (select s.steps_count from Steps s where s.user_id = o.user_id and s.steps_date = DATEADD(dd, -2, o.steps_date)) as prepre_count
from
    Steps o
)
select
    user_id,
    steps_date,
    ROUND((steps_count + pre_count + prepre_count) / 3.0, 2) as rolling_average
from
    steps_threedays
where
    pre_count is not null and prepre_count is not null
order by
    user_id, steps_date
