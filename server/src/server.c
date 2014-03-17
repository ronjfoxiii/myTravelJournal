/*
 * hw2.c
 *
 *  Created on: march 9, 2014
 *      Author: Tom
 */
#include "server.h"


/**
*Tom Yeager
 *This function gets user name and reads file that was saved as this username
 *use Jannson library to send JSON response back to the client/google API
 */
char* getUsername(const char* name) {
	char * rv;
	
	rv = readFromFile(name);
	
	
	//use Jannson library to send JSON response back to the client/google API

	return rv; 
}

/**
*Tom Yeager
 *This function saves lat, lon, title, to a file that will be named the current users name
 *
 */

int saveToFile(char *lat, char *lon, char *title, char *filename)
{
	FILE *f = fopen(filename, "a");
	
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	
	fprintf(f, "%s,", lat);
	fprintf(f, "%s,", lon);
	fprintf(f, "%s\n", title);
	
	fclose(f);

	return 1;
}

/**
 *This function reads cords from file that is saved based on a username.  
 *It will then send a JSON formatted response back to the google maps api and place the saved markers on the map.
 */
char* readFromFile(char *filename)
{
	char str[999];
	FILE * file;
	file = fopen(filename, "r");
	if (file) {
		while (fscanf(file, "%s", str)!=EOF)
			str = str + " " + str;
		fclose(file);
	}
	
	return str;

}


/**
 **/
 
char* handle_request(char * req) {
	char * rv; // This will be our return value
	char * res; // This will point to a location in rv where we can write the html to.
	char * ftoken; // this will be a token that we pull out of the 'path' variable indicating the function
	               // for example, if you go to http://localhost:8000/?f=fib&n=10, this will be "f=fib"
	char * atoken; // A token representing the argument to the function, i.e., "n=10"
	char * tmp; // used to point to where the arguments start

	// TODO: allocate a big chunk of memory for the result. Like 2048 characters
	 rv = (char*) malloc(2048 * sizeof(char)); 
	
	// TODO: write the first line of the HTML header to rv.
	// see http://www.opencalais.com/HTTPexamples for some examples
	// you only need to write the first few lines here.
	 sprintf(rv, "%s", "HTTP/1.1 200 OK\n\n");

	// FREEBEE: set the 'res' pointer to be in the location after the header
	res = &(rv[strlen("HTTP/1.1 200 OK\n\n")]);

	// TODO: check if the request is a GET request.
	
	// Use strncmp, see http://www.cplusplus.com/reference/cstring/strncmp/
	   if (strncmp(req, "GET", 3) == 0) 
	   {
			// FREEBEE: set the tmp pointer to where the "path" variable begins
			tmp = req+4;
			// TODO: increment tmp point if it points to a '/'
			
			if(*tmp == '/')
			{
				tmp = tmp + 1;
			}
			// TODO: increment tmp point if it points to a '?'
			if(*tmp == '?')
			{
				tmp = tmp + 1;
			}

			// TODO: Set the 'ftoken' variable to the first argument of the path variable.
			ftoken = strtok((char *)tmp, "&"); 
			
			// Use the strtok function to do this
			// For an example, see http://www.cplusplus.com/reference/cstring/strtok/

			// TODO: set atoken to the n= argument
			atoken = strtok(NULL, " ");
			
			// TODO: advance the atoken to remove the "n="
			atoken = atoken + 2; 


			// TODO: if getEnvValue, call function and print result
			if(strncmp(ftoken, "f=getUsername", 13) == 0)
			{
				getUsername(atoken);
			}
		}

		return rv;
	// TODO: return result
}

