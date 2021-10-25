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

	printf("%s", msg); //Print the corresponding message from the caller function


	if(type == 1) //We check for a num
	{

		int checkInt;
		scanf(" %d", &checkInt);
		fflush(stdin);

		/*while ( (checkInt > 6) || (checkInt < 0 ) )
		{
			printf("Sorry, that is not a valid input. Please reference the menu options again.");
			scanf("%d", &checkInt);

		}*/

		return checkInt;
	}


	if(type == 2) //We check for a char
	{
		char checkChar;
		checkChar = getchar();

		/*while ( (checkChar != 'Y') || (checkChar != 'N') ) //Input Validation
		{
			printf("Sorry, that is not a valid input. Enter either Y or N.");
			checkChar = getchar();
		}
		*/

		return checkChar;
	}
	return 0;
}





////////////////////////////////////////////////





Status save_prompt(AddressBook *address_book)
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





///////////////////////////////////////////////





Status list_contacts(AddressBook *address_book)
{
	char listOption;
	int contONE = 0;
	int contTWO = 1;
    int contTHREE = 2;

	do
	{
		int c;
		while ((c = getchar()) != '\n' && c != EOF) { }


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

		printf("\nPress [q] to Quit, [n] to display the next page, or [p] to display"
				" the previous page.  |  ");
		listOption = getc(stdin);


		/*while(listOption != 'q' || listOption != 'n' || listOption != 'q')
		{
			printf("\nSorry, that is not a valid input. Please note input is case sensitive."
				"Please input either q, n, or p.  |  ");

			int d;
			while ((d = getchar()) != '\n' && d != EOF) { }

			listOption = getc(stdin);
		}
		*/

		if( (listOption == 'n') && (contONE < 27) ) //Next page
		{
			contONE += 3;
			contTWO += 3;
			contTHREE += 3;
		}
		else if ( (listOption == 'n') && (contONE == 27) ) //Do not allow past the upper limit of address book ([29])
		{
			printf("\nYou have reached the end of the contact list.\n");
		}

		///////////////////////////////////

		if( (listOption == 'q') && (contONE > 0) ) //Previous page
		{
			contONE -= 3;
			contTWO -= 3;
			contTHREE -= 3;
		}
		else if ( (listOption == 'q') && (contONE == 0) )
		{
			printf("\nYou are at the beginning of the contact list.");
		}


	} while (listOption != 'q');


	return e_success;
}





////////////////////////





void menu_header(const char *str) //This is called by main_menu()
{
	fflush(stdout);

	system("cls");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}




/////////////////////////




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
				search_contact(address_book, e_search);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				list_contacts(address_book);
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}




///////////////////////////////




Status add_contacts(AddressBook *address_book) //AUSTIN'S CODE
{


	ContactInfo newContact;
	menu_header("Add");
	int addMenuChoice = 1;
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

	scanf(" %d",&addMenuChoice);

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


	printf("\nAll set! Allocating new contact to Contact Array...\n"); 		//Now we write to the CSV file

	address_book->list[arrayLocation] = newContact; //This saves the contact

	arrayLocation++; //Moves us to the next available ContactInfo in the array

return e_success;
}




//////////////////////////////



/*
Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	//Redundant. Anything that can be done here could be called in search_contact()
}
*/




