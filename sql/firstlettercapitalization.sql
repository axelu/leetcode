
-- 3368. First Letter Capitalization
-- https://leetcode.com/problems/first-letter-capitalization/





/* Write your T-SQL query statement below */

/* the problem states to preserve all existing spaces,
 * but testing it shows that the reference implementation
 * if words are separated by more than 1 space,
 * returns them separated by only 1 space as well as
 * leading spaces and trailing spaces are trimmed
 * {"headers":{"user_content":["content_id","content_text"]},"rows":{"user_content":[[1,"  hello   world of SQL  "]]}}
 * well, turns out it trims leading space, but if more than 1, it preserves 1
 * but trailing spaces get all trimmed
 * we will assume on leading of trailing spaces and not deal with that inconsistency, our solution trims all leading and trailing
 *
 * also the problem does not talk about ordering the result, but through observation it requires ordering by content_id asc
 *
 * as of this writing STRING_SPLIT on leetcode's version of SQL Server does not support ordinal param
 * but it preserves the ordering
 */

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
)

select
    c.content_id,
    uc.content_text as original_text,
    STRING_AGG (CONVERT(NVARCHAR(max),c.converted_text), ' ') AS converted_text
FROM
    converted c join user_content uc on c.content_id = uc.content_id
group by
    c.content_id,
    uc.content_text
order by
    c.content_id

