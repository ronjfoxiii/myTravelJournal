#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int main() {


	saveToFile("39°57′N", "75°10′W", "Philadelphia"); 


  
  exit(0);
}


int saveToFile(char *lat, char *lon, char *title)
{
	FILE *f = fopen("log.txt", "w");
	
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	
	fprintf(f, "%s,", lat);
	fprintf(f, "%s,", lon);
	fprintf(f, "%s/n", title);
	
	fclose(f);

	return 1;
}

int readFromFile(char *filename)
{


}





