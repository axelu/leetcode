
-- 2394. Employees With Deductions
-- https://leetcode.com/problems/employees-with-deductions/




/* Write your T-SQL query statement below */


with worked_hours
as
(
select
  employee_id,
  sum(
  case
    when datediff(second,in_time,out_time)%60 = 0
    then datediff(second,in_time,out_time)/60
    else datediff(second,in_time,out_time)/60 + 1
  end)/60 as hours
from
  logs
group by
  employee_id
)
select
  e.employee_id
from
  employees e left join worked_hours w on e.employee_id = w.employee_id
where
  w.hours is null or
  w.hours < e.needed_hours
