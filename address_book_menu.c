#include <stdio.h>
//#include <stdio_ext.h>  This is commented out per proffesor's instructions on Teams
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h" //Previously was "abk_fileops.h"
//#include "abk_log.h" 	Unsure what this is for, however we do not have this file and it is causing errors in the meantime.
#include "address_book_menu.h" //Previously was "abk_menus.h"
#include "address_book.h" //Previously was "abk.k"
extern int ContactID;



/*
int get_option(int type, const char *msg)
{
	
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	  

	//Fill the code to add above functionality 
}
*/


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


/*
Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 

	return e_success;
}
/*



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

	ContactInfo newContact;
	int addMenuChoice;
	int nameChoice  = 0; //Determines when to display name.
	int phoneChoice = 0; //Determines which Phone Number will be next entered and displayed
	int emailChoice = 0; //Determines which Email will be next entered and displayed

	ContactID++;
	newContact.si_no = ContactID;

	while(addMenuChoice != 0)
	{
	printf("\n######  Address Book  ######\n"
		     "######  Add Contact Menu:");


	printf("\n\n0. Back\n");

	if(nameChoice == 0)
		{
			 printf("1. Name	       :\n");
		}

		   if(nameChoice > 0)
			{
			   printf("1. Name	       :  %s\n", newContact.name[0]);
			}
		

	if (phoneChoice == 0)
		{
			printf("2. Phone No 1  :\n");
		}

		   if ( phoneChoice > 0 )
		   {
			   printf("2. Phone No 1  :  %s\n", newContact.phone_numbers[0]);

			   if ( phoneChoice > 1 )
		   		{
			   		printf("   Phone No 2  :  %s\n", newContact.phone_numbers[1]);

					if ( phoneChoice > 2 )
		   			{
			   			printf("   Phone No 3  :  %s\n", newContact.phone_numbers[2]);

						if ( phoneChoice > 3 )
		   				{
			   				printf("   Phone No 4  :  %s\n", newContact.phone_numbers[3]);

							if ( phoneChoice > 4 )
							{
								printf("   Phone No 5  :  %s\n", newContact.phone_numbers[4]);
							}
		   				}

		   			}
		   		}
		   }
		
		
	if( emailChoice == 0)
		{
			printf("3. Email ID 1  :");
		}

			if ( emailChoice > 0 )
		   {
			   printf("3. Email ID 1  :  %s\n", newContact.email_addresses[0]);

			   if ( emailChoice > 1 )
		   		{
			   		printf("   Email ID 2  :  %s\n", newContact.email_addresses[1]);

					if ( emailChoice > 2 )
		   			{
			   			printf("   Email ID 3  :  %s\n", newContact.email_addresses[2]);

						if ( emailChoice > 3 )
		   				{
			   				printf("   Email ID 4  :  %s\n", newContact.email_addresses[3]);

							if ( emailChoice > 4 )
							{
								printf("   Email ID 5  :  %s\n", newContact.email_addresses[4]);
							}
		   				}

		   			}
		   		}
		   }

	
	
	printf("\n\nPlease select an option: ");
	
	scanf("%d", &addMenuChoice);	//User inputs their menu choice

	while(addMenuChoice > 3 || addMenuChoice < 0) //Validate Menu Input
	{
		printf("\nThat is not a valid menu choice. Please enter your selection again.\n");
		scanf("%d", &addMenuChoice);
	}


	//////////////////////////////////////////////////////////


	if(addMenuChoice == 1) //Add a name
	{
		nameChoice++;
		printf("Enter the contact name: ");
		scanf("%s", newContact.name[0]);
	}


	//////////////////////////////////////////////////////////


	if(addMenuChoice == 2) //Add a phone number
	{
		phoneChoice++;

		if(phoneChoice == 1)
		{
			printf("\nPlease enter Phone Number 1: ");
			scanf("%s", newContact.phone_numbers[0]);
		}

		if(phoneChoice == 2)
		{
			printf("\nPlease enter Phone Number 2: ");
			scanf("%s", newContact.phone_numbers[1]);
		}

		if(phoneChoice == 3)
		{
			printf("\nPlease enter Phone Number 3: ");
			scanf("%s", newContact.phone_numbers[2]);
		}

		if(phoneChoice == 4)
		{
			printf("\nPlease enter Phone Number 4: ");
			scanf("%s", newContact.phone_numbers[3]);
		}

		if(phoneChoice == 5)
		{
			printf("\nPlease enter Phone Number 5: ");
			scanf("%s", newContact.phone_numbers[4]);
		}

		if(phoneChoice > 5)
		{
			printf("\nSorry, you cannot add more than 5 phone numbers. "
			"Should you wish to change a number, please use the edit contact function.\n");
		}

	}


	//////////////////////////////////////////////////////////


	if (addMenuChoice == 3) //Add an Email
	{

		emailChoice++;

		if(emailChoice == 1)
		{
			printf("\nPlease enter Email 1: ");
			scanf("%s", newContact.email_addresses[0]);
		}

		if(emailChoice == 2)
		{
			printf("\nPlease enter Email 2: ");
			scanf("%s", newContact.email_addresses[1]);
		}

		if(emailChoice == 3)
		{
			printf("\nPlease enter Email 3: ");
			scanf("%s", newContact.email_addresses[2]);
		}

		if(emailChoice == 4)
		{
			printf("\nPlease enter Email 4: ");
			scanf("%s", newContact.email_addresses[3]);
		}

		if(emailChoice == 5)
		{
			printf("\nPlease enter Email 5: ");
			scanf("%s", newContact.email_addresses[4]);
		}

		if(emailChoice > 5)
		{
			printf("\nSorry, you cannot add more than 5 email addresses. "
			"Should you wish to change an email, please use the edit contact function.\n");
		}

	}


	//////////////////////////////////////////////////////////


	} //Closing Bracket for While Loop


	printf("All set! Saving..."); 		//Now we write to the CSV file


	//address_book->list = &newContact; //This saves the contact

	//printf("%s", address_book->list->name[0]); //This ensures the name was saved



	//Open the file in passed Address_Book
	address_book->fp = fopen("addressbook.csv", "a+");


	//Print the name of the contact to the file
	fprintf(address_book->fp, "%s", newContact.name[0]);
	fprintf(address_book->fp, ",");					//Print a "," because its a CSV file
	

	if (phoneChoice > 0) //Print the phone numbers to the file
	{
		for (int PhoneCntr = 0; 0 < phoneChoice; PhoneCntr++)
		{
		fprintf(address_book->fp, "%s", newContact.phone_numbers[PhoneCntr]);
		fprintf(address_book->fp, ",");
		}
	}


	if (emailChoice > 0) //Print the emails to the file
	{
		for (int EmailCntr = 0; 0 < emailChoice; EmailCntr++)
		{
		fprintf(address_book->fp, "%s", newContact.email_addresses[EmailCntr]);
		fprintf(address_book->fp, ",");
		}
	}


	fprintf(address_book->fp, "%d", newContact.si_no); //Print si_no to the file
	fprintf(address_book->fp, ",");



	fprintf(address_book->fp, "%s", NEXT_ENTRY); //Prints a \n to the CSV file



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
