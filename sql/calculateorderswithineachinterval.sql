
-- 2893. Calculate Orders Within Each Interval
-- https://leetcode.com/problems/calculate-orders-within-each-interval/




/* Write your T-SQL query statement below */

with orders_interval as
(
select
    minute,
    case
        when minute % 6 = 0
        then minute / 6
        else minute / 6 + 1
    end as interval_no,
    order_count
from
    Orders
)
select
    interval_no,
    sum(order_count) as total_orders
from
    orders_interval
group by
    interval_no
order by
    interval_no
