
-- 3554. Find Category Recommendation Pairs
-- https://leetcode.com/problems/find-category-recommendation-pairs/


/* Write your T-SQL query statement below */

-- distinct user aka customer to category purchases
with user_category as
(
select distinct
    pp.user_id,
    pi.category
from
    ProductPurchases pp join ProductInfo pi on pp.product_id = pi.product_id
),
categories as
(
select distinct category from ProductInfo
),
pair_counts as
(
select
  c1.category as category1,
  c2.category as category2,
  (select count(uc.user_id) from user_category uc join user_category uc1 on uc.user_id = uc1.user_id
   where uc.category = c1.category and uc1.category = c2.category) as customer_count
from
  categories c1,
  categories c2
where
  c1.category < c2.category
)
select
    pc.category1,
    pc.category2,
    pc.customer_count
from
    pair_counts pc
where
    pc.customer_count > 2
order by
    pc.customer_count desc, pc.category1, pc.category2
