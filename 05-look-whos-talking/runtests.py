import unittest
from look_whos_talking import translate_to_māori

class TestParseDate(unittest.TestCase):
  def test_valid_dates(self):
    with open('tests.txt', 'r',encoding='utf-8') as f:
      for line in f:
        english, māori = line.rstrip().split(",")
        self.assertEqual(translate_to_māori(english), māori.lstrip())
      
  # def test_invalid_dates(self):
  #   with open('invalid.txt', 'r',encoding='utf-8') as f:
  #     for line in f:
  #       english, māori = line.split(",")
  #       with self.assertRaises(ValueError):
  #         translate_to_māori(english)

if __name__ == '__main__':
  unittest.main()
