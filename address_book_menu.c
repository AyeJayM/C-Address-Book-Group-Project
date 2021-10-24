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

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/*
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */

	return e_success;
}

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

void main_menu(void)
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
				/* Add your implementation to call add_contacts function here */
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
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
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
						menu(address_book);
						break;
		case 1:
						int flag = 1;
						while(flag) {
						printf("Enter the name of the contact to edit\n");
						scanf("%s", &name);
						for(int i = 0; i < address_book->count; i++) {
							if(strcmp(*address_book->list[i].name, name) == 0) {
								flag = 0;
								printf("Edit the name of the contact: %s\n", *address_book->list[i].name);
								scanf("%s", &newName);
								strcpy(*address_book->list[i].name, newName);
								printf("Would you like to edit the phone number: Enter y for yes or n for no\n");
								char select;
								scanf("%s", &select);
								if(select == "y") {
									printf("Edit the phone number: %s\n", *address_book->list[i].phone_numbers);
									scanf("%s", &newPhone);
									strcpy(*address_book->list[i].phone_numbers, newPhone);
								}
								printf("Would you like to edit the email address: Enter y for yes or n for no\n");
								scanf("%s", &select);
								if(select == "y") {
									printf("Edit the email address: %s\n", *address_book->list[i].email_addresses);
									scanf("%s", &newEmail);
									strcpy(*address_book->list[i].email_addresses, newEmail);
								}
							printf("Edit(s) successful");
							}
						}
						if(flag == 1) {
							printf("No match for inputed name: %s\n", name);
						}
						}
						break;
		case 2:
						int flag = 1;
						while(flag) {
						printf("Enter the phone number of the contact to edit\n");
						scanf("%s", &phone);
						for(int i = 0; i < address_book->count; i++) {
							if(strcmp(*address_book->list[i].phone_numbers, phone) == 0) {
								flag = 0;
								printf("Edit the phone number: %s\n", *address_book->list[i].phone_numbers);
								scanf("%s", &newPhone);
								strcpy(*address_book->list[i].phone_numbers, newPhone);
								printf("Would you like to edit the name of the contact: Enter y for yes or n for no\n");
								char select;
								scanf("%s", &select);
								if(select == "y") {
									printf("Edit the name of the contact: %s\n", *address_book->list[i].name);
									scanf("%s", &newName);
									strcpy(*address_book->list[i].name, newName);
								}
								printf("Would you like to edit the email address: Enter y for yes or n for no\n");
								scanf("%s", &select);
								if(select == "y") {
									printf("Edit the email address: %s\n", *address_book->list[i].email_addresses);
									scanf("%s", &newEmail);
									strcpy(*address_book->list[i].email_addresses, newEmail);
								}
							printf("Edit(s) successful");
							}
						}
						if(flag == 1) {
							printf("No match for inputed phone number: %s\n", phone);
						}
						}
						break;
		case 3:
		int flag = 1;
						while(flag) {
						printf("Enter the email address to edit\n");
						scanf("%s", &email);
						for(int i = 0; i < address_book->count; i++) {
							if(strcmp(*address_book->list[i].email_addresses, email) == 0) {
								flag = 0;
								printf("Edit the name of the email: %s\n", *address_book->list[i].email_addresses);
								scanf("%s", &newEmail);
								strcpy(*address_book->list[i].email_addresses, newEmail);
								printf("Would you like to edit the phone number: Enter y for yes or n for no\n");
								char select;
								scanf("%s", &select);
								if(select == "y") {
									printf("Edit the phone number: %s\n", *address_book->list[i].phone_numbers);
									scanf("%s", &newPhone);
									strcpy(*address_book->list[i].phone_numbers, newPhone);
								}
								printf("Would you like to edit the name: Enter y for yes or n for no\n");
								scanf("%s", &select);
								if(select == "y") {
									printf("Edit the name of the contact: %s\n", *address_book->list[i].name);
									scanf("%s", &newName);
									strcpy(*address_book->list[i].name, newName);
								}
							printf("Edit(s) successful");
							}
						}
						if(flag == 1) {
							printf("No match for inputed email address: %s\n", email);
						}
						}
						break;
	}
	printf("Going back to main menu\n");
	menu(address_book);
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
