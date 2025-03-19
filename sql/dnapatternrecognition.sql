

-- 3475. DNa Pattern Recognition
-- https://leetcode.com/problems/dna-pattern-recognition/




/* Write your T-SQL query statement below */

select
    sample_id,
    dna_sequence,
    species,
    CASE
        when dna_sequence like 'ATG%'
        then 1
        else 0
    END as has_start,
    CASE
        when (dna_sequence like '%TAA' or dna_sequence like '%TAG' or dna_sequence like '%TGA')
        then 1
        else 0
    END as has_stop,
    CASE
        when dna_sequence like '%ATAT%'
        then 1
        else 0
    END as has_atat,
    CASE
        when dna_sequence like '%GGG%'
        then 1
        else 0
    END has_ggg
from
    Samples
order by
    sample_id
