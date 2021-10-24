#include <stdio.h>
//#include <stdio_ext.h> Commented out as per professor's instructions on Teams
#include <stdlib.h>
#include <string.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

int ContactID = 0;
int arrayLocation = 0;

int main(void)
{
	AddressBook address_book;
	ContactInfo contactsArray[30];
	address_book.list = contactsArray;


	ContactInfo defaultInfo;
	strcpy(defaultInfo.name[0] , "?");
	strcpy(defaultInfo.phone_numbers[0], "?");
	strcpy(defaultInfo.email_addresses[0], "?");

	for (int init = 0; init < 30; init++) // Inititalize name field to our null status
	{
		strcpy(contactsArray[init].name[0] , defaultInfo.name[0]); // This is how we will determine if a contact is "empty"...
	}										   		 			   // If the "name" fields begins with a "?"


	for (int phoneInit = 0; phoneInit < 30; phoneInit++) //Initialize phone numbers to our null status
	{
		for (int k = 0; k < 5; k++)
		{
			strcpy(contactsArray[phoneInit].phone_numbers[k], defaultInfo.phone_numbers[0]);
		}
	}


	for (int emailInit = 0; emailInit < 30; emailInit++) // Intialize email addresses to our null status
	{
		for (int j  = 0; j < 5 ; j++)
		{
			strcpy(contactsArray[emailInit].email_addresses[j], defaultInfo.email_addresses[0]);
		}
	}
	

	Status ret;


	// Load the file from .csv file if any
	ret = load_file(&address_book);

	if (ret == e_success)
	{
		// Show all the available menu
		ret = menu(&address_book);

		if (ret == e_success)
		{
			// Save the entries 
			save_prompt(&address_book);
		}
	}



	return 0;
} // saving the array location to the first line of the .csv
