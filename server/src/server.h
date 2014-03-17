/*
 * hw2.h
 *
 *  Created on: Feb 9, 2013
 *      Author: lou
 */

#include <string.h>
#include <math.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Computes the nth Fibonacci number
 * @see http://en.wikipedia.org/wiki/Fibonacci_number
 */
int fib(int n);

/**
 * This function opens a directory and counts the number of files
 * in it.  If the path provided is not a directory or can
 * not be opened, this function returns 0.
 */
int numFiles(char* path);

/**
 * This function computes the size of a file (in bytes)
 * using the fopen and fseek commands.
 *
 * If the file can not be opened, return 0
 */
long int getFileSize(char* file);

/**
 * This function looks up an evironment variable using the
 * getenv function.
 * @see http://www.cplusplus.com/reference/cstdlib/getenv/
 *
 * If the environment variable is not found,
 * you should return the string "None"
 */
char* getEnvValue(const char* name);

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
char* handle_request(char * req);
