#include <csignal>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fstream>

char newSentence[] = "I changed the sentence and you are forked!!!!";
std::ofstream file("test.txt");

void PrintWordPerLine(char a_sentence[]) {
	const char *word = strtok(a_sentence, " ");
	while (word) {
		// next lines are just to delay the program
		for (int i = 0 ; i < 10000000 ; ++i) {
			double m = sqrt(i);
		}

		std::cout << word << std::endl;
        file << word << " ";
		word = strtok(NULL, " ");
	}
}

void handleHa(int a_signum, siginfo_t *a_sinfo, void *a_context){
    PrintWordPerLine(newSentence);
	file << std::endl;
}

int main(){
    
    struct sigaction sigAct;
    sigAct.sa_sigaction = &handleHa;
    sigAct.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sigAct, NULL);
    while(true){
		char sentence[] = "hello world there is a juke in my soup";
		PrintWordPerLine(sentence);
		file << std::endl;
    }
    return 0;

}