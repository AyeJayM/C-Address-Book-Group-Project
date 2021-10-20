#include <stdio.h>
//#include <stdio_ext.h>  This is commented out per proffesor's instructions on Teams
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h" //Previously was "abk_fileops.h"
//#include "abk_log.h" 	Unsure what this is for, however we do not have this file and it is causing errors in the meantime.
#include "address_book_menu.h" //Previously was "abk_menus.h"
#include "address_book.h" //Previously was "abk.k"





int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

/*Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}
*/



Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}




/* FOR DEBUG ////////////////////////
void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}
*/////////////////////////




/*void main_menu(void) /////////////// DEBUG
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}
*/



///////////////////////////// DEBUG
/*
Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				// Add your implementation to call add_contacts function here
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				// Add your implementation to call list_contacts function here
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}
*/ ////////////////


Status add_contacts(AddressBook *address_book) //AUSTIN'S CODE
{
	
	/* Add the functionality for adding contacts here */
	printf("\nWelcome to the add contact process. Please follow along with the instuctions and"
			" provide a name, phone numbers, and email address for the contact.\n");

	printf("\nPlease provide the name of the contact.\n");
	char inputName[32];

	//fgets(&address_book->list->name[0], 32, stdin);
	//scanf("%s", *address_book->list->name[0]);
	fgets(inputName, 32, stdin);

	strcpy(address_book->list->name, inputName);




	printf("\nHow many phone numbers do you have for this contact. Max allowed is 5.\n");
	int numOfPhones;						//Holds number of phone numbers for loop
	scanf("%d", &numOfPhones);

	while (numOfPhones < 0 || numOfPhones > 5)
	{
		printf("\nSorry, that is not a valid input. Please enter a value from 0 to 5.\n");
		fscanf(stdin, "%d", &numOfPhones);
	}


	if (numOfPhones > 0)
	{
		for (int i = 0; 0 < numOfPhones; i++)
		{
			printf("\nPlease provide phone number: %d out of %d for the contact.", ( i + 1 ), numOfPhones);
			fscanf(stdin, "%d", address_book->list->phone_numbers[i]); //Accepts inputted numbers from the user
							//FIX THIS ^^^^^^^^^^^^^^^^^^^^^^^
		}
	}


	printf("\nHow many phone numbers do you have for this contact. Max allowed is 5.\n");
	int numOfEmails; 					//Holds number of email addresses for loop
	scanf("%d", &numOfEmails);

	while (numOfEmails < 0 || numOfEmails > 5)
	{
		printf("\nSorry, that is not a valid input. Please enter a value from 0 to 5.\n");
		fscanf(stdin, "%d", &numOfEmails);
	}


	if (numOfEmails > 0)
	{
		for (int i = 0; 0 < numOfEmails; i++)
		{
			printf("\nPlease provide phone number: %d out of %d for the contact.", ( i + 1 ), numOfEmails);
			fscanf(stdin, "%d", address_book->list->email_addresses[i]); //Accept inputted emails from the user.
		}
	}


	printf("All set! Saving..."); 		//Now we write to the CSV file



	//Open the file in passed Address_Book
	address_book->fp = fopen("addressbook.csv", "a+");

	//Print the name of the contact to the file
	fprintf(address_book->fp, "%s", address_book->list->name[0]);
	fprintf(address_book->fp, ",");					//Print a "," because its a CSV file
	

	if (numOfPhones > 0)
	{
		for (int PhoneCntr = 0; 0 < numOfPhones; PhoneCntr++)
		{
		fprintf(address_book->fp, "%s", address_book->list->phone_numbers[PhoneCntr]);
		fprintf(address_book->fp, ",");
		}
	}


	if (numOfEmails > 0)
	{
		for (int EmailCntr = 0; 0 < numOfEmails; EmailCntr++)
		{
		fprintf(address_book->fp, "%s", address_book->list->email_addresses[EmailCntr]);
		fprintf(address_book->fp, ",");
		}
	}

 	fclose(address_book->fp); //Close the file
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
