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
extern int arrayLocation;




int get_option(int type, const char *msg)
{
	printf("\n%s\n", msg); //Print the corresponding message from the caller function


	if(type == 1) //We check for a num
	{
		int checkInt = scanf("%d", &checkInt);

		while (checkInt > 6 || checkInt < 0)
		{
			printf("Sorry, that is not a valid input. Please reference the menu options again.");
			checkInt = scanf("%d", &checkInt);
		}

		return checkInt;
	}


	if(type == 2) //We check for a char
	{
		char checkChar = getchar();

		while (checkChar != 'Y' || checkChar != 'N') //Input Validation
		{
			printf("Sorry, that is not a valid input. Enter either Y or N.");
			checkChar = getchar();
		}

		return checkChar;
	}

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




Status list_contacts(AddressBook *address_book)
{
	char listOption;
	int contONE = 0;
	int contTWO = 1;
    int contTHREE = 2;

	do
	{
		printf("\n######  Address Book  ######\n"
		       "######  List Contacts:\n");
		
		printf("\n%s\n", address_book->list[contONE].name[0]);
		printf("%s\n", address_book->list[contONE].phone_numbers[0]);
		printf("%s\n", address_book->list[contONE].email_addresses[0]);
		printf("%d\n", address_book->list[contONE].si_no);

		printf("\n%s\n", address_book->list[contTWO].name[0]);
		printf("%s\n", address_book->list[contTWO].phone_numbers[0]);
		printf("%s\n", address_book->list[contTWO].email_addresses[0]);
		printf("%d\n", address_book->list[contTWO].si_no);

		printf("\n%s\n", address_book->list[contTHREE].name[0]);
		printf("%s\n", address_book->list[contTHREE].phone_numbers[0]);
		printf("%s\n", address_book->list[contTHREE].email_addresses[0]);
		printf("%d\n", address_book->list[contTHREE].si_no);

		printf("\nPress [q] to Quit, n to display the next page, or p to display"
				" the previous page.  |  ");
		listOption = getchar();



		while(listOption != 'q' || listOption != 'n' || listOption != 'q')
		{
			printf("\nSorry, that is not a valid input. Please note input is case sensitive."
				"Please input either q, n, or p.  |  ");

			listOption = getchar();
		}


		if( (listOption = 'n') && (contONE < 27) ) //Next page
		{
			contONE += 3;
			contTWO += 3;
			contTHREE += 3;
		}
		else if ( (listOption = 'n') && (contONE == 27) ) //Do not allow past the upper limit of address book ([29])
		{
			printf("\nYou have reached the end of the contact list.\n");
		}

		///////////////////////////////////

		if( (listOption = 'q') && (contONE > 0) ) //Previous page
		{
			contONE -= 3;
			contTWO -= 3;
			contTHREE -= 3;
		}
		else if ( (listOption = 'q') && (contONE == 0) )
		{
			printf("\nYou are at the beginning of the contact list.");
		}




		
	} while (listOption != "q");
	
	// * Add code to list all the contacts availabe in address_book.csv file
	// * Should be menu based
	// * The menu provide navigation option if the entries increase the page size
	 

	return e_success;
}



/*

////////////////////////
void menu_header(const char *str) //This is called by main_menu()
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

*/

/////////////////////////

/*

void main_menu(void) // This is called by menu()
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

/*

///////////////////////////// 

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
				add_contacts(address_book);
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

*/

Status add_contacts(AddressBook *address_book) //AUSTIN'S CODE
{

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
		     "######  Add Contact Menu:\n");

	printf("\nChoosing back will save the newly added contact!\n");

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
			phoneChoice = 5; //Ensures no odd behavior when doing the write loop to the CSV file
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
			emailChoice = 5; //Ensures no odd behavior during write loop
		}

	}


	//////////////////////////////////////////////////////////


	} //Closing Bracket for While Loop


	printf("\nAll set! Saving...\n"); 		//Now we write to the CSV file

	address_book->list[arrayLocation] = newContact; //This saves the contact

	
	//Open the file in passed Address_Book
	address_book->fp = fopen("addressbook.csv", "a+");
	

	//Print the name of the contact to the file
	//fprintf(address_book->fp, "%s", address_book->list->name[0]);
	//fprintf(address_book->fp, ",");					//Print a "," because its a CSV file
	fprintf(address_book->fp, "%s", newContact.name[0]);
	fprintf(address_book->fp, ",");


	
	if (phoneChoice > 0) //Print the phone numbers to the file
	{
		
		for (int i = 0; i < phoneChoice; i++)
			{		
				//fprintf(address_book->fp, "%s", address_book->list->phone_numbers[i]);
				//fprintf(address_book->fp, ",");
				fprintf(address_book->fp, "%s", newContact.phone_numbers[i]);
				fprintf(address_book->fp, ",");
			}
	}


	if (emailChoice > 0) //Print the emails to the file
	{
		for (int j = 0; j < emailChoice; j++)
		{
			//fprintf(address_book->fp, "%s", address_book->list->email_addresses[j]);
			//fprintf(address_book->fp, ",");
			fprintf(address_book->fp, "%s", newContact.email_addresses[j]);
			fprintf(address_book->fp, ",");
		}
	}
	


	fprintf(address_book->fp, "%d", newContact.si_no); //Print si_no to the file
	fprintf(address_book->fp, ",");

	


	fprintf(address_book->fp, "%s", "\n"); //Prints a \n to the CSV file

	fclose(address_book->fp); //Close the file

	arrayLocation++; //Moves us to the next available ContactInfo in the array

 	
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
