
-- 3705. Find Golden Hour Customers
-- https://leetcode.com/problems/find-golden-hour-customers/




/* Write your T-SQL query statement below */

with cte_total_order_count as
(
select
    customer_id,
    count(*) as total_order_count
from
    restaurant_orders
group by
    customer_id
),
cte_peak_hour_order_count as
(
select
    customer_id,
    count(*) as peak_hour_order_count
from
    restaurant_orders
where
    ( timefromparts(datepart(hour, order_timestamp), datepart(minute, order_timestamp), datepart(second, order_timestamp), 0, 0) >= timefromparts(11,0,0,0,0)
    and timefromparts(datepart(hour, order_timestamp), datepart(minute, order_timestamp), datepart(second, order_timestamp), 0, 0) < timefromparts(14,0,0,0,0) )
    or ( timefromparts(datepart(hour, order_timestamp), datepart(minute, order_timestamp), datepart(second, order_timestamp), 0, 0) >= timefromparts(18,0,0,0,0)
    and timefromparts(datepart(hour, order_timestamp), datepart(minute, order_timestamp), datepart(second, order_timestamp), 0, 0) < timefromparts(21,0,0,0,0) )
group by
    customer_id
),
cte_rating_count as
(
select
    customer_id,
    count(*) as rating_count
from
    restaurant_orders
where
    order_rating is not null
group by
    customer_id
),
cte_rating_avg as
(
select
    customer_id,
    avg(order_rating * 1.0) as rating_avg
from
    restaurant_orders
where
    order_rating is not null
group by
    customer_id
),
cte_customer_stats as
(
select distinct
    o.customer_id,
    toc.total_order_count,
    isnull(phoc.peak_hour_order_count, 0) as peak_hour_order_count,
    isnull(rc.rating_count, 0) as rating_count,
    isnull(ra.rating_avg, 0) as rating_avg
from
    restaurant_orders o
        join cte_total_order_count toc on o.customer_id = toc.customer_id
        left outer join cte_peak_hour_order_count phoc on o.customer_id = phoc.customer_id
        left outer join cte_rating_count rc on o.customer_id = rc.customer_id
        left outer join cte_rating_avg ra on o.customer_id = ra.customer_id
)
select
    customer_id,
    total_order_count as total_orders,
    round((peak_hour_order_count * 1.0 / total_order_count) * 100, 0) as peak_hour_percentage,
    round(rating_avg, 2) as average_rating
from
    cte_customer_stats
where
    total_order_count >= 3
    and peak_hour_order_count * 1.0 / total_order_count >= .6
    and rating_avg >= 4.0
    and rating_count * 1.0 / total_order_count >= .5
order by
    rating_avg desc, customer_id desc
