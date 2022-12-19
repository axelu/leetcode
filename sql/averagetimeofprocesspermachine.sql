
-- 1661. Average Time of Process per Machine
-- https://leetcode.com/problems/average-time-of-process-per-machine/



/* Write your T-SQL query statement below */


select machine_id,round(sum([end]-start)/count(machine_id),3) as processing_time
from
(
  select machine_id,process_id,activity_type,timestamp from activity
) as SourceTable pivot(avg(timestamp) for activity_type in ([start],[end])) as PivotTable
group by machine_id
