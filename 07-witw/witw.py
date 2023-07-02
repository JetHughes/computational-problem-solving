import logging
import re
from axis import Axis

logging.basicConfig(level=logging.DEBUG)

regex_label = re.compile(r'([A-Za-z\s,]{2,}+$)')
regex_number = re.compile(r'(-?\d+(\.\d+)?)([°\'\"]?)')
regex_directions = re.compile(r'\b(n|s|e|w|north|east|south|west)\b')

# TODO allow for direction indicators in labels: e.g., "North Dunedin"
# TODO investigate regex.finditer() 
# TODO decide if I want to be able to parse 10° 10'
# TODO If the numbers are only valid in the opposite order swap them
# TODO check if there special characters ° or ' following the numbers?
# TODO more analysis on input with more than one direction
# TODO allow to only one half of the coordinate and assume equal

def parse(input:str) -> tuple[float, float, str]:
  """
  Searches a line to find coordinates

  Args:
    input (str): the line to search

  Returns:
    tuple[float, float, str]
  """
  input = str.lower(input.rstrip())
  label = get_label(input)
  values = get_values(input)
  axes = get_axes(input)

  # Assume the format based on the amount of numbers
  # Standard for
  if len(values) == 2: 
    return coords_std(values, axes[0], axes[1], label)
  
  # Degrees and decimal minutes
  if len(values) == 4: 
    return coords_ddm(values, axes[0], axes[1], label)
  
  # Degrees, Minutes, Seconds
  if len(values) == 6:
    return coords_dms(values, axes[0], axes[1], label)
  
  # Otherwise 
  raise ValueError("Unable to parse")

def format_std(latitude:float, longitude:float) -> str:
  return f"{latitude:.6f}, {longitude:.6f}"

def format_dms(latitude:float, longitude:float) -> str:
  """
  Converts latitude and longitude from standard form to degrees, minutes, 
  and seconds format, and prints the coordinates in the desired output format.

  Args:
    latitude (float): The latitude coordinate in decimal format.
    longitude (float): The longitude coordinate in decimal format.

  Returns:
    str: The coordinates in degrees, minutes, and seconds format.
  """
  def convert(value:float):
    degrees = int(abs(value))
    minutes = int((abs(value) - degrees) * 60)
    seconds = round((abs(value) - degrees - minutes / 60) * 3600, 1)
    return f"{degrees:02d}°{minutes:02d}'{seconds:04.1f}\""
  lat_dir = f"{'S' if latitude < 0 else 'N'}"
  lon_dir = f"{'W' if longitude < 0 else 'E'}"
  return f"{convert(latitude)}{lat_dir} {convert(longitude)}{lon_dir}"

def get_label(input) -> str:
  # Search for a label at the end of the input
  label_match = regex_label.search(input)
  logging.debug(f"Label match: {label_match}")
  if label_match is None: return ""
  label = label_match.group(0)


  # Remvove direction indicators and surrounding commas or spaces
  return regex_directions.sub("", label).strip(",| ")

def get_values(input) -> list[float]:
  """
  Extracts valid values from the list of number matches

  Args:
    number_matches (list[any]): The list of number regex matches 

  Returns:
    tuple[list[float], int]
  Raises:
    ValueError: if there are less than two matches
    ValueError: if there is an uneven number of matches
  """
  # Search input for numbers using regex
  number_matches = regex_number.findall(input)
  logging.debug(f"numbers: {number_matches}")

  # Perform checks on the number of matches
  if len(number_matches) < 2:
    raise ValueError("Not enough numbers")
  if len(number_matches) % 2 != 0:
    raise ValueError("Uneven amount of numbers")

  # covert each regex group to a float 
  # e.g., ('33.8688', '.8688') --> 33.8688
  values = list(map(lambda match: float(match[0]), number_matches))
  logging.debug(f"Values: {values}")
  return values

