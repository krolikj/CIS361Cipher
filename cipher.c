#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remove duplicate characters in array wordd and return the reslut string
char *removeDuplicates(char word[]);

// Search the first num characters in array charArray for character target
// return a non-zero integer if found, otherwise, return 0
int targetFound(char charArray[], int num, char target);

// Initialize the encrypt array with appropriate cipher letters according 
// to the given key
void initializeEncyptArray(char key[], char encrypt[]);

// Initialize the decrypt array with appropriate substitute letters based 
// on the encrypt array
void initializeDecyptArray(char encrypt[], char decrypt[]);

// process data from the input file and write the result to the output file 
// pass the encrypt array to parameter substitute if encryption is intended 
// pass the decrypt array to parameter substitute if decryption is intended
void processInput(FILE *inf, FILE *outf, char substitute[]);

int main(int argc, char *argv[])
{
  char encrypt[26], decrypt[26];
  int option;
  char *key;
  FILE *inFile, *outFile;

  if(argc != 5){
    printf("Encrypt/Decrypt Keyward Infile Outfile\n");
    printf("0 = Encrypt, 1 = Decrypt\n");
    exit(1);
  }

  key = argv[2];
  inFile = fopen(argv[3], "r");
  outFile = fopen(argv[4], "w");

  option = atoi(argv[1]);
  for(int i = 0; i < strlen(argv[2]); i++){
    key[i] = argv[2][i];
  }
 
  initializeEncyptArray(key, encrypt);
  initializeDecyptArray(encrypt, decrypt);

  if(!option)
    processInput(inFile, outFile, encrypt);
  else
    processInput(inFile, outFile, decrypt);
}

char *removeDuplicates(char word[]){
  int length = strlen(word);
  for(int i = 0; i < length; i++){
    for(int j = i + 1; j < length;){
      if(word[i] == word[j]){
        for(int k = j; k < length; k++){
          word[k] = word[k+1];
        }
        length--;
      }
      j++;
    }
  }
  return word;  
}

int targetFound(char charArray[], int num, char target){
  for(int i = 0; i < num; i++){
    if(charArray[i] == target)
      return 1;
  }
  return 0;
}

void initializeEncyptArray(char key[], char encrypt[]){
  char c = 'Z';
  int i = 0;
  removeDuplicates(key);
  for(i = 0; i < strlen(key); i++)
    encrypt[i] = key[i];

  for(int j = i; j < 26; j++){
    while(targetFound(encrypt, j, c)){
      c--;
    }
    encrypt[j] = c;
  }
  encrypt[26] = '\0';
}

void initializeDecyptArray(char encypt[], char decrypt[]){

  for(int i = 0; i < 26; i++){
    decrypt[encypt[i]-65] = i + 65;
  }
  decrypt[26] = '\0';
}

void processInput(FILE *inf, FILE *outf, char substitute[]){

  char ch;

  if(inf == NULL || outf == NULL){
    printf("File could not be opened\n");
    exit(1);
  }
 
  while(!feof(inf)){
    fscanf(inf, "%c", &ch);
    if(isalpha(ch)){
      if(islower(ch)){
        ch = ch - 32;
        fprintf(outf, "%c", substitute[ch-65]+32);
      }
       else
        fprintf(outf, "%c", substitute[ch-65]);
    }
    else
      fprintf(outf, "%c", ch);
  }
}
