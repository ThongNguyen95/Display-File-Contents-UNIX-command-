//Thong Nguyen - HW2
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char * argv[]) {

	if (argc != 2 && argc != 3) {
		printf("\tSynopsis: head [OPTION] [FILE]\n"
			"\t[OPTION]:-nK (print the first K lines)\n");

	} else if ((argc == 3) && ((argv[1][0] != '-') || (argv[1][1] != 'n'))) {
		printf("\tSynopsis: head [OPTION] [FILE]\n"
			"\t[OPTION]:-nK (print the first K lines)\n");

	}
	else {
		char buffer[] = " "; //create an character array of size 2, with buffer[1] = '\0';
		int fd;
		int lineCount = 0;
		int totalLines;

		if (argc == 2) {
			//open the file
			fd = open(argv[1], O_RDONLY);
			if (fd == -1) {
				printf("Failed to open the file!\n");
				return 0;
			}

			//determine number of lines to read
			totalLines = 10;
		}

		if (argc == 3) {
			//open the file
			fd = open(argv[2], O_RDONLY);
			if (fd == -1) {
				printf("Failed to open the file!\n");
				return 0;
			}

			//determine number of lines to read
			char temp[strlen(argv[1]) - 1]; //include the terminating null character
			int i;
			for (i = 2; i < strlen(argv[1]) + 1; i++) {
				temp[i - 2] = argv[1][i];		//Copy each word from argv[1] into temp
			}
			totalLines = atoi(temp); //convert into integer
		}

		while (lineCount < totalLines) {
			int bytes = read(fd, buffer, 1);
			if (bytes > 0) {
				printf("%s", buffer);
				if (strcmp(buffer, "\n") == 0) {
					lineCount++;
				}
			} else {
				lineCount = totalLines;
			}
		}

		close(fd);
	}

	return 0;
}
