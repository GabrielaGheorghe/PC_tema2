#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util/task_helper.h"
#define MAX 5000
#define SEPARATORS " ,.:;?!\n\0"


char *replacing(char *poem, char *word, char *friendly_word) 

{ 
    char *result; //variabila in care va fi stocata poezia cu diminutive
    result = (char*)malloc(5000*sizeof(char));
    int i = 0;
    int length_friendly = strlen(friendly_word); // lungimea diminutivului
    int length_word = strlen(word); // lungimea cuvantului
   	
   	if( result != NULL){

     while (*poem){ 

        if (strstr(poem, word) == poem) // la gasirea cuvanului in variabila poem
        { 
        	if(strstr(strstr(poem, word), friendly_word) != NULL){ // se verifica daca a fost deja inlocuit cu diminutivul
        		strcpy(&result[i], friendly_word); // cuvantul mai este inlocuit o data cu diminutivul sau
        		poem = poem + length_friendly; // poem va puncta dupa cuvantul ce avea deja diminutiv
        		i = i + length_friendly; // i va reprezenta pozitia imediat urmatoare de dupa cuvantul schimbat in diminutivul sau

        	}
        	else{ // cazul in care cuvantul nu a mai fost inlocuit cu diminutivul sau

            	strcpy(&result[i], friendly_word); // se inlocuieste cuvantul cu diminutivul
            	i = i + length_friendly; //i va reprezenta pozitia imediat urmatoare diminutivului
            	poem = poem + length_word; /* se cauta urmatorul cuvant in poem incepand cu pozitia
            	                              imediat urmatoare cuvantului ce a fost schimbat */
        	}
        } 
        else
            result[i++] = *poem++; // se parcurge poezia pana la gasirea unui cuvant ce accepta diminutiv
     } 
    }
	
    result[i] = '\0'; // poemului nou format i se adauga delimitatorul de sir 
    return result; 
}  

void uppercase(char *poem) /* transformarea primei litere a fiecarui vers in majuscula,
							celelalte fiind convertite in minuscule */
{
	int i = 0;

		for (i=0; i < strlen(poem); i++){ // transformarea tuturor literelor din poezie in minuscule

			if( (*(poem+i) > 64) && (*(poem+i) < 91)){ // verificarea daca litera este majuscula
			 poem[i] = poem[i] + 32 ; // convertirea in  minuscula
			}

		}

		for (i=0; i < strlen(poem); i++ ){ /* transformarea primelor litere din fiecare vers inafara de primul
											 in majuscula */
			
			if ((poem[i] == '\n') && (poem[i+1] >= 97) && (poem[i+1] <= 122)){ /* la intalnirea caracterului '\n'(sfarsit de linie)
																				se verifica daca urmatoarea litera este minuscula */
				 poem[i + 1] =poem[i + 1]- 32; // convertirea in mauscula
				
			}
	}

	*poem = *poem - 32;

	return;
}


void trimming(char *poem) // eliminarea spatiilor in plus si a delimitatorilor 

{
	//eliminare spatii
	int n;
	n = strlen(poem);
	int count = 0;
	int i = 0;
	int j = 0;

	for (int i = 0; i < n; i++) {

		if (poem[i] != ' ') { // verifica ce caractere sunt diferite de spatiu
			poem[count] = poem[i]; /* caracterele diferite de spatiu se stocheza in poem, 
									cu indentarea incepanad de la zero */
			count++;
		}

		if (poem[i] == ' ') {  /* verifica ce caractere sunt egale cu spatiu
								si sunt urmate de cel putin inca un spatiu */
			j = i+ 1;
			while (poem[j] == ' ') {
				j++;
		    }

	i = j;	//sare peste spatiile in plus
	poem[count] = poem[i - 1];
	count++;	
	poem[count] = poem[i]; /* pune primul caracter de dupa numarul de spatii 
							pe imediata pozitie de dupa spatiu */
	count++;
		}
		
	}
	poem[count] = '\0'; /* dupa construirea poemului fara spatii in plus, 
							se pune delimitatorul de siruri pentru a sterge dublurile
							caracterelor de la finalul sirului */
	

	//eliminare delimitatori

	int a,b;
	for(a = 0, b = 0; a <= n ; a++){

		if ((poem[a] != ',') && (poem[a] != '.') && (poem[a] != ':') && (poem[a] != ';') && (poem[a] != '?') && (poem[a] != '!')){
	
			poem[b] = poem[a]; /* se parcurge poemul caracter cu caracter, iar in cazul in care un caracter este diferit de 
								delimitatori, acesta se va stoca in noul vector creat format numai din litere */
			b++;
		}
	}

return;
}

