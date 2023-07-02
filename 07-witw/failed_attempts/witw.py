import argparse
import sys
import re
from old_attempts.parse_coords_regex import parse_coord_regex
from witw import get_digits, count_digits
from old_attempts.parse_scan import scan_input

def std_form(coord_str):
  # std form 90.000000, 180.000000
  # accepts: 
  # - coords in the wrong order and possibly specified by N, E, S, W
  # - wrong number of decimals
  if ", " in coord_str:
    lat_str, lon_str = coord_str.split(", ")

    if "E" in lat_str or "W" in lat_str: # if the coords are in the wrong order swap them
      tmp = lon_str
      lon_str = lat_str
      lat_str = tmp

    lat = float(lat_str.replace("S", "-").replace("N", ""))
    lon = float(lon_str.replace("W", "-").replace("E", ""))
    return lat, lon
  else:
    raise ValueError("std No comma")

def no_comma_std(coord_str):
  split = re.split(" ", coord_str)
  digits = get_digits(split)
  if len(digits) == 2:
    lat = digits[0]
    lon = digits[1]
  else:
    raise ValueError("no comma, not two digits")
  return lat, lon

def convert_dms_to_standard(dms_coords):
  """
  Converts degrees minutes seconds (DMS) coordinates to standard form.

  :param dms_coords: A list of DMS coordinates in the format [latitude, longitude].
  :return: A tuple of standard coordinates in the format (latitude, longitude).
  """
  lat_dms = dms_coords[0]
  lat_degrees = lat_dms[0]
  lat_minutes = lat_dms[1]
  lat_seconds = lat_dms[2]
  lat_decimal = lat_degrees + lat_minutes / 60 + lat_seconds / 3600

  lon_dms = dms_coords[1]
  lon_degrees = lon_dms[0]
  lon_minutes = lon_dms[1]
  lon_seconds = lon_dms[2]
  lon_decimal = lon_degrees + lon_minutes / 60 + lon_seconds / 3600

  return lat_decimal, lon_decimal

def dms(coord_str):
  # 10°00'00.0"N 10°00'00.0"E
  # parts = coord_str.rsplit("°|'|.")
  dms = re.split("\'|\"|\°| ", coord_str)
  for p in dms:
    print(f"{p},", end="")
  # if there is an indicator of the direction
  if "N" in dms or "E" in dms or "S" in dms or "W" in dms:
    # and if there are six sigits
    digit_count = count_digits(dms)
    if digit_count == 6:
      # convert from NESW to positive or negative values
      if dms[3] == "S" or dms[3] =="W":
        dms[0] = -dms[0]
      if dms[7] == "S" or dms[7] == "S":
        dms[4] = -dms[4]

      # if they are in the wrong order swap them
      if (dms[3] == "N" or dms[3] == "S"): 
        lat, lon = convert_dms_to_standard([[float(dms[0]), float(dms[1]), float(dms[2])], [float(dms[4]), float(dms[5]), float(dms[6])]])
      else:
        lat, lon = convert_dms_to_standard([[float(dms[4]), float(dms[5]), float(dms[6])]], [float(dms[0]), float(dms[1]), float(dms[2])])
      return lat, lon
    else:
      raise ValueError(f"dms Invalid digit count ({digit_count})")
  else:
    raise ValueError("dms no Labels")

def degrees_and_decimal_minutes(coord_str):
  raise ValueError


forms = [std_form, no_comma_std, dms, degrees_and_decimal_minutes]

def parse_coords(coord_str):
  for form in forms:
    try:
      lat, long = form(coord_str)
      return lat, long
    except ValueError as err:
      print(err)
      continue
      # Standard form except for the number of decimal points given differs from 6.
      # Standard form except the comma is missing.
      # Standard form, except the numbers are non-negative and followed by N or S (for latitude) and E or W (for longitude), possibly in the wrong order.
      # "Degrees, minutes, seconds” form with or without decimal places on the seconds, and with or without the standard markers for degrees, minutes and seconds.
      # Degrees and decimal minutes form

  raise ValueError("Unable to process")

def parse_args():
  parser = argparse.ArgumentParser()
  parser.add_argument('-r', '--use-regex', action='store_true',
                      help='use regex to process coords')
  parser.add_argument('-s', '--use-scan', action='store_true',
                      help='use scan to process coords')
  return parser.parse_args()

def save_coord(lat, lon):
  if -90 <= lat <= 90 and -180 <= lon <= 180:
    # Convert to standard form
    lat_str = f"{abs(lat):.6f} {'S' if lat < 0 else 'N'}"
    lon_str = f"{abs(lon):.6f} {'W' if lon < 0 else 'E'}"
    print(f"{lat_str}, {lon_str}")
    return f"{lat_str}, {lon_str}"
  raise ValueError("Unable to process")

def main():
  args = parse_args()
  for line in sys.stdin:
    coord_str = line.rstrip("\n")
    try:
      if(args.use_regex):
        lat, lon = parse_coord_regex(coord_str)
      elif(args.use_scan):
        lat, lon = scan_input(coord_str)
      else:
        lat, lon = parse_coords(coord_str)
      save_coord(lat, lon)
    except ValueError as err:
      # save_coord(None, None)
      print(err)

if __name__ == "__main__":
  main()
