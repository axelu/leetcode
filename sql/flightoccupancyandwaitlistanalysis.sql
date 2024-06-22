
-- 2783. Flight Occupancy and Waitlist Analysis
-- https://leetcode.com/problems/flight-occupancy-and-waitlist-analysis/




/* Write your T-SQL query statement below */

with bookings as
(
select flight_id, count(passenger_id) as booked_cnt from Passengers group by flight_id
)
select
    f.flight_id,
    CASE
        when ISNULL(b.booked_cnt,0) > f.capacity
        then f.capacity
        else ISNULL(b.booked_cnt,0)
    END as booked_cnt,
    CASE
        when ISNULL(b.booked_cnt,0) > f.capacity
        then ISNULL(b.booked_cnt,0) - f.capacity
        else 0
    END as waitlist_cnt
from
    Flights as f left join bookings as b on f.flight_id = b.flight_id
order by
    f.flight_id
