
-- 1158. Market Analysis I
-- https://leetcode.com/problems/market-analysis-i/


/* Write your T-SQL query statement below */

select
  u.user_id as buyer_id,
  u.join_date,
  isnull(o.order_cnt,0) as orders_in_2019
from
  users u left outer join (
      select
        o.buyer_id,
        count(*) as order_cnt
      from
        orders o
      where
        datepart(year,order_date) = 2019
      group by o.buyer_id
    ) o on u.user_id = o.buyer_id