Status search_contact(AddressBook *address_book, Modes mode) // Isabella's Code
{
	char str[255];
	const char *type;
	switch (mode)
	{
	case e_delete:
		type = "to Delete by";
		break;
	case e_edit:
		type = "to Edit by";
		break;
	default:
		type = "to Search by";
		break;
	}
	printf("######## Search Contact %s: \n\n", type);
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n");

	int contactNo;
	scanf("%d", &contactNo);


	address_book->fp = fopen("address_book", "r");

	if(address_book->fp == NULL){
		printf("File is empty or does not exist.\n");
		return e_no_match;
	}

	switch(contactNo){

		case 0:
		{
			printf("Selected: Back........\nReturning to main menu....\n");
			return e_back;
		}
		case 1:
		{
			//Search for name
			printf("Enter the Name:\n");
			scanf("%s", str);
			char temp[255];

			//size of entire addr book
			for(int i =0; i< sizeof address_book->fp +1; i++){
				//per contact
				for(int ii = 0; ii < sizeof(address_book->list->name)/sizeof(address_book->list->name[ii]); ii++){
					fscanf(address_book->fp, "%s", temp);
					if(strcmp(str, temp)== 0){
						//print out contact

						printf("%d  :  ", i);
						printf("%p  :  ", address_book->list->name[i]);
						printf("%p  :  ", address_book->list->phone_numbers[i]);
						printf("%p\n", address_book->list->email_addresses[i]);
						return e_success;

					}
				}
			}
			//if we come out of this it means it wasn't found
			break;
		}
		case 2:
		{
			//phone no.
			printf("Please enter the PHONE NUMBER of the contact you want to search for:\n");
			scanf("%s", str);
			char temp[255];

			for(int i =0; i< sizeof address_book->fp +1; i++){
				//per contact
				for(int ii = 0; ii < sizeof(address_book->list->phone_numbers)/sizeof(address_book->list->phone_numbers[ii]); ii++){
					fscanf(address_book->fp, "%s", temp);
					if(strcmp(str, temp)== 0){
						//print out contact
						//need fancy format? printf("SI No.\tName\t\t");
						printf("%d  :  ", i);
						printf("%p  :  ", address_book->list->name[i]);
						printf("%p  :  ", address_book->list->phone_numbers[i]);
						printf("%p\n", address_book->list->email_addresses[i]);
						return e_success;

					}
				}
			}
			break;
		}
		case 3:
		{
			//email
			printf("Please enter the EMAIL of the contact you want to search for:\n");
			scanf("%s", str);
			char temp[255];
			for(int i =0; i< sizeof address_book->fp +1; i++){
				//per contact
				for(int ii = 0; ii < sizeof(address_book->list->email_addresses)/sizeof(address_book->list->email_addresses[ii]); ii++){
					fscanf(address_book->fp, "%s", temp);
					if(strcmp(str, temp)== 0){
						//print out contact
						printf("%d  :  ", i);
						printf("%p  :  ", address_book->list->name[i]);
						printf("%p  :  ", address_book->list->phone_numbers[i]);
						printf("%p\n", address_book->list->email_addresses[i]);
						return e_success;

					}
				}
			}
			break;
		}
		case 4:
		{
			//serial no.
			printf("Please enter the SERIAL NUMBER of the contact you want to search for:\n");
			int sino;
			scanf("%d", &sino);

			//char temp[255];
			int num;
			for(int i =0; i< sizeof address_book->fp +1; i++){
				//per contact
																									//error at si_no[ii] expression must have pointer-to-object type but it has type "int"
				for(int ii = 0; ii < sizeof(address_book->list->si_no)/sizeof(address_book->list->si_no); ii++){
					fscanf(address_book->fp, "%d", &num);
					if(sino == num){
						//print out contact
						printf("%d  :  ", i);
						printf("%p  :  ", address_book->list->name[i]);
						printf("%p  :  ", address_book->list->phone_numbers[i]);
						printf("%p\n", address_book->list->email_addresses[i]);
						return e_success;

					}
				}
			}
			break;
		}
		default:

			if(contactNo < 0 || contactNo > 4){
				printf("This is an invalid number.\n");
				break;
			}


	}
	printf("Contact Was Not Found\n.");
	return e_fail;

}




/////////////////////////////////////////





