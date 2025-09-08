
-- 3642. Find Books with Polarized Opinions
-- https://leetcode.com/problems/find-books-with-polarized-opinions/




/* Write your T-SQL query statement below */

with books_with_minreadings as
(
select
    book_id
from
    reading_sessions
group by
    book_id
having
    count(session_id) >= 5
),
books_with_minreadings_and_polarizedopinions as
(
select
    mr.book_id
from
    books_with_minreadings mr
where
    mr.book_id in (select book_id from reading_sessions where session_rating <= 2) and
    mr.book_id in (select book_id from reading_sessions where session_rating >= 4)
),
lowest_rating as
(
select
    rs.session_id,
    rs.book_id,
    rs.session_rating,
    rank() over(partition by rs.book_id order by rs.session_rating asc) as rnk
from
    reading_sessions rs join books_with_minreadings_and_polarizedopinions b on rs.book_id = b.book_id
),
highest_rating as
(
select
    rs.session_id,
    rs.book_id,
    rs.session_rating,
    rank() over(partition by rs.book_id order by rs.session_rating desc) as rnk
from
    reading_sessions rs join books_with_minreadings_and_polarizedopinions b on rs.book_id = b.book_id
),
cte as
(
select
    bmrpo.book_id,
    b.title,
    b.author,
    b.genre,
    b.pages,
    hr.session_rating - lr.session_rating as rating_spread,
    (select count(*) from reading_sessions rs where bmrpo.book_id = rs.book_id
        and (rs.session_rating <= 2 or rs.session_rating >= 4)) /
    CAST((select count(*) from reading_sessions rs where bmrpo.book_id = rs.book_id) as decimal) as polarization_score
from
    books_with_minreadings_and_polarizedopinions bmrpo
        join books b on bmrpo.book_id = b.book_id
        join lowest_rating lr on (bmrpo.book_id = lr.book_id and lr.rnk = 1)
        join highest_rating hr on (bmrpo.book_id = hr.book_id and hr.rnk = 1)
)
select distinct
    book_id,
    title,
    author,
    genre,
    pages,
    rating_spread,
    round(polarization_score, 2) as polarization_score
from
    cte
where
    polarization_score >= .6
order by
    polarization_score desc, title desc
