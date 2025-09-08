
-- 3626. Find Stores with Inventory Imbalance
-- https://leetcode.com/problems/find-stores-with-inventory-imbalance/




/* Write your T-SQL query statement below */

-- definition inventory imbalance:
--     stores where the most expensive product has lower stock than the cheapest product.
-- only include stores with at least 3 different products
-- assumptions:
--    store_id + product_name is unigue
-- Note: max and min price in a given store may not be unique

with stores_with_at_least_three_products as
(
select
    store_id,
    count(product_name) as product_count
from
    inventory
group by
    store_id
having
    count(product_name) > 2
),
expensive as
(
select
    rank() over(partition by i.store_id order by i.price desc) as rnk,
    i.store_id,
    i.inventory_id,
    i.product_name,
    i.quantity,
    i.price
from
    inventory i join stores_with_at_least_three_products s on i.store_id = s.store_id
),
most_expensive as
(
    select * from expensive where rnk = 1
),
cheap as
(
select
    rank() over(partition by i.store_id order by i.price asc) as rnk,
    i.store_id,
    i.inventory_id,
    i.product_name,
    i.quantity,
    i.price
from
    inventory i join stores_with_at_least_three_products s on i.store_id = s.store_id
),
cheapest as
(
    select * from cheap where rnk = 1
),
most_exp_cheapest as
(
select
    c.store_id,
    s.store_name,
    s.location,
    e.inventory_id as most_exp_inventory_id,
    ei.product_name as most_exp_product,
    ei.quantity as most_exp_quantity,
    c.inventory_id as cheapest_inventory_id,
    ci.product_name as cheapest_product,
    ci.quantity as cheapest_quantity
from
    cheapest c join stores s on c.store_id = s.store_id
        join inventory ci on c.inventory_id = ci.inventory_id,
    most_expensive e
        join inventory ei on e.inventory_id = ei.inventory_id
where
    c.store_id = e.store_id
)
select
    store_id,
    store_name,
    [location],
    most_exp_product,
    cheapest_product,
    round(cheapest_quantity / cast(most_exp_quantity as decimal),2) as imbalance_ratio
from
    most_exp_cheapest
where
    most_exp_quantity < cheapest_quantity
order by
    round(cheapest_quantity / cast(most_exp_quantity as decimal),2) desc, store_name
