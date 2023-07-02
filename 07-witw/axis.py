import enum
class Axis(enum.Enum):
  LATITUDE_POSITIVE = 0
  LATITUDE_NEGATIVE = 1
  LONGITUDE_POSITIVE = 2
  LONGITUDE_NEGATIVE = 3
  
  def sign(self) -> int:
    return -1 if self in (Axis.LATITUDE_NEGATIVE, Axis.LONGITUDE_NEGATIVE) else 1
  
  def dir(self) -> str:
    return "lat" if self in (Axis.LATITUDE_NEGATIVE, Axis.LATITUDE_POSITIVE) else "lon"
  
  def get_axis(value:str):
    directions= {'n':Axis.LATITUDE_POSITIVE,'s':Axis.LATITUDE_NEGATIVE,
              'e':Axis.LONGITUDE_POSITIVE,'w':Axis.LONGITUDE_NEGATIVE,
              'north':Axis.LATITUDE_POSITIVE,'south':Axis.LATITUDE_NEGATIVE,
              'east':Axis.LONGITUDE_POSITIVE,'west':Axis.LONGITUDE_NEGATIVE}
    return directions.get(value)