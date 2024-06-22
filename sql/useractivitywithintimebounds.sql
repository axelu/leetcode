
-- 3060. User Activities within Time Bounds
-- https://leetcode.com/problems/user-activities-within-time-bounds/





/* Write your T-SQL query statement below */

-- assume sessions for a given user do not overlap
/*
{"headers": {"Sessions": ["user_id", "session_start", "session_end", "session_id", "session_type"]}, "rows": {"Sessions": [
[104, "2023-11-13 00:37:09", "2023-11-13 06:07:09", 667, "Streamer"],
[104, "2023-11-13 02:59:15", "2023-11-13 05:06:15", 809, "Viewer"],
[104, "2023-11-13 13:13:15", "2023-11-13 19:48:15", 906, "Streamer"]
]}}

{"headers": {"Sessions": ["user_id", "session_start", "session_end", "session_id", "session_type"]}, "rows": {"Sessions": [
[104, "2023-11-13 00:37:09", "2023-11-13 06:07:09", 667, "Streamer"],
[104, "2023-11-13 02:59:15", "2023-11-13 05:06:15", 809, "Viewer"],
[104, "2023-11-13 13:13:15", "2023-11-13 19:48:15", 906, "Viewer"]
]}}

in this case both 667 and 809 are considered 'consecutive' before 906, so in both cases user 104 is counted

 */

with sessions_prior_same_id as
(
select
    user_id,
    session_type,
    session_id,
    session_start,
    session_end,
    LAG(session_id) over(partition by user_id, session_type order by session_start, session_id) as pre_session_id
from
    Sessions
),
-- select * from sessions_prior_same_id

sessions_prior_same_details as
(
select
    s.user_id,
    s.session_type,
    s.session_id,
    s.session_start,
    s.session_end,
    s.pre_session_id,
    sp.session_start as pre_session_start,
    sp.session_end as pre_session_end
from
    sessions_prior_same_id as s join Sessions as sp on s.pre_session_id = sp.session_id
where
    s.pre_session_id is not null and
    DATEDIFF(hh, sp.session_end, s.session_start) <= 12
),
sessions_prior as
(
select
    sp.user_id,
    sp.session_type,
    sp.session_id,
    sp.pre_session_id,
    CASE
        when (select
                count(*)
              from
                Sessions as s
              where
                s.user_id = sp.user_id and s.session_type != sp.session_type and
                s.session_start > sp.pre_session_end and s.session_start < sp.pre_session_end
             ) <> 0
        then 1
        else 0
    END as has_in_between_different
from
    sessions_prior_same_details as sp
)
select distinct user_id from sessions_prior where has_in_between_different = 0 order by user_id
