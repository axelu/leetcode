
-- 2494. Merge Overlapping Events in the Same Hall
-- https://leetcode.com/problems/merge-overlapping-events-in-the-same-hall/



/* Write your T-SQL query statement below */

with events
as
(
select
  row_number() over(order by hall_id,start_day,end_day) as rownbr,
  hall_id,
  start_day,
  end_day
from
  hallevents
),

event_overlap -- recursive cte
as
(
select
  rownbr,
  hall_id,
  start_day,
  end_day
from
  events
where
  rownbr = 1 -- first hall first event
union all
select
  e.rownbr,
  e.hall_id,
  case
    when e.hall_id = eo.hall_id
    then
      case
        when e.start_day <= eo.end_day
        then eo.start_day
        else e.start_day
      end
    else e.start_day
  end as start_day,
  case
    when e.hall_id = eo.hall_id
    then
      case
        when e.start_day <= eo.end_day
        then
          case
            when e.end_day > eo.end_day
            then e.end_day
            else eo.end_day
          end
        else e.end_day
      end
    else e.end_day
  end as end_day
from
  event_overlap eo inner join events e on e.rownbr = eo.rownbr + 1 -- eo is prior row
)

select
  hall_id,
  start_day,
  max(end_day) as end_day
from
  event_overlap
group by
  hall_id,
  start_day
option (maxrecursion 0)
