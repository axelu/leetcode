
-- 3140. Consecutive Available Seats II
-- https://leetcode.com/problems/consecutive-available-seats-ii/



/* Write your T-SQL query statement below */

with cte as
(
select
    seat_id,
    free,
    CASE
        when (free = 1)
        then
            CASE
                when ( (LAG(free) over(order by seat_id) is NULL) OR (LAG(free) over(order by seat_id) = 0 ) )
                then 1
                else 0
            END
        else -1
    END as is_first,
    CASE
        when (free = 1)
        then
            CASE
                when ( (LEAD(free) over(order by seat_id) is NULL) OR (LEAD(free) over(order by seat_id) = 0 ) )
                then 1
                else 0
            END
        else -1
    END as is_last
from
    Cinema
),
first_last as
(
select
    seat_id,
    is_first,
    is_last,
    CASE
        when ( is_first = 1 and is_last = 1 )
        then seat_id
        else
            CASE
                when ( is_first = 0 and is_last = 1 )
                then LAG(seat_id) over(order by seat_id)
                else -1
            END
    END as first_seat_id
from
    cte
where
    is_first = 1 or is_last = 1
),
first_last_ranked as
(
select
    first_seat_id,
    seat_id as last_seat_id,
    seat_id - first_seat_id + 1 as consecutive_seats_len,
    RANK() over(order by seat_id - first_seat_id + 1 desc) as rnk
from
    first_last
where
    first_seat_id <> -1
)
select first_seat_id, last_seat_id, consecutive_seats_len from first_last_ranked where rnk = 1 order by first_seat_id
