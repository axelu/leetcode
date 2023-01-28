
-- 1635. Hopper Company Queries I
-- https://leetcode.com/problems/hopper-company-queries-i/





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

activedrivers
as
(
select distinct
  m.mth as [month],
  sum(isnull(d.new_drivers,0)) over(order by m.mth) as active_drivers
from
  months m left join drivers_joining d on m.mth = d.mth
),

accepted_ride_cnt
as
(
select
  datepart(month,r.requested_at) as [month],
  count(*) as accepted_rides
from
  rides r join acceptedrides a on r.ride_id = a.ride_id
where
  datepart(year,r.requested_at) = @rpt_yr
group by
   datepart(month,r.requested_at)
)

select
  ad.[month],
  ad.active_drivers,
  isnull(ar.accepted_rides,0) as accepted_rides
from
  activedrivers ad left join accepted_ride_cnt ar on ad.[month] = ar.[month]
order by
  ad.[month]
