
-- 2922. Market Analysis III
-- https://leetcode.com/problems/market-analysis-iii/





/* Write your T-SQL query statement below */

with orders_plus as
(
select
    o.order_id,
    o.seller_id,
    s.favorite_brand as seller_favorite_brand,
    o.item_id,
    i.item_brand
from
    Orders as o join Users as s on o.seller_id = s.seller_id
    join Items as i on o.item_id = i.item_id
),
orders_nonfavorite as
(
select distinct
    seller_id,
    item_id
from
    orders_plus
where
    item_brand <> seller_favorite_brand
),
orders_nonfavorite_count as
(
select
    seller_id,
    count(item_id) as num_items
from
    orders_nonfavorite
group by
    seller_id
),
orders_nonfavorite_ranked as
(
select
    seller_id,
    num_items,
    RANK() over(order by num_items DESC) as rnk
from
    orders_nonfavorite_count
)
select
    seller_id,
    num_items
from
    orders_nonfavorite_ranked
where
    rnk = 1
order by
    seller_id
