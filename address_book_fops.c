#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret = access( DEFAULT_FILE, F_OK);

	if (ret == 0)
	{
		address_book->fp = fopen(DEFAULT_FILE, "r");
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
		address_book->fp = fopen(DEFAULT_FILE, "w");

		if (address_book->fp == NULL)
		{
		return e_fail;
		}
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
