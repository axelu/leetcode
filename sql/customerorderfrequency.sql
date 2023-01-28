
-- 1511. Customer Order Frequency
-- https://leetcode.com/problems/customer-order-frequency/


/* Write your T-SQL query statement below */

select
  customer_id,
  name
from customers
where customer_id in (
    select t.customer_id
    from (
        select
          o.customer_id,
          datepart(year,o.order_date) as order_year,
          datepart(month,o.order_date) as order_month,
          sum(o.quantity * p.price) as total
        from
          orders o inner join product p on o.product_id = p.product_id
        where
          datepart(year,o.order_date) = 2020 and
          datepart(month,o.order_date) in (6,7)
        group by o.customer_id, datepart(year,o.order_date), datepart(month,o.order_date)
        having sum(o.quantity * p.price) >= 100
    ) t
    group by t.customer_id
    having count(t.customer_id) = 2
)

