
-- 3156. Employee Task Duration and Concurrent Tasks
-- https://leetcode.com/problems/employee-task-duration-and-concurrent-tasks/





/* Write your T-SQL query statement below */

-- no overlap
-- {"headers":{"Tasks":["task_id","employee_id","start_time","end_time"]},"rows":{"Tasks":[[1,1001,"2023-05-01 08:00:00","2023-05-01 09:00:00"],[2,1001,"2023-05-01 09:00:00","2023-05-01 10:00:00"]]}}
-- {"headers":{"Tasks":["task_id","employee_id","start_time","end_time"]},"rows":{"Tasks":[[1,1001,"2023-05-01 08:00:00","2023-05-01 08:59:59"],[2,1001,"2023-05-01 09:00:00","2023-05-01 10:00:00"]]}}

-- overlap
-- {"headers":{"Tasks":["task_id","employee_id","start_time","end_time"]},"rows":{"Tasks":[[1,1001,"2023-05-01 08:00:00","2023-05-01 09:00:01"],[2,1001,"2023-05-01 09:00:00","2023-05-01 10:00:00"]]}}
-- {"headers":{"Tasks":["task_id","employee_id","start_time","end_time"]},"rows":{"Tasks":[[1,1001,"2023-05-01 08:00:00","2023-05-01 09:00:00"],[2,1001,"2023-05-01 08:59:59","2023-05-01 10:00:00"]]}}

-- overlap eclipsed
-- {"headers":{"Tasks":["task_id","employee_id","start_time","end_time"]},"rows":{"Tasks":[[1,1001,"2023-05-01 08:00:00","2023-05-01 09:00:00"],[2,1001,"2023-05-01 08:15:00","2023-05-01 08:45:00"]]}}
-- {"headers":{"Tasks":["task_id","employee_id","start_time","end_time"]},"rows":{"Tasks":[[1,1001,"2023-05-01 08:00:00","2023-05-01 09:00:00"],[2,1001,"2023-05-01 08:00:00","2023-05-01 09:00:00"]]}}

with overlap as
(
select
    t.task_id,
    t.employee_id,
    (select count(*) from Tasks as i where i.employee_id = t.employee_id and t.end_time > i.start_time and i.start_time >= t.start_time) overlap_count
from
    Tasks t
 ),

tasks_ordered as
(
select
  row_number() over(order by employee_id,start_time,end_time) as rownbr,
  employee_id,
  start_time,
  end_time
from
  Tasks
),
task_overlap -- recursive cte
as
(
select
  rownbr,
  employee_id,
  start_time,
  end_time
from
  tasks_ordered
where
  rownbr = 1 -- first employee first task
union all
select
  t.rownbr,
  t.employee_id,
  case
    when t.employee_id = tol.employee_id
    then
      case
        when t.start_time <= tol.end_time
        then tol.start_time
        else t.start_time
      end
    else t.start_time
  end as start_time,
  case
    when t.employee_id = tol.employee_id
    then
      case
        when t.start_time <= tol.end_time
        then
          case
            when t.end_time > tol.end_time
            then t.end_time
            else tol.end_time
          end
        else t.end_time
      end
    else t.end_time
  end as end_time
from
  task_overlap as tol inner join tasks_ordered as t on t.rownbr = tol.rownbr + 1 -- to is prior row
),
tasks_merged as
(
select
  employee_id,
  start_time,
  max(end_time) as end_time
from
  task_overlap
group by
  employee_id,
  start_time
),
tasks_duration as
(
select
  employee_id,
  sum(datediff(ss, start_time, end_time)) / 3600 as duration_h
from
  tasks_merged
group by
  employee_id

)
select
  td.employee_id,
  td.duration_h as total_task_hours,
  (select max(ol.overlap_count) from overlap as ol where ol.employee_id = td.employee_id) as max_concurrent_tasks
from
  tasks_duration as td
order by
  td.employee_id
option (maxrecursion 0)

