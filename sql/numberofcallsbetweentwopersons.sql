
-- 1699. Number of Calls Between Two Persons
-- https://leetcode.com/problems/number-of-calls-between-two-persons/



/* Write your T-SQL query statement below */

select
  t.person1,
  t.person2,
  count(*) as call_count,
  sum(duration) as total_duration
from (
    select
      case when to_id < from_id then to_id else from_id end as person1
      ,case when to_id < from_id then from_id else to_id end as person2
      ,duration
    from
      calls
) t
group by
  person1,person2
