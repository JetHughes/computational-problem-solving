# Date Parser
`python3 date_parser.py [OPTION]...`

## Testing
- Unit tests for individual functions
- Argv's for running files with different output options
- Script to generate valid dates
- Invalid data
- Units test to test `parse_date()`. How to evaluate correctness

## Report
At fist I was testing using single line from stdin. This worked at the beginning to simply verify that the program was outputing in the correct format, and accepting input correctly. The first thing I after that was write a program to generate every possible valid date. This file was too large run through entirely for every test, so I extracted all the formats for a single date, and came up with as many invalid dates and edge cases as I could think of. To test the program I would cat these files into the python program and check the output. This quickly became cumbersome to look through for valid and invalid dates and comparing the output with the input. Added some command line arguments to change the program so it would only print valid or only print invalid dates. This sped up testing a little. Now I could run through larger files as it didn't have to print every line. However, it was not optimal

So I broke my program down into isolated functions and wrote unit tests using pythons unittest. This enabled me to identify specifically which tests were failing so it was easy to fix issues. I had unit tests for functions which check, leap years, the day, month, year, separators, and whether the date is valid. In addition I added some tests for the whole parse_date() function, which runs through a representative selection of invalid and valid dates.

## Description
Reads input from stdin and determines whether or not it is a valid date. Criteria:

  **Order**: day month year

  **Day**: `d` or `0d` or `dd`

  **Month**: `mm` or `m` or `0m` or the first three letters of the month name (all in the same case, or with the first letter upper-case)

  **Year**: `yy` or `yyyy` between 1753 and 3000 (inclusive)

  **Separator**: `-` or `/` or `<space>`

Note: 
- Only one separator type in one date
- 29th of feb is valid only on leap years
- Two digits year lie between 1950 and 2049
- Leading/Trailing whitespace are invalid

## Options
  -i, --invalid-only, only generate output for invalid dates

  -v, --valid-only, only generate output for valid dates

## Examples

  `python3 date_parser.py`

  `python3 date_parser.py -i < valid_dates.in`

  `python3 date_parser.py < mixed_dates.in > mixed.out`
  

## Windows example

  `cat invalid_dates.in | python3 date_parser.py > results.out`

  `cat invalid_dates.in | python3 date_parser.py -v`
  

## Running Unit Tests
To run unit tests use `python3 run_tests.py`
