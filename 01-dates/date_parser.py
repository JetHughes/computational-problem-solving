"""A script to check the format of a list of dates

Uses sys and argparse to write and read data. Uses regex to assist with parsing. 
Takes date strings from stdin separated by newlines and outputs them in the 
format 'dd MMM yyyy' or 'INVALID' if the input string is invalid.
  
Example Usage: 
  python date_parser.py
  python date_parser.py < valid_tests.in
  cat valid_tests.in | python date_parser.py
"""

import sys
import re
import argparse

MIN_VALID_YEAR = 1753
MAX_VALID_YEAR = 3000
SHORT_MONTHS = {4, 6, 9, 11}
MONTHS = {
  'jan':1, 'feb':2, 'mar':3, 'apr':4, 'may':5, 'jun':6, 'jul':7, 'aug':8, 'sep':9, 'oct':10, 'nov':11, 'dec':12, 
  'JAN':1, 'FEB':2, 'MAR':3, 'APR':4, 'MAY':5, 'JUN':6, 'JUL':7, 'AUG':8, 'SEP':9, 'OCT':10, 'NOV':11, 'DEC':12, 
  'Jan':1, 'Feb':2, 'Mar':3, 'Apr':4, 'May':5, 'Jun':6, 'Jul':7, 'Aug':8, 'Sep':9, 'Oct':10, 'Nov':11, 'Dec':12,
}
MONTH_ABBREVIAION = ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 'JUL', 'AUG', 'SEP', 'OCT', 'NOV', 'DEC']

# Regex patterns
SEPARATOR_PATTERN = r'^(\w+)([-/ ])(\w+)(\2)(\w+)$' 
DAY_MONTH_DIGIT_PATTERN = r'^(0?[0-9]|[0-9]{2})$' 
YEAR_PATTERN = r'^([0-9]{4}|[0-9]{2})$' # two or four digits

def is_leap_year(year):
  return (year % 4 == 0 and not year % 100 == 0) or year % 400 == 0

def check_valid_separators(date_str):
  """Checks for a date string with valid separators (-, /, or space).
  Raises a ValueError if the separators are invalid.
  Valid formats are "x/x/x" or "x-x-x" or "x x x" where "x" is at least one alphanumeric character
  
  Args:
    date_str (str): A string which could be a date.
      
  Raises:
    ValueError: If the separators in the date string are not valid.
  """
  match = re.match(SEPARATOR_PATTERN, date_str)
  if not match:
    raise ValueError("Invalid Separators")  

def valid_day(day_str):
  """Validates a day in string format and returns the integer value of the day.
  Valid formats are "d" or "0d" or "dd"
  Must be between 1 and 31 (inclusive)

  Args:
    day_str (str): The day string to validate.

  Returns:
    int: The integer value of the day.

  Raises:
    ValueError: If the day string has invalid format or is out of range
  """
  if not re.match(DAY_MONTH_DIGIT_PATTERN, day_str):
    raise ValueError("Invalid day format")
  day = int(day_str)
  if not 1 <= day <= 31:
    raise ValueError('Day out of range')  
  return day
  
def valid_month(month_str):
  """Validates a month in string format and returns the integer value of the month.
  Valid formats are "m" or "0m" or "mm" 0r "aaa" or "Aaa" or "AAA"
  Must be between 1 and 12 or be the first three letters of the name of a month

  Args:
    month_str (str): The month string to validate.

  Returns:
    int: The integer value of the month.

  Raises:
    ValueError: If the month string has invalid format or is out of range
  """

  # Check if the date is given as digits
  if re.match(DAY_MONTH_DIGIT_PATTERN, month_str):
    month = int(month_str)
    if month < 1 or month > 12:
      raise ValueError('Month out of range')  
  # Check if the date is given as a three letter abbreviation
  else:
    month = MONTHS.get(month_str)
    if month is None:
      raise ValueError('Invalid month format')
  return month   

