import json
import sys
import re
import logging

logging.basicConfig(level=logging.CRITICAL)

with open('data.json', 'r',encoding='utf-8') as f:
  data_str = f.read()
data = json.loads(data_str)

regex_subject_modifier = re.compile(r' \((\d+) (incl|excl)\) ')
  
def get_subject_word(sentence:str) -> str:
  """
  Get the word part of the subject of the sentence using regex

  Args:
    sentence (str): The sentence to search
  
  Returns:
    str: The first subject word found in the sentence

  Raises:
    ValueError: If no words are found
  """
  for word in data["subject_words"]:
    if word + " " in sentence:
      return word
  raise ValueError(f"No subject words: {sentence}")

def get_subject_modifier(sentence:str) -> str:
  """
  Get the modifier part of the subject of the sentence using regex
  Should be in the format " (<number> <inclusivity>) "
  where <number> is an non negative integer, and <inclusivity> is incl or excl 

  Args:
    sentence (str): The sentence to search
  
  Returns:
    str: The modifier found if there is one with the number capped to 3
         otherwise returns an empty string
  """
  match = regex_subject_modifier.search(sentence)
  if match is None: return ""
  logging.debug(f"Modifier matches: {match.groups()}")
  number, clusivity = int(match.group(1)),  match.group(2)
  # Clamp the number so 3 we can use it to search the dictionary
  return f" ({number if number < 3 else 3} {clusivity})"

def get_subject(sentence:str) -> str:
  """
  Get the subject of the sentence

  Args:
    sentence (str): The sentence to search
  
  Returns:
    str: The subject found in the sentence

  Raises:
    ValueError: If no subject is found
  """
  word = get_subject_word(sentence)
  modifier = get_subject_modifier(sentence)
  logging.debug(f"Search subjects for: \'{word}{modifier}\'")
  try:
    # Search the dictionary of subjects for this combination of word and modifier
    return data["subjects_dict"][f"{word}{modifier}"]
  except KeyError as err:
    raise ValueError(f"Subject not in dictionary: {err}")

def get_starter_and_verb(sentence:str):
  """
  Get the verb and starter of the sentence

  Args:
    sentence (str): The sentence to search
  
  Returns:
    tuple[str, str]: The maori starter and the verb of the sentence

  Raises:
    ValueError: If no verbs are found
  """
  # Search for tense specific verbs.
  # From the tense of the verb we can also get the māori sentence starter
  for verb in data["verbs"]:
    if verb["english_present"] in sentence:
      return data["starters"]["present"], verb["māori"]
    if verb["english_future"] in sentence:
      return data["starters"]["future"], verb["māori"]
    if verb["english_past"] in sentence:
      return data["starters"]["past"], verb["māori"]
  raise ValueError(f"Verb not detected: {sentence}")

def translate_to_māori(sentence:str) -> str:
  """
  Translate a simple english sentence to māori

  Args:
    sentence (str): The sentence to translate
  
  Returns:
    str: The māori translation of the sentence
  """
  starter, verb = get_starter_and_verb(str.lower(sentence))
  subject = get_subject(str.lower(sentence))
  return f"{starter} {verb} {subject}"

def main():
  for line in sys.stdin:
    line = line.rstrip()
    if line == 'q': break
    try:
      result = translate_to_māori(line)
      print(result)
      logging.debug(f"{line}: {result}")
    except ValueError as err:
      print("INVALID")
      logging.error(f"{line}: INVALID: {str(err)}")

if __name__ == '__main__':
  main()