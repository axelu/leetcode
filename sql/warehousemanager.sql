
-- 1571. Warehouse Manager
-- https://leetcode.com/problems/warehouse-manager/




/* Write your T-SQL query statement below */

with
product_volume (product_id, volume)
as
(
    select product_id, width*length*height as volume
    from products
),
wh_details (name, product_id, volume)
as
(
    select wh.name as warehouse_name,
      wh.product_id, wh.units*b.volume
    from warehouse as wh, product_volume as b
    where wh.product_id = b.product_id
)

select name as warehouse_name, sum(volume) as volume
from wh_details
group by name
