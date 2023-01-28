
-- 1126. Active Businesses
-- https://leetcode.com/problems/active-businesses/





/* Write your T-SQL query statement below */

with cte
as
(
select
  event_type,
  cast(sum(occurences) as decimal)/count(*) as average_activity
from
  events
group by
  event_type
)
select
  e.business_id
from
  events e join cte on e.event_type = cte.event_type
where
  e.occurences > cte.average_activity
group by
  e.business_id
having
  count(*) > 1
