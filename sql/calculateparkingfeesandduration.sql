
-- 3166. Calculate Parking Fees and Duration
-- https://leetcode.com/problems/calculate-parking-fees-and-duration/





/* Write your T-SQL query statement below */



with totals as
(
select
    car_id,
    ROUND(CAST(SUM(DATEDIFF(s, entry_time, exit_time)) as decimal) / 3600, 2) as total_time_hrs,
    SUM(fee_paid) as total_fee_paid
from
    ParkingTransactions
group by
    car_id
),
time_in_lot as
(
select
    car_id,
    lot_id,
    SUM(DATEDIFF(s, entry_time, exit_time)) as duration_s
from
    ParkingTransactions
group by
    car_id, lot_id
),
most_time_in_lot as
(
select
    car_id,
    lot_id,
    duration_s,
    Rank() over (partition by car_id order by duration_s desc, lot_id) as rnk
from
    time_in_lot
)
select
    t.car_id,
    t.total_fee_paid,
    ROUND(t.total_fee_paid / t.total_time_hrs, 2) as avg_hourly_fee,
    til.lot_id as most_time_lot
from
    totals as t join most_time_in_lot as til on t.car_id = til.car_id where til.rnk = 1
order by
    t.car_id
