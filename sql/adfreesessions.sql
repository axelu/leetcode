
-- 1809. Ad-Free Sessions
-- https://leetcode.com/problems/ad-free-sessions/



/* Write your T-SQL query statement below */

select
  t.session_id
from (
    select
      p.session_id
      ,p.customer_id
      ,p.start_time
      ,p.end_time
      ,a.ad_id
      --,a.customer_id
      --,a.[timestamp]
    from
      playback as p left outer join ads as a on
        p.customer_id = a.customer_id and p.start_time <= a.[timestamp] and p.end_time >= a.[timestamp]
  ) t
where t.ad_id is null
