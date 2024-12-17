
-- 3374. First Letter Capitalization II
-- https://leetcode.com/problems/first-letter-capitalization-ii/





/* Write your T-SQL query statement below */

with cte as
(
SELECT content_id, value
FROM user_content
    CROSS APPLY STRING_SPLIT(content_text, ' ')
WHERE RTRIM(value) <> ''
),
converted as
(
select
    content_id,
    CASE
        when len(value) = 1
        then upper(value)
        else concat(upper(substring(value,1,1)), lower(substring(value,2,len(value)-1)))
    END as converted_text
from
    cte
),
intermediate1 as
(
select
    c.content_id,
    STRING_AGG (CONVERT(NVARCHAR(max),c.converted_text), ' ') AS content_text
FROM
    converted c
group by
    c.content_id
),
cte2 as
(
SELECT content_id, value
FROM intermediate1
    CROSS APPLY STRING_SPLIT(content_text, '-')
WHERE RTRIM(value) <> ''
),
converted2 as
(
select
    content_id,
    CASE
        when len(value) = 1
        then upper(value)
        else concat(upper(substring(value,1,1)), substring(value,2,len(value)-1))
    END as converted_text
from
    cte2
)

select
    c.content_id,
    uc.content_text as original_text,
    STRING_AGG (CONVERT(NVARCHAR(max),c.converted_text), '-') AS converted_text
FROM
    converted2 c join user_content uc on c.content_id = uc.content_id
group by
    c.content_id,
    uc.content_text
order by
    c.content_id
