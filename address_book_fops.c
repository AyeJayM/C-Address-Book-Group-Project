#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h> This is commented out per proffesor's instructions on Teams
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	 */

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
	}
	else
	{
		/* Create a file for adding entries */
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
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

			fprintf(address_book->fp, "%s", ","); // Print a new line to the file

		}


		fprintf(address_book->fp, "\n");

	}

	fclose(address_book->fp);

	return e_success;
}