Status edit_contact(AddressBook *address_book) //Richard's Code
{

	/* Add the functionality for edit contacts here */
	int num;
	char name[32];
	char phone[32];
	char email[32];
	char newName[32];
	char newPhone[32];
	char newEmail[32];
	menu_header("Edit Contact:\n");
	printf("Please select an option to edit your contacts by or return to the menu:\n");
	printf("0. Menu\n");
	printf("1. Name\n");
	printf("2. Phone Number\n");
	printf("3. Email Address\n");
  scanf("%d", &num);

	switch(num) {
		case 0:
		{
						menu(address_book);
						break;
		}
		case 1:
		{
						int flag = 1;
						while(flag) {
						printf("Enter the name of the contact to edit\n");
						//removed &name and replaced it with name
						scanf("%s", name);
						for(int i = 0; i< sizeof address_book->fp +1; i++) {
							if(strcmp(*address_book->list[i].name, name) == 0) {
								flag = 0;
								printf("Edit the name of the contact: %s\n", *address_book->list[i].name);
								//removed &
								scanf("%s", newName);
								strcpy(*address_book->list[i].name, newName);
								printf("Would you like to edit the phone number: Enter y for yes or n for no\n");
								char select;
								//replaced %s with %c
								scanf("%s", &select);
								if(select == 'y') {
									printf("Edit the phone number: %s\n", *address_book->list[i].phone_numbers);
									//removed &
									scanf("%s", newPhone);
									strcpy(*address_book->list[i].phone_numbers, newPhone);
								}
								printf("Would you like to edit the email address: Enter y for yes or n for no\n");
								//removed &
								scanf("%s", &select);
								if(select == 'y') {
									printf("Edit the email address: %s\n", *address_book->list[i].email_addresses);
									//removed &
									scanf("%s", newEmail);
									strcpy(*address_book->list[i].email_addresses, newEmail);
								}
							printf("Edit(s) successful\n");
							}
						}
						if(flag == 1) {
							printf("No match for inputed name: %s\n", name);
							printf("Would you like to quit? press q to quit or n for no\n");
							char select;
							scanf("%s", &select);
							if(select == 'q') {
								flag = 0;
							}
						}
						}
						break;
		}
		case 2:
		{
						int flag = 1;
						while(flag) {
						printf("Enter the phone number of the contact to edit\n");
						//removed &
						scanf("%s", phone);
						for(int i = 0; i< sizeof address_book->fp +1; i++) {
							if(strcmp(*address_book->list[i].phone_numbers, phone) == 0) {
								flag = 0;
								printf("Edit the phone number: %s\n", *address_book->list[i].phone_numbers);
								//removed &
								scanf("%s", newPhone);
								strcpy(*address_book->list[i].phone_numbers, newPhone);
								printf("Would you like to edit the name of the contact: Enter y for yes or n for no\n");
								char select;

								scanf("%s", &select);
								if(select == 'y') {
									printf("Edit the name of the contact: %s\n", *address_book->list[i].name);
									//removed &
									scanf("%s", newName);
									strcpy(*address_book->list[i].name, newName);
								}
								printf("Would you like to edit the email address: Enter y for yes or n for no\n");

								scanf("%s", &select);
								if(select == 'y') {
									printf("Edit the email address: %s\n", *address_book->list[i].email_addresses);
									//removed &
									scanf("%s", newEmail);
									strcpy(*address_book->list[i].email_addresses, newEmail);
								}
							printf("Edit(s) successful");
							}
						}
						if(flag == 1) {
							printf("No match for inputed phone number: %s\n", phone);
							printf("Would you like to quit? press q to quit or n for no\n");
							char select;
							scanf("%s", &select);
							if(select == 'q') {
								flag = 0;
							}
						}
						}
						break;
		}
		case 3:
		{
		int flag = 1;
						while(flag) {
						printf("Enter the email address to edit\n");
						//removed &
						scanf("%s", email);
						for(int i = 0; i< sizeof address_book->fp +1; i++) {
							if(strcmp(*address_book->list[i].email_addresses, email) == 0) {
								flag = 0;
								printf("Edit the email: %s\n", *address_book->list[i].email_addresses);
								//removed &
								scanf("%s", newEmail);
								strcpy(*address_book->list[i].email_addresses, newEmail);
								printf("Would you like to edit the phone number: Enter y for yes or n for no\n");
								char select;

								scanf("%s", &select);
								if(select == 'y') {
									printf("Edit the phone number: %s\n", *address_book->list[i].phone_numbers);
									//removed &
									scanf("%s", newPhone);
									strcpy(*address_book->list[i].phone_numbers, newPhone);
								}
								printf("Would you like to edit the name: Enter y for yes or n for no\n");

								scanf("%s", &select);
								if(select == 'y') {
									printf("Edit the name of the contact: %s\n", *address_book->list[i].name);
									//removed &
									scanf("%s", newName);
									strcpy(*address_book->list[i].name, newName);
								}
							printf("Edit(s) successful");
							}
						}
						if(flag == 1) {
							printf("No match for inputed email address: %s\n", email);
							printf("Would you like to quit? press q to quit or n for no\n");
							char select;
							scanf("%s", &select);
							if(select == 'q') {
								flag = 0;
							}
						}
						}
						break;
		}
	}
	printf("Going back to main menu\n");
	menu(address_book);
	return e_success;
}




////////////////////////////////




Status delete_contact(AddressBook *address_book)
{
	menu_header("Search Contact to Delete by:"); //printing header
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email Id\n");
	printf("4. Serial No\n\n");
	printf("Please select an option: ");
	int option = get_option(NUM, "");
	switch(option) {
		case 0:
		return e_back;
		break;
		case 1:
		break;
		case 2:
		break;
		case 3:
		break;
		case 4:
		break;
	}
	/* Add the functionality for delete contacts here */
	return e_success;
}