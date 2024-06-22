
-- 3126. Server Utilization Time
-- https://leetcode.com/problems/server-utilization-time/





/* Write your T-SQL query statement below */

-- assume there is a start and corresponding stop pair where start < stop

with starts1 as
(
select
    o.server_id,
    o.status_time,
    o.session_status,
    LAG(session_status) over(partition by server_id order by status_time) as pre_status
from
    Servers o
),
starts as
(
select * from starts1 where session_status = 'start' and (pre_status is null or pre_status = 'stop')
),
stops1 as
(
select
    o.server_id,
    o.status_time,
    o.session_status,
    LEAD(session_status) over(partition by server_id order by status_time) as pre_status
from
    Servers o
),
stops as
(
select * from stops1 where session_status = 'stop' and (pre_status is null or pre_status = 'start')
),
starts_stops1 as
(
select * from starts
union
select * from stops
),
starts_stops2 as
(
select
    server_id,
    status_time as start_time,
    session_status,
    LEAD(status_time) over(partition by server_id order by status_time) as stop_time
from
    starts_stops1
),
duration as
(
select
    server_id,
    start_time,
    stop_time,
    DATEDIFF(ss, start_time, stop_time) as duration_s
from
    starts_stops2
where
    session_status = 'start'
)
select
    sum(duration_s) / 86400 as total_uptime_days
from
    duration
