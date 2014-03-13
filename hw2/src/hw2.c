/*
 * hw2.c
 *
 *  Created on: Feb 9, 2013
 *      Author: lou
 */
#include "hw2.h"

/**
 * Computes the nth Fibonacci number
 * @see http://en.wikipedia.org/wiki/Fibonacci_number
 */
int fib(int n) {
	// TODO: compute the nth fibonacchi number
	if(n <= 1) 
	{
		return n;
	}
	
	return fib(n-1) + fib(n-2);
}

/**
 * This function opens a directory and counts the number of files
 * in it.  If the path provided is not a directory or can
 * not be opened, this function returns 0.
 */
int numFiles(char* path) {
	DIR *dp; // a pointer to a directory
	int rv = 0; // the return value
	struct dirent *ep; // a directory entry

	// TODO: open the directory using opendir, and see if it was successful
	  if (!(dp = opendir(path)))
		  return 0;

	  while (0 != (ep = readdir(dp))) {
		  rv = rv + 1;
      }

     closedir(dp);

  	  return rv;
	
		// TODO: Count the files in the directory
		// TODO: close the directy
	
	// TODO: return result
}

/**
 * This function computes the size of a file (in bytes)
 * using the fopen and fseek commands.
 *
 * If the file can not be opened, return 0
 */
long int getFileSize(char* file) {
	FILE* f; // the file to open
	long int rv = 0; // the return value


	// TODO: See if you can open the file
		f = fopen(file, "r");
		
		if(f != NULL)
		{
			fseek(f, 0, SEEK_END); 
			
			rv = ftell(f);
			
			fclose(f);
		}
		else
			return 0;
			
		
		return rv;
			
		// TODO: If successful, seek to the end of the file
		// TODO: use ftell to see how far you seeked
		// TODO: close the file
	// TODO: return result	
}

/**
 * This function looks up an evironment variable using the
 * getenv function.
 * @see http://www.cplusplus.com/reference/cstdlib/getenv/
 *
 * If the environment variable is not found,
 * you should return the string "None"
 */
char* getEnvValue(const char* name) {
	char * rv;

	// TODO: look up the environment variable
	rv = getenv(name);
	// TODO: check if it is  found
	if(rv == NULL)
		return "None";
		// TODO: if not, set the return value to "None"
	// TODO: return result
	return rv; 
}


/**
 * This function is the big one of this assignment.
 * It takes a string representing the HTTP request, parses the
 * values from the GET variables, creates an HTTP response,
 * and fills it with the results of one of the above functions.
 *
 * For example, if you go to:
 * http://localhost:8000/?f=fib&n=10
 * You should see:
 * 55
 * In your browser.
 *
 * Note the request above will have the first line be:
 * GET /?f=fib&n=10 HTTP/1.1
 * So you'll have to use a tokenizer to pull out the "10" and "f=fib"
 */
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

			// TODO: see if 'ftoken' is any of our functions
			// TODO: if ftoken is "f=fib", call fib and print results to res
			if(strncmp(ftoken, "f=fib", 5) == 0)
			{
				sprintf(rv, "%d", fib(atoi(atoken)) ) ; 
			}

			// TODO: if numFiles, call function and print result
			if(strncmp(ftoken, "f=numFiles", 10) == 0)
			{
				sprintf(rv, "%d", numFiles(atoken));
			}
				// TODO: if getFileSize, call function and print result
			if(strncmp(ftoken, "f=getFileSize", 13) == 0)
			{
				sprintf(rv, "%ld", getFileSize(atoken));
			}
				// TODO: if getEnvValue, call function and print result
			if(strncmp(ftoken, "f=getEnvValue", 13) == 0)
			{
				sprintf(rv, "%s", getEnvValue(atoken));
			}
		}

		return rv;
	// TODO: return result
}
