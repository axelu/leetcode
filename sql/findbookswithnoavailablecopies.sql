
-- 3570. Find Books with No Available Copies
-- https://leetcode.com/problems/find-books-with-no-available-copies/




/* Write your T-SQL query statement below */

with borrowed_book_count as
(
select
    count(*) as cnt,
    br.book_id
from
    borrowing_records br
where
    br.return_date IS NULL
group by
    br.book_id
)
select
    bbc.book_id,
    lb.title,
    lb.author,
    lb.genre,
    lb.publication_year,
    bbc.cnt as current_borrowers
from
    borrowed_book_count bbc join library_books lb on bbc.book_id = lb.book_id
where
    bbc.cnt = lb.total_copies
order by bbc.cnt desc, lb.title
