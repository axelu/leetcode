
-- 2793. Status of Flight Tickets
-- https://leetcode.com/problems/status-of-flight-tickets/


/* Write your T-SQL query statement below */

-- Passengers.booking_time column contains distinct values.

with bookings as
(
select
    p.passenger_id,
    p.flight_id,
    p.booking_time,
    RANK() over(partition by p.flight_id order by p.booking_time) as booked_capacity,
    f.capacity as total_capacity
from
    Passengers as p join Flights as f on p.flight_id = f.flight_id
)
select
    passenger_id,
    CASE
        when booked_capacity > total_capacity
        then 'Waitlist'
        else 'Confirmed'
    END as status
from
    bookings
order by
    passenger_id
