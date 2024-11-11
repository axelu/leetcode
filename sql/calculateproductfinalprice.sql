
-- 3293. Calculate Product Final Price
-- https://leetcode.com/problems/calculate-product-final-price/



/* Write your T-SQL query statement below */

with cte as
(
select
    p.product_id,
    p.category,
    p.price as price_without_discount,
    ISNULL(d.discount,0) as discount_percentage
from
    Products p left outer join Discounts d on p.category = d.category
)
select
    product_id,
    ROUND(price_without_discount * (100 - discount_percentage) / 100.0, 2) as final_price,
    category
from
    cte
order by
    product_id
