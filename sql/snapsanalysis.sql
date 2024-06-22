
-- 3056. Snaps Analysis
-- https://leetcode.com/problems/snaps-analysis/





/* Write your T-SQL query statement below */

with user_activities as
(
select
    -- a.user_id,
    u.age_bucket,
    a.activity_type,
    sum(a.time_spent) as time_spent
from
    Activities as a join Age u on a.user_id = u.user_id
group by
    a.activity_type, u.age_bucket
),
open_send as
(
select * from (
select age_bucket, activity_type, time_spent from user_activities
) as SourceTable
pivot ( sum(time_spent) for activity_type in ([open],send)) as PivotTable
)
select
    age_bucket,
    ROUND((ISNULL(send, 0.0) * 100.0) / (ISNULL([open], 0.0) + ISNULL(send, 0.0)), 2) as send_perc,
    ROUND((ISNULL([open], 0.0) * 100.0) / (ISNULL([open], 0.0) + ISNULL(send, 0.0)), 2) as open_perc
from
    open_send
