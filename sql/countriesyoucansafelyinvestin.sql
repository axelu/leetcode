
-- 1501. Countries You Can Safely Invest In
-- https://leetcode.com/problems/countries-you-can-safely-invest-in/





/* Write your T-SQL query statement below */

-- global call duration average
declare @global_avg_call_duration float;
set @global_avg_call_duration = (select sum(duration)*2.0/(count(*)*2) from calls);

-- call duration average by country
select
  country
from
  (
    select
      c.caller_id as id,
      c.duration,
      s.name as country
    from
      calls c join person p on c.caller_id = p.id
        join country s on substring(p.phone_number,1,3) = s.country_code
    union all
    select
      c.callee_id as id,
      c.duration,
      s.name
    from
      calls c join person p on c.callee_id = p.id
        join country s on substring(p.phone_number,1,3) = s.country_code
  ) t
group by
  country
having
  cast(sum(duration) as decimal)/count(*) > @global_avg_call_duration

