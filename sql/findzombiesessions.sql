
-- 3673. Find Zombie Sessions
-- https://leetcode.com/problems/find-zombie-sessions/


/* Write your T-SQL query statement below */

with session_userid as
(
select distinct session_id, user_id from app_events
),
session_start as
(
select session_id, min(event_timestamp) as start_timestamp from app_events group by session_id
),
session_end as
(
select session_id, max(event_timestamp) as end_timestamp from app_events group by session_id
),
session_duration as
(
select
    ss.session_id,
    ss.start_timestamp,
    se.end_timestamp,
    datediff(mi,ss.start_timestamp,se.end_timestamp) as session_duration_minutes
from
    session_start ss join session_end se on ss.session_id = se.session_id
),
scroll_count as -- ok if session with 0 scrolls omitted
(
select
    session_id,
    count(*) as scroll_event_count
from
    app_events
where
    event_type = 'scroll'
group by
    session_id
),
clicks as
(
select
    session_id,
    count(*) as click_event_count
from
    app_events
where
    event_type = 'click'
group by
    session_id

),
click_count as
(
select
    ss.session_id, -- using session_start for unique sessions
    ISNULL(cs.click_event_count,0) as click_event_count
from
    session_start ss left outer join clicks cs on ss.session_id = cs.session_id
),
purchases as
(
select
    session_id,
    count(*) as purchase_event_count
from
    app_events
where
    event_type = 'purchase'
group by
    session_id

),
purchase_count as
(
select
    ss.session_id, -- using session_start for unique sessions
    ISNULL(ps.purchase_event_count,0) as purchase_event_count
from
    session_start ss left outer join purchases ps on ss.session_id = ps.session_id
),
cte as
(
select
    sd.session_id,
    sd.session_duration_minutes,
    sc.scroll_event_count,
    cc.click_event_count,
    (cc.click_event_count * 1.0)/sc.scroll_event_count as click_to_scroll_ratio,
    pc.purchase_event_count
from
    session_duration sd
        join scroll_count sc on sd.session_id = sc.session_id
        join click_count cc on sd.session_id = cc.session_id
        join purchase_count pc on sd.session_id = pc.session_id
)
select
    cte.session_id,
    su.user_id,
    cte.session_duration_minutes,
    cte.scroll_event_count as scroll_count
from
    cte join session_userid su on cte.session_id = su.session_id
where
    cte.session_duration_minutes > 30
    and cte.scroll_event_count >= 5
    and cte.click_to_scroll_ratio < 0.2
    and cte.purchase_event_count = 0
order by
    cte.scroll_event_count desc, cte.session_id
