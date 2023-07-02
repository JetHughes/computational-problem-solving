def scan_input(coord_str):
  matches = {" ", "°", "\'", "\"", "N", "E", "S", "W"}
  for i in range(0, len(coord_str)):
    if coord_str[i] in matches:
      do_stuff_with_match(match, prev_chars)
  return 0

def process_char(char):
  