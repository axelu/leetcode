
-- 3262. Find Overlapping Shifts
-- https://leetcode.com/problems/find-overlapping-shifts/





/* Write your PL/SQL query statement below */

with cte_shiftoverlap as
(
select
    o.employee_id,
    o.start_time,
    o.end_time,
    (select count(*) from EmployeeShifts i where i.employee_id = o.employee_id and i.start_time > o.start_time and o.end_time > i.start_time) as cnt_overlapping_shifts
from EmployeeShifts o
)
select
    employee_id,
    sum(cnt_overlapping_shifts) as overlapping_shifts
from
    cte_shiftoverlap
group by
    employee_id
having
    sum(cnt_overlapping_shifts) > 0
order by
    employee_id
