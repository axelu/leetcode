
-- 1098. Unpopular Books
-- https://leetcode.com/problems/unpopular-books/




/* Write your T-SQL query statement below */

-- from problem: Assume today is 2019-06-23

-- books available in 2018
with books_available
as
(
select
  book_id,
  name
from
  books
where
  available_from < dateadd(month,-1,'2019-06-23')
),
-- copies sold in 2018
books_sold
as
(
select
  book_id,
  sum(quantity) as quantity
from
  orders
where
  dispatch_date >= dateadd(year,-1,'2019-06-23')
group by
  book_id
)
select
  a.book_id,
  a.name
from
  books_available a left join books_sold s on a.book_id = s.book_id
where
  s.quantity is null or
  s.quantity < 10
