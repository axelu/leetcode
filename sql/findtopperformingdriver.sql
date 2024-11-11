
-- 3308. Find Top Performing Driver
-- https://leetcode.com/problems/find-top-performing-driver/




/* Write your T-SQL query statement below */

with driver_details as
(
select
    v.driver_id,
    v.fuel_type,
    d.accidents,
    sum(t.distance) as total_distance,
    sum(t.rating)/(count(t.trip_id)*1.0) as average_rating
from
    Trips t join Vehicles v on t.vehicle_id = v.vehicle_id
        join Drivers d on v.driver_id = d.driver_id
group by
    v.driver_id, v.fuel_type, d.accidents
),
rankings as
(
select
    dd.fuel_type,
    dd.driver_id,
    dd.average_rating as rating,
    dd.total_distance as distance,
    dd.accidents,
    RANK() over (partition by dd.fuel_type order by dd.average_rating desc, dd.total_distance desc, dd.accidents) as rnk
from
    driver_details dd
)
select
    fuel_type,
    driver_id,
    ROUND(rating,2) as rating,
    distance
from
    rankings
where
    rnk = 1
