
-- 1251. Average Selling Price
-- https://leetcode.com/problems/average-selling-price/


/* Write your T-SQL query statement below */

with unitssoldwithprice (product_id,purchase_date,units,price,total)
as (
    select
      u.product_id,
      u.purchase_date,
      u.units,
      p.price,
      p.price*u.units as total
    from
      prices p inner join unitssold u on
        p.product_id = u.product_id and p.start_date <= u.purchase_date and p.end_date >= u.purchase_date
)

select
  product_id,
  cast(format(cast(sum(total) as float)/sum(units),'N2') as float) as average_price
from
  unitssoldwithprice
group by
  product_id
