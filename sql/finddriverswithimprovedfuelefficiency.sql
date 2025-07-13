
-- 3601. Find Drivers with Improved Fuel Efficiency
-- https://leetcode.com/problems/find-drivers-with-improved-fuel-efficiency/


/* Write your T-SQL query statement below */

with trip_efficiency as
(
select
    trip_id,
    driver_id,
    trip_date,
    distance_km/fuel_consumed as fuel_efficiency
from
    trips
),
first_half as
(
select
    driver_id,
    SUM(fuel_efficiency) / COUNT(driver_id) as avg
from
    trip_efficiency
where
    trip_date < '2023-07-01'
group by
    driver_id
),
second_half as
(
select
    driver_id,
    SUM(fuel_efficiency) / COUNT(driver_id) as avg
from
    trip_efficiency
where
    trip_date >= '2023-07-01'
group by
    driver_id
)
select
    fh.driver_id,
    d.driver_name,
    ROUND(fh.avg, 2) as first_half_avg,
    ROUND(sh.avg, 2) as second_half_avg,
    ROUND((sh.avg - fh.avg), 2) as efficiency_improvement
from
    first_half fh join second_half sh on fh.driver_id = sh.driver_id
        join drivers d on fh.driver_id = d.driver_id
where
    (sh.avg - fh.avg) > 0.0
order by
    (sh.avg - fh.avg) desc, d.driver_name
