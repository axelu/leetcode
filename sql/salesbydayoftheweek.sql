
-- 1479. Sales by Day of the Week
-- https://leetcode.com/problems/sales-by-day-of-the-week/



/* Write your T-SQL query statement below */


with categories
as
(
    select distinct item_category from items
),
weekdays
as
(
    select * from ( values
        (2,'Monday'),(3,'Tuesday'),(4,'Wednesday'),(5,'Thursday'),(6,'Friday'),
        (7,'Saturday'),(1,'Sunday')
    ) t(id,name)

),
categories_weekdays
as
(
    select
      c.item_category,
      wd.name as weekdayname
    from
      categories c, weekdays wd
),
category_orders
as
(
    select
      i.item_category,
      wd.name as weekdayname,
      sum(o.quantity) as quantity
    from
      orders o join items i on o.item_id = i.item_id
               join weekdays wd on datepart(weekday,o.order_date) = wd.id
    group by
      i.item_category,wd.name
)
select *
from (
select
  cw.item_category as category,
  cw.weekdayname,
  isnull(co.quantity,0) as quantity
from
  categories_weekdays cw left join category_orders co on
    cw.item_category = co.item_category and cw.weekdayname = co.weekdayname
) as sourcetable
pivot
(
  sum(quantity)
  for weekdayname in (Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday)
) as pivottable
