Author: Jet Hughes

# Coordinate Conversion and GeoJSON Generation
This Python script reads a sequence of lines from standard input and converts valid coordinates into GeoJSON features. The features, along with their names (if provided), are saved as a FeatureCollection. Invalid input lines are flagged and displayed as errors.

# Requirements
To run the script, make sure you have the following dependencies installed:
- Python 3.x
- geojson library
- geojsonio library

You can install the dependencies using pip:
```pip install geojson geojsonio```

# Usage
Use `python main.py` to run the script. 
Type in each coordinate. 
Input 'p' to print the coordinates and exit
Input 'q' to quit the program without printing the coordinates. 

You can also pipe a file into stdin to read a list of coordinates:
```cat coordinates.in | python main.py```
