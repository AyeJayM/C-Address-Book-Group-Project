#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //This is commented out per proffesor's instructions on Teams
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book) //Kim's Code
{
	int ret = access( "addressbook.csv", F_OK);

	if (ret == 0)
	{
		address_book->fp = fopen("addressbook.csv", "r");
		address_book->list = (malloc) (sizeof(ContactInfo) * 30);
		address_book->count = 0;
    if (address_book->fp == NULL)
    {
      return e_fail;
    }
    const char s[2] = ",";
    char line[500];
    char *token;
    int i;
    while(fgets(line, sizeof line, address_book->fp) != NULL)
    {
        token = strtok(line, s);
        ContactInfo c;
        strcpy(c.name[0], token);
        for(i=0;i<5;i++)
        {
          token = strtok(NULL,s);
          strcpy(c.phone_numbers[i], token);    
        }
        for(i=0;i<5;i++)
        {
          token = strtok(NULL,s);
          strcpy(c.email_addresses[i], token);    
        }
        token = strtok(NULL,s);
        c.si_no = atoi(token);
		address_book->list[address_book->count] = c;
		address_book->count += 1;
    }
    fclose(address_book->fp);
	}
	else
	{
		address_book->fp = fopen("addressbook.csv", "w");

		if (address_book->fp == NULL)
		{
		return e_fail;
		}
	}

	return e_success;
}

Status save_file(AddressBook *address_book) //Austin's Code
{
	
	 // Write contacts back to file.
	 //Re write the complete file currently
	 
	address_book->fp = fopen("addressbook.csv", "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}


	for (int printNum = 0; printNum < 30; printNum++)
	{

		//Print the name of the contact to the file
		if(address_book->list[printNum].name[0][0] != '?') //Check for our null status
		{
			fprintf(address_book->fp, "%s", address_book->list[printNum].name[0]);
			fprintf(address_book->fp, ",");					//Print a "," because its a CSV file
		}


	
		if(address_book->list[printNum].phone_numbers[0][0] != '?') //Prints the phone numbers
		{		
			for (int numbersLoop = 0; numbersLoop < 5; numbersLoop++)
			{
				if ( address_book->list[printNum].phone_numbers[numbersLoop][0] != '?')
				{
				fprintf(address_book->fp, "%s", address_book->list[printNum].phone_numbers[numbersLoop]);
				fprintf(address_book->fp, ",");
				}
			}
		}
		


		if(address_book->list[printNum].email_addresses[0][0] != '?') // Prints the email addresses
		{		
			for (int emailLoop = 0; emailLoop < 5; emailLoop++)
			{
				if ( address_book->list[printNum].email_addresses[emailLoop][0] != '?')
				{
				fprintf(address_book->fp, "%s", address_book->list[printNum].email_addresses[emailLoop]);
				fprintf(address_book->fp, ",");
				}
			}
		}

		if (address_book->list[printNum].name[0][0] != '?')
		{
			fprintf(address_book->fp, "%d", address_book->list[printNum].si_no); //Print si_no to the file
			fprintf(address_book->fp, ",");

			fprintf(address_book->fp, "\n");

		}


		//fprintf(address_book->fp, "\n");

	}

	fclose(address_book->fp);

	return e_success;
}
