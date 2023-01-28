
-- 1294. Weather Type in Each Country
-- https://leetcode.com/problems/weather-type-in-each-country/



/* Write your T-SQL query statement below */

select
  c.country_name,
  case
    when t.avg_tmp <= 15 then 'Cold'
    when t.avg_tmp >= 25 then 'Hot' else 'Warm'
  end as weather_type
from (
    select
      w.country_id,
      datepart(year,w.day) as year,
      datepart(month,w.day) as month,
      cast(sum(w.weather_state) as decimal)/count(*) as avg_tmp
    from
      weather as w
      where datepart(year,w.day) = 2019 and datepart(month,w.day) = 11
    group by w.country_id,datepart(year,w.day),datepart(month,w.day)
) t inner join countries c on t.country_id = c.country_id
