
-- 3268. Find Overlapping Shifts II
-- https://leetcode.com/problems/find-overlapping-shifts-ii/





/* Write your T-SQL query statement below */

-- (employee_id, start_time) is the unique key for this table.
-- so no two shifts for the same employee can start at the same time
-- !!! shifts do not cross days!!! meaning the max end time is startday + 1 00:00:00
-- discovered via testing with shifts that span more than 1 day
-- will assume start_time < end_time

-- sanitize
with shifts as
(
select
    employee_id,
    CAST(start_time AS DATE) as start_date,
    start_time,
    CASE
        WHEN end_time > DATEADD(dd,1,CAST(CAST(start_time AS DATE) AS DATETIME))
        THEN DATEADD(dd,1,CAST(CAST(start_time AS DATE) AS DATETIME))
        else end_time
    END as end_time
from
    EmployeeShifts
),
/*
overlap_mins as -- will not have employees with 0 min overlap
(
select
    s.employee_id,
    s.start_date,
    s.start_time,
    s.end_time,
    r.start_time as ostart_time,
    r.end_time as oend_time,
    CASE
        WHEN s.end_time > r.end_time
        THEN DATEDIFF(mi, r.start_time, r.end_time)
        ELSE DATEDIFF(mi, r.start_time, s.end_time)
    END as overlap_in_min
from
    shifts s join shifts r on s.employee_id = r.employee_id and s.start_date = r.start_date and s.start_time < r.start_time and s.end_time > r.start_time
)
-- total_overlap
select
    employee_id,
    sum(overlap_in_min) as total_overlap_duration
from
    overlap_mins
group by
    employee_id
*/
intervals as
(
select employee_id, start_date, start_time as time_point from shifts
union
select employee_id, start_date, end_time from shifts
),
interval_times as
(
select
    employee_id,
    start_date,
    time_point as start_time,
    LEAD(time_point) over(partition by employee_id, start_date order by time_point) as end_time
from
    intervals
),
overlaps as
(
select
    o.employee_id,
    o.start_date,
    o.start_time,
    o.end_time,
    DATEDIFF(mi, o.start_time, o.end_time) as duration,
    (select
        count(*)
     from
        shifts i
     where
        i.employee_id = o.employee_id and
        i.start_date = o.start_date and
        i.start_time <= o.start_time and
        i.end_time > o.start_time and
        i.end_time >= i.end_time
    ) as cnt_overlapping_shifts
from
    interval_times o
where
    o.end_time is not null
),
overlap_durations as
(
select
    employee_id,
    CAST(duration * (cnt_overlapping_shifts * (cnt_overlapping_shifts-1)/2.0) as INT) as duration
from
    overlaps
),
overlap_total_duration as
(
select
    employee_id,
    SUM(duration) as total_overlap_duration
from
    overlap_durations
group by
    employee_id
)
select
    o.employee_id,
    (select MAX(i.cnt_overlapping_shifts) from overlaps i where o.employee_id = i.employee_id) as max_overlapping_shifts,
    o.total_overlap_duration
from
    overlap_total_duration o
order by
    o.employee_id

