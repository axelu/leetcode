
-- 1645. Hopper Company Queries II
-- https://leetcode.com/problems/hopper-company-queries-ii/



/* Write your T-SQL query statement below */

declare @rpt_yr int;
set @rpt_yr = 2020;


with months
as
(
    select * from ( values (1),(2),(3),(4),(5),(6),(7),(8),(9),(10),(11),(12) ) t(mth)
),

drivers_joining
as
(
select 1 as mth, count(*) as new_drivers from drivers where join_date <= cast(@rpt_yr as varchar)+'-01-31'
union
select distinct datepart(month,join_date) as month, count(*) over(partition by datepart(month,join_date)) from drivers where datepart(year,join_date) = @rpt_yr and datepart(month,join_date) > 1
),

available_drivers
as
(
select distinct
  m.mth,
  sum(isnull(d.new_drivers,0)) over(order by m.mth) as available_drivers
from
  months m left join drivers_joining d on m.mth = d.mth
),

drivers_with_accepted_rides
as
(
select
  datepart(month,r.requested_at) as mth,
  count(distinct a.driver_id) as cnt
from
  acceptedrides a join rides r on a.ride_id = r.ride_id
where
  datepart(year,r.requested_at) = @rpt_yr
group by
  datepart(month,r.requested_at)
)

select
  m.mth as [month],
  case
    when a.available_drivers is null
    then 0
    else
      case
        when a.available_drivers = 0
        then 0
        else round(isnull(d.cnt,0) * 100.0 / a.available_drivers,2)
      end
  end as working_percentage
from
  months m left join available_drivers a on m.mth = a.mth
           left join drivers_with_accepted_rides d on m.mth = d.mth
order by
  m.mth
