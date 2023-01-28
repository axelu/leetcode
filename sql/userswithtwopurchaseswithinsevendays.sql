
-- 2228. Users With Two Purchases Within Seven Days
-- https://leetcode.com/problems/users-with-two-purchases-within-seven-days/



/* Write your T-SQL query statement below */

select distinct
  p.user_id
from
  purchases p join purchases o on
    p.user_id = o.user_id and
    p.purchase_id <> o.purchase_id and
    o.purchase_date between dateadd(day,-7,p.purchase_date) and p.purchase_date
order by
  p.user_id
