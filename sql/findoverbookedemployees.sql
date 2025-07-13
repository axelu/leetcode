
-- 3611. Find Overbooked Employees
-- https://leetcode.com/problems/find-overbooked-employees/


/* Write your T-SQL query statement below */

SET DATEFIRST 1; -- ( Monday )

with meeting_hours_by_week as
(
select
    employee_id,
    datepart(week, meeting_date) as wk,
    sum(duration_hours) as total_meeting_hours
from
    meetings
group by
    employee_id,
    datepart(week, meeting_date)
),
heavy_weeks as
(
select
    employee_id,
    count(*) as meeting_heavy_weeks
from
    meeting_hours_by_week
where
    total_meeting_hours > 20.0
group by
    employee_id
)
select
    hw.employee_id,
    e.employee_name,
    e.department,
    hw.meeting_heavy_weeks
from
    heavy_weeks hw join employees e on hw.employee_id = e.employee_id
where
    hw.meeting_heavy_weeks >= 2
order by
    hw.meeting_heavy_weeks desc, e.employee_name
