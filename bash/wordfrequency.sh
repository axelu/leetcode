
# 192. Word Frequency
# https://leetcode.com/problems/word-frequency/

# bash



# Read from the file words.txt and output the word frequency list to stdout.

# Trim leading and Trim trailing space
# Replace more than one space with one space
# Change space into carriage returns
# Sort
# Count Unique
# Reverse as we need descending frequency
# Output

sed 's/^[ ]*//g;s/[ ]*$//g;s/[ ]\+/ /g;s/ /\n/g' words.txt | sort | uniq -c | sort -r | awk '{print $2,$1}'
