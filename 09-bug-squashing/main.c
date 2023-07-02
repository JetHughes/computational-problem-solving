#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const int MAX_RECORDS = 100;

struct Record
{
  char *firstName;
  char *lastName;
  char *phone;
  char *emailAddress;
};

enum Field
{
  FIRST_NAME,
  LAST_NAME,
  PHONE,
  EMAIL_ADDRESS
};

int searchRecords(struct Record **records, char *searchStr, enum Field field, int numRecords)
{
  int numMatches = 0;
  for (int i = 0; i < numRecords; i++)
  {
    char *fieldValue = NULL;
    switch (field)
    {
    case FIRST_NAME:
      fieldValue = records[i]->firstName;
      break;
    case LAST_NAME:
      fieldValue = records[i]->lastName;
      break;
    case PHONE:
      fieldValue = records[i]->phone;
      break;
    case EMAIL_ADDRESS:
      fieldValue = records[i]->emailAddress;
      break;
    }
    if (strcasecmp(fieldValue, searchStr) == 0)
    {
      numMatches++;
    }
  }
  return numMatches;
}

void sortRecords(struct Record **records, enum Field field, int numRecords)
{
  for (int i = 0; i < numRecords; i++)
  {
    for (int j = 0; j < numRecords; j++)
    {
      int cmp;
      switch (field)
      {
      case FIRST_NAME:
        cmp = strcmp(records[i]->firstName, records[j]->firstName);
        break;
      case LAST_NAME:
        cmp = strcmp(records[i]->lastName, records[j]->lastName);
        break;
      case PHONE:
        cmp = strcmp(records[i]->phone, records[j]->phone);
        break;
      case EMAIL_ADDRESS:
        cmp = strcmp(records[i]->emailAddress, records[j]->emailAddress);
        break;
      }
      if (cmp < 0)
      {
        struct Record *record = records[i];
        records[i] = records[j];
        records[j] = record;
      }
    }
  }
}

void printRecordsField(struct Record **records, enum Field field, int numRecords)
{
  for (int i = 0; i < numRecords; i++)
  {
    printf("%d:", i + 1);
    switch (field)
    {
    case FIRST_NAME:
      printf("  firstName: %s\n", records[i]->firstName);
      break;
    case LAST_NAME:
      printf("  lastName: %s\n", records[i]->lastName);
      break;
    case PHONE:
      printf("  phone: %s\n", records[i]->phone);
      break;
    case EMAIL_ADDRESS:
      printf("  emailAddress: %s\n", records[i]->emailAddress);
      break;
    }
  }
}

int readRecordsFromFile(char *filename, struct Record **records, int *numRecords)
{
  // Open File
  FILE *f = fopen(filename, "r");
  if (f == NULL)
  {
    printf("Error: Failed to open file\n");
    return 1;
  }

  // Read File
  int count = 0;
  while (count < MAX_RECORDS && !feof(f))
  {
    // Allocate memory
    struct Record *record = malloc(sizeof(*record));
    record->firstName = malloc(80 * sizeof(char));
    record->lastName = malloc(80 * sizeof(char));
    record->phone = malloc(15 * sizeof(char));
    record->emailAddress = malloc(80 * sizeof(char));

    // Attempt to read line
    if (fscanf(f, "%s %s %s %s", record->firstName, record->lastName, record->phone, record->emailAddress) == 4)
    {
      records[count] = record;
      count++;
      printf("Saved Record: %s %s %s %s\n", record->firstName, record->lastName, record->phone, record->emailAddress);
    }
    else // If the line fails to process, free the memory we allocated
    {
      printf("Invalid record: memory freed\n");
      free(record->firstName);
      free(record->lastName);
      free(record->phone);
      free(record->emailAddress);
      free(record);
    }
  }
  fclose(f);
  *numRecords = count;
  printf("Read file complete\n\n");
  return 0;
}

void freeRecords(struct Record **records, int numRecords)
{
  for (int i = 0; i < numRecords; i++)
  {
    free(records[i]->firstName);
    free(records[i]->lastName);
    free(records[i]->phone);
    free(records[i]->emailAddress);
    free(records[i]);
  }
  free(records);
}

int main(int argc, char **argv)
{
  // Read Records
  struct Record **records = (struct Record **)malloc(MAX_RECORDS * sizeof(struct Record **));
  int numRecords = 0;
  if (readRecordsFromFile(argv[1], records, &numRecords) != 0)
  {
    freeRecords(records, numRecords);
    return 1;
  }

  // Print Records
  sortRecords(records, FIRST_NAME, numRecords);
  printRecordsField(records, FIRST_NAME, numRecords);
  printRecordsField(records, LAST_NAME, numRecords);
  printRecordsField(records, EMAIL_ADDRESS, numRecords);
  printRecordsField(records, PHONE, numRecords);

  // Search Records
  char buffer[100];
  int command = 10;
  while (command != 0)
  {
    char *val = malloc(100 * sizeof(val[0]));
    printf("\nPlease enter a command (1=first name, 2=last name, 3=email, 4=phone, 0=exit):\n");
    fgets(buffer, 100, stdin);
    command = atoi(buffer);
    if (command == 0)
    {
      break;
    }

    printf("Please enter a search value:\n");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(val, buffer);

    enum Field field;
    switch (command)
    {
    case 1:
      printf("looking for firstname %s\n", val);
      field = FIRST_NAME;
      break;
    case 2:
      printf("looking for lastname %s\n", val);
      field = LAST_NAME;
      break;
    case 3:
      printf("looking for email %s\n", val);
      field = EMAIL_ADDRESS;
      break;
    case 4:
      printf("looking for phone %s\n", val);
      field = PHONE;
    default:
      break;
    }
    sortRecords(records, field, numRecords);
    int numMatches = searchRecords(records, val, field, numRecords);
    printf("found %d matches\n", numMatches);
  }

  // Free memory and exit
  freeRecords(records, numRecords);
  return 0;
}