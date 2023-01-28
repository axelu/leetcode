
-- 1070. Product Sales Analysis III
-- https://leetcode.com/problems/product-sales-analysis-iii/





/* Write your T-SQL query statement below */

select
  product_id,
  year as first_year,
  quantity,
  price
from
  (
    select
      product_id,
      year,
      quantity,
      price,
      rank() over(partition by product_id order by year) as rnk
    from
      sales
  ) t
where
  rnk = 1
