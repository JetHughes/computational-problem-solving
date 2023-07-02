import unittest
import date_parser

class TestDateCoherence(unittest.TestCase):
  def test_valid_date(self):
    self.assertIsNone(date_parser.check_date_coherence(1, 1, 2022))

  def test_invalid_day_for_february(self):
    with self.assertRaises(ValueError):
      date_parser.check_date_coherence(30, 2, 2022)

  def test_invalid_day_for_month(self):
    with self.assertRaises(ValueError):
      date_parser.check_date_coherence(31, 4, 2022)

  def test_invalid_day_for_non_leap_year(self):
    with self.assertRaises(ValueError):
      date_parser.check_date_coherence(29, 2, 2023)

class TestValidDay(unittest.TestCase):
  def test_valid_day(self):
    self.assertEqual(date_parser.valid_day('1'), 1)
    self.assertEqual(date_parser.valid_day('31'), 31)
    self.assertEqual(date_parser.valid_day('01'), 1)

  def test_invalid_day(self):
    with self.assertRaises(ValueError):
      date_parser.valid_day('0')
    with self.assertRaises(ValueError):
      date_parser.valid_day('00')
    with self.assertRaises(ValueError):
      date_parser.valid_day('32')
    with self.assertRaises(ValueError):
      date_parser.valid_day('abc')

class TestValidMonth(unittest.TestCase):
  def test_valid_month_number(self):
    self.assertEqual(date_parser.valid_month('1'), 1)
    self.assertEqual(date_parser.valid_month('12'), 12)

  def test_valid_month_abbreviation(self):
    self.assertEqual(date_parser.valid_month('jan'), 1)
    self.assertEqual(date_parser.valid_month('Feb'), 2)
    self.assertEqual(date_parser.valid_month('MAR'), 3)

  def test_invalid_month(self):
    with self.assertRaises(ValueError):
      date_parser.valid_month('00')
    with self.assertRaises(ValueError):
      date_parser.valid_month('13')
    with self.assertRaises(ValueError):
      date_parser.valid_month('junk')
    with self.assertRaises(ValueError):
      date_parser.valid_month('a')
    with self.assertRaises(ValueError):
      date_parser.valid_month('JaN')
    with self.assertRaises(ValueError):
      date_parser.valid_month('jaN')
    with self.assertRaises(ValueError):
      date_parser.valid_month('jAn')

class TestValidYear(unittest.TestCase):
  def test_valid_year(self):
    self.assertEqual(date_parser.valid_year('2000'), 2000)
    self.assertEqual(date_parser.valid_year('50'), 1950)
    self.assertEqual(date_parser.valid_year('49'), 2049)
    self.assertEqual(date_parser.valid_year(str(date_parser.MIN_VALID_YEAR)), date_parser.MIN_VALID_YEAR)
    self.assertEqual(date_parser.valid_year(str(date_parser.MAX_VALID_YEAR)), date_parser.MAX_VALID_YEAR)
    
  def test_invalid_year(self):
    with self.assertRaises(ValueError):
      date_parser.valid_year('abcd')
    with self.assertRaises(ValueError):
      date_parser.valid_year('12345')
    with self.assertRaises(ValueError):
      date_parser.valid_year(str(date_parser.MIN_VALID_YEAR - 1))
    with self.assertRaises(ValueError):
      date_parser.valid_year(str(date_parser.MAX_VALID_YEAR + 1))

class TestValidSeparators(unittest.TestCase):
  # Testing regex pattern:
  # ^\w+([-/ ])\w+\1\w+$
  # should match any 3 strings of alphanumeric characters
  # separated exclusively by "/" "-" or "<space>"

  def test_valid_separators_valid_dates(self):
    self.assertIsNone(date_parser.check_valid_separators("03/03/2023"))
    self.assertIsNone(date_parser.check_valid_separators("03 03 2023"))
    self.assertIsNone(date_parser.check_valid_separators("03-03-2023"))

  def test_valid_separators_invalid_dates(self):
    self.assertIsNone(date_parser.check_valid_separators("003/03/2023"))
    self.assertIsNone(date_parser.check_valid_separators("03 030 2023"))
    self.assertIsNone(date_parser.check_valid_separators("03-03-feb"))
    self.assertIsNone(date_parser.check_valid_separators("03/mar/2023"))
    self.assertIsNone(date_parser.check_valid_separators("03 03 23"))
    self.assertIsNone(date_parser.check_valid_separators("3-03-2023"))

  def test_mismatching_separators(self):
    with self.assertRaises(ValueError):
      date_parser.check_valid_separators("03/03 2020")
    with self.assertRaises(ValueError):
      date_parser.check_valid_separators("03/03-2020")
    with self.assertRaises(ValueError):
      date_parser.check_valid_separators("03/03-2020")

  def test_extra_whitespace(self):
    with self.assertRaises(ValueError):
      date_parser.check_valid_separators(" 03-03-2020")
    with self.assertRaises(ValueError):
      date_parser.check_valid_separators("03/03/2020 ")
    with self.assertRaises(ValueError):
      date_parser.check_valid_separators("03 03  2020")
    with self.assertRaises(ValueError):
      date_parser.check_valid_separators("03 -03-2020")    

class TestLeapYear(unittest.TestCase):
  def test_valid_leap_year(self):
    self.assertTrue(date_parser.is_leap_year(2000))
    self.assertTrue(date_parser.is_leap_year(2024))
  
  def test_invalid_leap_year(self):
    self.assertFalse(date_parser.is_leap_year(2100))
    self.assertFalse(date_parser.is_leap_year(2003))

class TestParseDate(unittest.TestCase):
  def test_valid_dates(self):
    with open("./test_data/oc/valid_formats.in") as valid_dates:
      for date in valid_dates:
        self.assertEqual(len(date_parser.parse_date(date)), 3)
  
  def test_invalid_dates(self):
    with open("./test_data/oc/invalid_tests.in") as invalid_dates:
      for date in invalid_dates:
        with self.assertRaises(ValueError):
          date_parser.parse_date(date)

if __name__ == '__main__':
  unittest.main()
