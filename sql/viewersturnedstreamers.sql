
-- 2995. Viewers Turned Streamers
-- https://leetcode.com/problems/viewers-turned-streamers/





/* Write your T-SQL query statement below */

with sessions_ranked as
(
select
    user_id,
    session_start,
    session_type,
    RANK() over(partition by user_id order by session_start) as rnk
from
    Sessions
),
users_first_viewers as
(
select
    user_id
from
    sessions_ranked
where
    rnk = 1 and
    session_type = 'Viewer'
),
users_streaming_sessions as
(
select
    s.user_id,
    count(s.session_id) as sessions_count
from
    Sessions as s
where
    s.user_id in (select user_id from users_first_viewers) and
    s.session_type = 'Streamer'
group by
    s.user_id
)
select
    fv.user_id,
    ss.sessions_count
from
    users_first_viewers as fv join users_streaming_sessions as ss on fv.user_id = ss.user_id
order by
    sessions_count desc, fv.user_id desc
