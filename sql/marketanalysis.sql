
-- 1159. Market Analysis II
-- https://leetcode.com/problems/market-analysis-ii/



/* Write your T-SQL query statement below */

with order_details
as
(
select
  o.order_id,
  o.order_date,
  o.item_id,
  i.item_brand,
  o.buyer_id,
  o.seller_id,
  s.favorite_brand as seller_favorite_brand,
  rank() over(partition by o.seller_id order by o.order_date) as seller_sale_cnt
from
  orders o
    join items i on o.item_id = i.item_id
    join users s on o.seller_id = s.user_id
)
select
  u.user_id as seller_id,
  case
    when u.user_id in (select od.seller_id from order_details od where od.seller_id = u.user_id and od.seller_sale_cnt = 2 and od.item_brand = u.favorite_brand)
    then 'yes'
    else 'no'
  end as [2nd_item_fav_brand]
from
  users u
