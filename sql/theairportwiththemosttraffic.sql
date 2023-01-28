
-- 2112. The Airport With the Most Traffic
-- https://leetcode.com/problems/the-airport-with-the-most-traffic/



/* Write your T-SQL query statement below */

select
  airport as airport_id
from (
    select
      airport,
      rank() over(order by flights_count desc) as rnk
    from (
        select
          airport,
          sum(cnt) as flights_count
        from (
            select
              departure_airport as airport,
              sum(flights_count) as cnt
            from
              flights
            group by
              departure_airport
            union
            select
              arrival_airport as airport,
              sum(flights_count) as cnt
            from
              flights
            group by
              arrival_airport
        ) t
        group by
          airport
      ) t
  ) t
where
  rnk = 1
