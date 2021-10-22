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
	strcpy(defaultInfo.name[0] , "0");

	for (int init = 0; init < 30; init++)
	{
		strcpy(contactsArray[init].name[0] , defaultInfo.name[0]); // This is how we will determine if a contact is "empty"...
	}										   		 			   // If the "name" fields begins with a "0"

	
	printf("%s", address_book.list[4].name[0]);


	/* Status ret;

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
	*/


	add_contacts(&address_book);

	printf("%s\n", address_book.list[arrayLocation-1].name[0]);
	printf("%s\n", address_book.list[arrayLocation-1].phone_numbers[0]);
	printf("%s\n", address_book.list[arrayLocation-1].email_addresses[0]);
	printf("%d\n", address_book.list[arrayLocation-1].si_no);

	return 0;
}
