-- 3328. Find Cities in Each State II
-- https://leetcode.com/problems/find-cities-in-each-state-ii/


/* Write your T-SQL query statement below */

with states_with_three_or_more_cities as
(
select
    state,
    count(city) as city_count
from
    cities
group by
    state
having count(city) > 2
),
cities_with_same_start_letter_as_state as
(
select distinct
    c.state,
    j.city
from
    cities c join cities j on c.state = j.state and substring(c.state,1,1) = substring(j.city,1,1)
),
cities_with_same_start_letter_as_state_count as
(
select
    state,
    count(*) as matching_letter_count
from
    cities_with_same_start_letter_as_state
group by
    state
)
select distinct
  c.state,
  trim(stuff((
        select ', ' + i.city
        from cities i
        where c.state = i.state
        order by i.city asc
        for xml path('')
    ), 1, 1, ''
  )) as cities,
  cwslc.matching_letter_count
from
  cities c join cities_with_same_start_letter_as_state_count cwslc on c.state = cwslc.state join states_with_three_or_more_cities swtomc on c.state = swtomc.state
order by
  cwslc.matching_letter_count desc,
  state
