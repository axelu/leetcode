
-- 1709. Biggest Window Between Visits
-- https://leetcode.com/problems/biggest-window-between-visits/



/* Write your T-SQL query statement below */

select distinct
  t.user_id,
  t.date_diff as biggest_window
from
(
    select
      r.user_id,
      r.date_diff,
      rank() over(partition by r.user_id order by r.date_diff desc) as rnk
    from
    (
        select
          user_id,
          datediff(day,visit_date,lead(visit_date,1,'2021-01-01') over(partition by user_id order by visit_date)) as date_diff
        from
          uservisits
    ) r
) t
where
  t.rnk = 1
order by
  t.user_id