void make_it_silly(char *sir, float nr) /* transforma fiecare litera din poezie din majuscula/minusula
											in complementarea ei pe baza unei probabilitati */
{
	float sample;
	for(int i=0; i < strlen(sir); i++){
		
		if((sir[i] >= 65) && (sir[i] <= 90)){ //verificare daca litera este majuscula
		 sample = rand() % 100 / 99.0; //generarea numarului random in intervalui [0;1]
			if (sample < nr) /* verificare daca nr. introdus de la tastatura(convertit in float) 
									este mai mic decat numarul generat random */ 
			 sir[i] = sir[i] + 32; //transformarea literei in minuscula
			}
		else

		if ((sir[i] >= 97) && (sir[i] <= 122)){ //cazul 2, in care se verifica daca litera este minuscula
		 sample = rand() % 100 / 99.0;  //generarea numarului random in intervalui [0;1]
			if (sample < nr) /* verificare daca nr. introdus de la tastatura(convertit in float) 
									este mai mic decat numarul generat random */ 
			 sir[i] = sir[i] - 32; //transformarea literei in majuscula
			}
		
}

return;
}

void rhimy()
{
	return;
}

char * friendly(char *poem) {

	char *friendly[10];
	char *words[MAX];
	char *token;
	char *result;
	char *copy = strdup(poem); // copie a poeziei
	int count = 1;
	token = strtok(copy, SEPARATORS); // separarea poeziei in cuvinte
	words[0] = token; 
	while(token != NULL) {
		token = strtok(NULL, SEPARATORS);
		words[count] = token; //stocarea cuvintelor poeziei in vectorul de pointeri *words[MAX]
		count++;
	}
	count--;
	for (int i = 0; i < count; ++i) {
		get_friendly_word(words[i], friendly); // se verifica ce cuvinte au diminutiv
			if( *friendly != NULL) {
			 poem = replacing(poem, words[i], *friendly); //se face replace in poezie cu acel diminutiv
			}
	}
	
	free(copy);
	
return poem;
}

void print(char *str) /* functia pentru afisarea poeziei 
						dupa apelul anumitor comenzi pentru prelucrarea ei */
{
	printf("%s\n\n", str);
	return;
}


int main(void)
{	
	srand(42);
	int len;
	char *poem;
	poem = (char*)malloc(5000*sizeof(char)); /*alocarea dinamica pentru variabila 
											in care este stocata poezia*/
	char *path;
	path = (char*)malloc(1000*sizeof(char)); /*alocare dinamica pentru variabila 
											in care este stocata calea catre poezie*/

	
	while(1){

	char command[MAX];
	fgets(command,MAX,stdin); //citirea comenzilor introduse de la tastatura
	
	len = strlen(command);
	if ( command[len - 1] == '\n') {  //eliminare '\n' de la sfarsitul comenzii date 
		command[len - 1] = '\0';
		len --;
	}

	/* comanda introdusa de la tastatura va fi comparata pe rand cu
	   diverse cuvinte cheie folosind 'strcmp' si se va intra pe cazul corespunzator */
	
	if (strcmp(command, "uppercase") == 0) { //cazul pentru 'uppercase'

		uppercase(poem);
			
	}
	else if (strcmp(command, "trimming") == 0) { //cazul pentru 'trimming'

		trimming(poem);	
	}
	else if ((command[0] == 'm') && (command[8] == 's')) { //cazul pentru 'make it silly'

		char *prob;
		prob = (char*)malloc(20*sizeof(char)) ; /* alocarea dinamica pentru variabila
														in care este stocata probabilitatea */
		strcpy(prob, command + 14); //stocarea cifrei de probabilitate in variabila prob
		float val_float;
		val_float = atof(prob); //convertirea probabilitatii intr-o variabila de tip float
		make_it_silly(poem, val_float);
		free(prob);

	}
	else if (strcmp(command, "make_it_friendlier") == 0) { //cazul pentru 'make it friendlier'
			
		poem = friendly(poem);
		
	}

	else if ((command[0] == 'm') && (command[8] == 'r')) { //cazul pentru 'make it rhyme'
	
	}
	else if (strcmp(command, "print") == 0) { //cazul pentru afisarea poeziei dupa executarea unei comenzi

		print(poem);		
	}
	else if (strcmp(command, "quit") == 0) { //cazul pentru parasirea buclei de comenzi

		free(poem); 
							/* eliberarea memoriei necesara stocarii 
								variabilelor poem si path */
		free(path);
		break;
	} else {							//cazul pentru 'load poem'
		
		strcpy(path,command + 5);  //stocarea in variabila 'path' a caii pentru poezie
		if ((poem != NULL) && (path != NULL))
		load_file(path, poem);
			
		}

	}


	return 0;
}

// student GHEORGHE LUMINITA-GABRIELA, 312 CB