
-- 3451. Find Invalid IP Addresses
-- https://leetcode.com/problems/find-invalid-ip-addresses/



/* Write your T-SQL query statement below */

-- length less than 7
-- starts with 0[0-9] or contains .0[0-9]
-- starts with . or ends with .
-- does not contain a . or contains more then three dots
-- contains ..
-- contains anything other than . or numbers
-- contains a number greater than 255

-- de-dup
with ips as
(
select
    ROW_NUMBER() over (order by ip) as ip_id,
    ip,
    count(*) as [count]
from
    logs
group by
    ip
),
octets as
(
select
  ip_id,
  cs.Value as octet --SplitData
from
  ips
cross apply STRING_SPLIT (ip, '.') cs
),
invalid_ip_ids as
(
select ip_id from octets group by ip_id having count(*) < 4 OR count(*) > 4
union
select ip_id from octets where len(octet) > 1 and octet like '0%'
union
select ip_id from octets where octet LIKE '%[^0-9]%'
union
select ip_id from octets where len(octet) > 3 OR (octet LIKE '[0-9][0-9][0-9]' and CONVERT(int, octet) > 255)
)

select ip, [count] as invalid_count
from ips join invalid_ip_ids ii on ips.ip_id = ii.ip_id
order by [count] desc, ip desc