def valid_year(year_str):
  """Validates a year in string format and returns year as an Integer.
  
  - Valid formats are "0y" or "yy" or "yyyy"
  - Must be between 1753 and 3000 (inclusive)

  Checks if the format is correct using a regex. 
  If a two digit year is given, it is converted to a four digit year 
  that lies between 1950 and 2049

  Args:
    year_str (str): The year string to validate.

  Returns:
    int: The integer value of the year.

  Raises:
    ValueError: If the year string has invalid format or is out of range
  """
  # Check that year is a valid format
  if not re.match(YEAR_PATTERN, year_str):
    raise ValueError("Invalid year format")
  year = int(year_str)
  # Correct two digit years
  if len(year_str) == 2:
    year += 1900 if year >= 50 else 2000
  # Check that the date is within the given range
  if year < MIN_VALID_YEAR or year > MAX_VALID_YEAR:
    raise ValueError('Year out of range')
  return year

def check_date_coherence(day, month, year):
  """For a given day, month and year, check that the day falls within the month.

  Given the month lies between 1 and 31 the date is invalid when:
  - the month is feb and the day is more than 29
  - the month is feb, the day is 29, and it is not a leap year
  - the month is short (4, 6, 9, 11) and the day is more than 30

  Args:
    day (int): The day to validate.
    month (int): The month to validate.
    year (int): The year to validate.

  Raises:
    ValueError: If the given combination of day, month, and year is not coherent
  """
  # Check that the day and the month and year together are valid
  if month == 2 and day > 29:
    raise ValueError('Invalid day for February')
  elif day > 30 and month in SHORT_MONTHS:
    raise ValueError('Invalid day for month')
  elif day == 29 and month == 2 and not is_leap_year(year):
    raise ValueError('Invalid day for non-leap year')  

def parse_date(date_str): 
  """Parses a date string and returns its separate parts as Integer values

  Firstly, check if the separators are valid, then extract each component 
  of the date. Next, year that the day, year, and month have correct format 
  and are valid. Finally check that the combination of components is coherent.

  Args:
    date_str (str): The date string to parse.

  Returns:
    tuple:
  """
  check_valid_separators(date_str)
  day_str, month_str, year_str = re.split("-|\/| ", date_str)
  day = valid_day(day_str)
  month = valid_month(month_str)
  year = valid_year(year_str)
  check_date_coherence(day, month, year)  
  return day, month, year

def print_date(day, month, year):
  """Print a date string in the format dd MMM yyyy
  E.g. 03 MAR 2023

  Args:
    day (int): The day to print
    month (int): The month to print
    year (int): The year to print
  """
  day_str = str(day).zfill(2)
  month_str = MONTH_ABBREVIAION[month-1]
  year_str = str(year)
  sys.stdout.write(f'{day_str} {month_str} {year_str}\n')

def print_error(line, err):
  """Print an invalid date string to stdout, and the reason to stderr
  E.g.,
  00 mar 2023 - INVALID
  Date out of range

  Args:
    line (string): The invalid date
    err (string): The reason the date is invalid
  """
  sys.stdout.write(f'{line} - INVALID\n')
  sys.stderr.write(f'{str(err)}\n')  

def parse_args():
  """Parses command line arguments

  The program accepts two optional arguments: '--invalid-only' or '-i' to output only invalid date strings,
  and '--valid-only' or '-v' to output only valid date strings.

  Returns:
    An argparse Namespace object with the flags passed in as attributes.
  """
  parser = argparse.ArgumentParser()
  parser.add_argument('-i', '--invalid-only', action='store_true',
                      help='Print only invalid dates')
  parser.add_argument('-v', '--valid-only', action='store_true',
                      help='Print only valid dates')
  return parser.parse_args()

def main():
  """Reads date strings from standard input, parses them, and outputs them in a standard format.

  This code was written with the assistance of ChatGPT, an AI language model trained by OpenAI.
  
  Input: Date strings separated by newlines, from standard input
  Output: Date strings in the format 'dd MMM yyyy' or 'INVALID' if the input string is invalid
  """
  args = parse_args()
  for line in sys.stdin:
    line = line.rstrip("\n")
    try:
      day, month, year = parse_date(line)
      if not args.invalid_only: 
        print_date(day, month, year)
    except ValueError as err:
      if not args.valid_only:
        print_error(line, err)

if __name__ == '__main__':
  main()