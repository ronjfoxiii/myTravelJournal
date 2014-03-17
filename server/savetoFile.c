#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


//Test saveto and readfrom file - Tom Yeager

int main() {


	saveToFile("39°57′N", "75°10′W", "Philadelphia", "username.txt"); 

	readFromFile("username.txt");

  
  exit(0);
}


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

int readFromFile(char *filename)
{
	char str[999];
	FILE * file;
	file = fopen(filename, "r");
	if (file) {
		while (fscanf(file, "%s", str)!=EOF)
			printf("%s",str);
		fclose(file);
	}

}





