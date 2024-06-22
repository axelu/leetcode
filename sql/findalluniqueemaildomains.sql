
-- 3059. Find All Unique Email Domains
-- https://leetcode.com/problems/find-all-unique-email-domains/




select
    substring(email, CHARINDEX('@', email) + 1, len(email)) as email_domain,
    count(*) as [count]
from Emails
 where
    substring(email, len(email)-3, 4) = '.com'
group by
    substring(email, CHARINDEX('@', email) + 1, len(email));