def get_axes(input) -> tuple[Axis, Axis]:
  """
  Retrieves two axes from the list of direction matches. 
  If there are no direcions assume Latitude positive and Longitude negative

  Args:
    direction_matches (list[any]): The list of direction matches

  Returns:
    tuple[Axis, Axis]: A tuple containing the two Axes

  Raises:
    ValueError: If there are more than two directions or the directions are on the same axis
  """
  # Search input for directions using regex
  direction_matches = regex_directions.findall(input)
  logging.debug(f"Direction Matches: {direction_matches} Len:{len(direction_matches)}")
  
  # If there are no directions assume Latitude positive and Longitude negative
  if len(direction_matches) == 0:
    axis1, axis2 = Axis.LATITUDE_POSITIVE, Axis.LONGITUDE_POSITIVE
    logging.debug(f"Axes: {axis1} {axis2}")
    return axis1, axis2

  # If we have only one direction infer the other one
  if len(direction_matches) == 1:
    axis1 = Axis.get_axis(direction_matches[0])
    axis2 = Axis.LATITUDE_POSITIVE if axis1.dir == "lon" else Axis.LONGITUDE_POSITIVE
    logging.debug(f"Axes: {axis1} {axis2}")
    return axis1, axis2

  # If we have four directions,
  # assume we are trying to parse:
  # 40 d 26 m 47 s N, 79 d 58 m 56 s W
  # So take the 2nd and 4th coordinate
  if len(direction_matches) == 4:
    axis1 = Axis.get_axis(direction_matches[1])
    axis2 = Axis.get_axis(direction_matches[3])
    logging.debug(f"Axes: {axis1} {axis2}")
  
  # Otherwise take only the first two
  axis1 = Axis.get_axis(direction_matches[0])
  axis2 = Axis.get_axis(direction_matches[1])
  logging.debug(f"Axes: {axis1} {axis2}")


  # If directions are both lat or both lon something is wrong
  if axis1.dir() == axis2.dir():
    raise ValueError("Directions share the same axis")
  return axis1, axis2

def coords_std(values:list[float], axis1:Axis, axis2:Axis, label:str) -> tuple[float, float, str]:
  """
  Calculates the latitude and longitude based on the input values and directions.

  Args:
    value1 (float): The first value representing either latitude or longitude.
    direction1 (str): The axis of the first number.
    value2 (float): The second value representing either latitude or longitude.
    direction2 (str): The axis of the second number.
    label (str): The label of the coords

  Returns:
    tuple[float, float]: A tuple containing the calculated latitude and longitude.
  """
  logging.debug("Parsing coordinates in standard form...")
  value1 = values[0] * axis1.sign()
  value2 = values[1] * axis2.sign()
  return coords_valid(value1, value2, axis1, label)

def coords_dms(values:list[float], axis1:Axis, axis2:Axis, label:str) -> tuple[float, float, str]:
  """
  Converts degrees minutes seconds (DMS) coordinates to standard form.
  If degrees or minutes have decimal points ignore them

  Args:
    values (list[float]): the list of 6 floats representing the degrees, minutes, and seconds of each coord
    axis1 (Axis): the axis associated with the first three values
    axis2 (Axis): the axis associated with the second three values
    label (str): The label of the coords

  Returns:
    tuple[float, float]: the values converted to std form
  """
  logging.debug("Parsing coordinates in DMS form...")
  value1 = axis1.sign() * (int(values[0]) + int(values[1]) / 60 + values[2] / 3600)
  value2 = axis2.sign() * (int(values[3]) + int(values[4]) / 60 + values[5] / 3600)
  return coords_valid(value1, value2, axis1, label)

def coords_ddm(values:list[float], axis1:Axis, axis2:Axis, label:str) -> tuple[float, float, str]:
  """
  Converts degrees and decimal minutes (DDM) coordinates to standard form.
  If degrees has decimal points ignore them

  Args:
    values (list[float]): the list of 4 floats representing the degrees and minutes of each coord
    axis1 (Axis): the axis associated with the first two values
    axis2 (Axis): the axis associated with the second two values
    label (str): The label of the coords

  Returns:
    tuple[float, float]: the values converted to std format
  """
  logging.debug("Parsing coordinates in DDM form...")
  value1 = axis1.sign() * (int(values[0]) + values[1] / 60)
  value2 = axis2.sign() * (int(values[2]) + values[3] / 60)
  return coords_valid(value1, value2, axis1, label)

def coords_valid(lat:float, lon:float, axis1:Axis, label:str) -> tuple[float, float, str]:
  """
  Checks the validity of latitude and longitude values.

  Args:
    lat (float): The latitude value.
    lon (float): The longitude value.
    label (str): The label of the coords

  Returns:
    tuple[float, float, str]: The coordinates and their label
  """
  # Check ranges
  if not (-90 <= lat <= 90): 
    raise ValueError("Latitude out of range")
  if not (-180 <= lon <= 180):
    raise ValueError("Longitude out of range")
  
  # Can add more checks here
  
  # Return coords in the correct order
  return (lat, lon, label) if axis1.dir() == "lat" else (lon, lat, label)