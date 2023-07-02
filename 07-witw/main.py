import sys
import logging
from geojson import Point, Feature
import geojsonio

from witw import parse, format_dms, format_std

logging.basicConfig(level=logging.ERROR)

CHAR_QUIT = 'q'
CHAR_PRINT = 'p'

def create_feature(latitude:float, longitude:float, label:str) -> Feature:
  """
  Converts a coordinate in standard form to a geojson feature

  Args:
    latitude (float): The latitude
    longitude (float): The longitude
    label (str): The label of the coords
    
  Returns:
    Feature: The WGS84 GIS feature
  """
  logging.debug(f"Create feature: {latitude} {longitude} {label}")
  point_coords = (longitude, latitude) # Swap coords for geojson
  point_properties = {"name":label} # TODO extract names of places
  return Feature(geometry=Point(point_coords), properties=point_properties)

def main():
  """
  A program that reads a sequence of lines from stdin and, where possible, 
  converts them into GeoJSON features (with names if given) and saves those 
  as a featurecollection. 
  
  If input is given that is impossible to interpret this way, e.g., Ha, 
  tricked you! the program will write Unable to process: followed by 
  the offending input line. 
  
  Valid coordinates are displayed in the browser using geojsonio
  """
  # Intro
  print("Welcome! Input a coordinate and press enter to save it")
  print("Input 'p' to print all coordinates and exit")
  print("Input 'q' to exit without printing")

  features = []
  for line in sys.stdin:
    if line.rstrip() == CHAR_QUIT: 
      return 0
    if line.rstrip() == CHAR_PRINT:   
      break
    try:
      lat, lon, label = parse(line)
      features.append(create_feature(lat, lon, label))
      sys.stdout.write(f"{format_std(lat, lon)}\t{format_dms(lat, lon)}\t'{str.title(label)}'\n\n")
    except ValueError as err:
      logging.error(str(err))
      sys.stdout.write(f"Unable to parse:{line}\n\n")
  geojsonio.display(features)
  return 0
    
if __name__ == "__main__":
  main()