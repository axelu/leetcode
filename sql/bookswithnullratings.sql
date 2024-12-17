
-- 3358. Books with NULL Ratings
-- https://leetcode.com/problems/books-with-null-ratings/




/* Write your T-SQL query statement below */

select
    book_id,
    title,
    author,
    published_year
from
    books
where
    rating IS NULL
order by
    book_id
