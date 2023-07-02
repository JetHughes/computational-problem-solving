import sys

# Function to check if a year is a leap year
def is_leap_year(year):
  # Leap year if (divisible by 4 but not by 100) OR (divisible by 400)
  if (year % 4 == 0 and not year % 100 == 0) or year % 400 == 0: 
    return True
  return False

# Generates all valid test cases for dateChecker.py
SEPARATORS = {"/", "-", " "}
MONTHS = ["jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"]
def gen_valid():
  # for every valid date i.e., each day, month, and year
    for day_num in range(1, 32):
      for month_num in range(1, 13):
        for year_num in range(1753, 3001):
              # find all the valid strings that represent the day, month, and year

              # guard statements to exclude invalid dates
              if month_num == 2 and day_num > 29:
                break
              elif day_num > 30 and (month_num == 4 or month_num == 6 or month_num == 9 or month_num == 11):
                break
              elif day_num == 29 and month_num == 2 and not is_leap_year(year_num):
                break

              # day number/zero padded day num if less than 10
              day_strs = {day_num}
              if day_num < 10: day_strs.add(f'0{day_num}')

              # month number/zero padded month number/every valid abbreviation
              month_strs = {month_num, MONTHS[month_num-1], MONTHS[month_num-1].upper(), MONTHS[month_num-1].title()}
              if month_num < 10: month_strs.add(f'0{month_num}')

              # four digit year number/two digit number if between 1950 and 2049
              year_strs = {year_num}
              if 1950 >= year_num >= 2049:
                year_strs.add(str(year_num).removeprefix("20|19"))

              # print every combination of string with each separator
              for sep_str in SEPARATORS:
                for day_str in day_strs:
                  for month_str in month_strs:
                    for year_str in year_strs:
                      sys.stdout.write(f'{day_str}{sep_str}{month_str}{sep_str}{year_str}\n')

gen_valid()