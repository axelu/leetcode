
-- 3521. Find Product Recommendation Pairs
-- https://leetcode.com/problems/find-product-recommendation-pairs/




/* Write your T-SQL query statement below */

with pair_counts as
(
select
  pi1.product_id as product1_id,
  pi2.product_id as product2_id,
  (select count(pp.user_id) from ProductPurchases pp join ProductPurchases pp1 on pp.user_id = pp1.user_id
   where pp.product_id = pi1.product_id and pp1.product_id = pi2.product_id) as customer_count
from
  ProductInfo pi1,
  ProductInfo pi2
where
  pi1.product_id < pi2.product_id
)
select
    pc.product1_id,
    pc.product2_id,
    (select category from ProductInfo where product_id = pc.product1_id) as product1_category,
    (select category from ProductInfo where product_id = pc.product2_id) as product2_category,
    pc.customer_count
from
    pair_counts pc
where
    pc.customer_count > 2
order by
    pc.customer_count desc, pc.product1_id, pc.product2_id
