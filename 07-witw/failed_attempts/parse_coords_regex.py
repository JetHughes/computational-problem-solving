import re

# Standard form.
std = r'^\s*(-?\d{1,2}\.\d{6}),\s*(-?\d{1,3}\.\d{6})\s*(.*)$'
# Standard form except for the number of decimal points given differs from 6.
std_wrong_dec = r'^\s*(-?\d{1,2}\.\d{1,5}),\s*(-?\d{1,3}\.\d{1,4})\s*(.*)$'
# Standard form except the comma is missing.
std_no_comma = r'^\s*(-?\d{1,2}\.\d{6})\s*(-?\d{1,3}\.\d{6})\s*(.*)$'
# Standard form, except the numbers are non-negative and followed by N or S (for latitude) and E or W (for longitude), possibly in the wrong order.
std_non_neg = r'^\s*(-?\d{1,2}\.\d{1,6})([NS])?\s*(-?\d{1,3}\.\d{1,6})([EW])?\s*(.*)$'
# "Degrees, minutes, seconds” form with or without decimal places on the seconds, and with or without the standard markers for degrees, minutes and seconds.
dms = r'^\s*(-?\d{1,3})°?\s*(-?\d{1,2})\'?\s*(-?\d{1,2}(?:\.\d+)?)?\"?\s*([NS])?\s*(-?\d{1,3})°?\s*(-?\d{1,2})\'?\s*(-?\d{1,2}(?:\.\d+)?)?\"?\s*([EW])?\s*(.*)$'
# Degrees and decimal minutes form
dms_std = r'^\s*(-?\d{2,3})\.(?\d{0,10})([NS])?\s*(-?\d{2,3})\.(?\d{0,10})([EW])?\s*(.*)$'

def parse_coord_regex(coord_str):
  if(re.match(std, coord_str)):
    print("std")
  elif(re.match(std_wrong_dec, coord_str)):
    print("std wrong dec")
  elif(re.match(std_no_comma, coord_str)):
    print("std no comma")
  elif(re.match(std_non_neg, coord_str)):
    print("std non neg")
  elif(re.match(dms, coord_str)):
    print("dms")
  elif(re.match(dms_std, coord_str)):
    print("dms std")
  else:
    raise ValueError("unable to process")
  return 0