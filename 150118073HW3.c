#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//SERKAN KOÇ 150118073

// In this program i defined a structure which has two data field a char array and length.
// We have 4 functions to do something with the given input.text file and print the results into output.text file.

typedef struct String  { // I used typedef to shorten the initialization.
char char_array[50];
int length ;
}String;

int charAt(String *s, int index); // These are function prototypes.

String *concat (String *s1,String *s2);

unsigned int strSearch(String *s1,String *s2);

int findScore(String *s1);

static int count_words = 0;    // have to declare these static and global otherwise it keeps returning zero
static int count_chars = 0;

int main(int argc, char *argv[])
{
    FILE *fp; //declaring pointer for input file
    FILE *fp2; //declaring pointer for output file
    fp2 = fopen(argv[2], "w");
    if(fp2==NULL){      // checking whether it is opened or not
        perror("Error opening output file");
        return(-1);
    }
   fp = fopen(argv[1], "r");
   if(fp == NULL) {
      perror("Error opening input file");
      return(-1);
   }
   char str[60]; // a char array to store the data from input.text line by line
   while( fgets (str, 60, fp)!=NULL ) { // getting an input line
        if(str[0]=='e' &&str[1]=='x' &&str[2]=='i' &&str[3]=='t'){ // checking the line if it is "exit or quit" if it returns true end the program.
            fprintf(fp2,"Program ends. Bye");
            exit(1);
        }
        else if(str[0]=='q' &&str[1]=='u' &&str[2]=='i' &&str[3]=='t'){
            fprintf(fp2,"Program ends. Bye");
            exit(1);
        }

        if(str[0]=='s' &&str[1]=='t' &&str[2]=='a' &&str[3]=='t'){ // checking the line stat and printing the results.
            fprintf(fp2,"The number of words: %d\n",count_words);
            fprintf(fp2,"The number of alphabetic letters: %d\n",count_chars);
        }
      int i; // i tried to simplify this but couldnt figure it out so its a bit messy from now on.
            // in order to use functions i had to find the function number from input.txt
            // so i checked the number after the char ':' and parsed the line in the correct position.
      for(i=0;str[i] != '\0';i++){
        if(str[i]==':'){ //here finding the function number.
            if(str[i+1]=='1'){ // implementations for function 1
                int func_num, index;
                String given_string;
                sscanf(str,"%[a-zA-Z !]:%d,%d",given_string.char_array,&func_num,&index); // parsing the line in the correct way
                fprintf(fp2,"%c\n",toupper(charAt(&given_string,index))); // calling function 1
                int y ;
                for(y = 0; y<=strlen(given_string.char_array);y++){ // i didnt know how else could i find the words and total number of chars but this is my way.
                    if(given_string.char_array[y] == ' '){ // every space means a word
                        count_words++;
                    }
                    else if((given_string.char_array[y]>='a' && given_string.char_array[y]<='z') || (given_string.char_array[y]>='A' && given_string.char_array[y]<='Z')){ // ever char between the given conditions is letter.
                        count_chars++;
                    }
                }
                count_words++; // i had to add plus one because after the last word in the string there is no space so it doesnt count by the for loop
                                // other else if statements are similar to this one .
            }
            else if(str[i+1]=='2'){
                int func_num;
                String given_string,given_parameter;
                char space[] = " ";
                sscanf(str,"%[a-zA-Z !]:%d,%[a-zA-Z !]",given_string.char_array,&func_num,given_parameter.char_array);
                int y ;
                for(y = 0; y<=strlen(given_string.char_array);y++){
                    if(given_string.char_array[y] == ' '){
                        count_words++;
                    }
                    else if((given_string.char_array[y]>='a' && given_string.char_array[y]<='z') || (given_string.char_array[y]>='A' && given_string.char_array[y]<='Z')){
                        count_chars++;
                    }
                }
                count_words++;
                strcat(given_string.char_array,space); // adding space to first string in order to seperate it from second string .
                String *p;
                p=concat(&given_string,&given_parameter);
                fprintf(fp2,"%s\n",*p);
                for(y = 0; y<=strlen(given_parameter.char_array);y++){
                    if(given_parameter.char_array[y] == ' '){
                        count_words++;
                    }
                    else if((given_parameter.char_array[y]>='a' && given_parameter.char_array[y]<='z') || (given_parameter.char_array[y]>='A' && given_parameter.char_array[y]<='Z')){
                        count_chars++;
                    }
                }
                count_words++;
            }
            else if(str[i+1]=='3'){
                int func_num;
                String given_string,given_parameter;
                sscanf(str,"%[a-zA-Z !]:%d,%[a-zA-Z !]",given_string.char_array,&func_num,given_parameter.char_array);
                int y ;
                for(y = 0; y<=strlen(given_string.char_array);y++){
                    if(given_string.char_array[y] == ' '){
                        count_words++;
                    }
                    else if((given_string.char_array[y]>='a' && given_string.char_array[y]<='z') || (given_string.char_array[y]>='A' && given_string.char_array[y]<='Z')){
                        count_chars++;
                    }
                }
                count_words++;
                for(y = 0; y<=strlen(given_parameter.char_array);y++){
                    if(given_parameter.char_array[y] == ' '){
                        count_words++;
                    }
                    else if((given_parameter.char_array[y]>='a' && given_parameter.char_array[y]<='z') || (given_parameter.char_array[y]>='A' && given_parameter.char_array[y]<='Z')){
                        count_chars++;
                    }
                }
                count_words++;
                fprintf(fp2,"%u\n",strSearch(&given_string,&given_parameter));
            }
            else if(str[i+1]=='4'){
               int func_num;
               String given_string;
               sscanf(str,"%[a-zA-Z !]:%d",given_string.char_array,&func_num);
               fprintf(fp2,"%d\n",findScore(&given_string));
               int y ;
               for(y = 0; y<=strlen(given_string.char_array);y++){
                    if(given_string.char_array[y] == ' '){
                        count_words++;
                    }
                    else if((given_string.char_array[y]>='a' && given_string.char_array[y]<='z') || (given_string.char_array[y]>='A' && given_string.char_array[y]<='Z')){
                        count_chars++;
                    }
                }
                count_words++;
            }
        }
      }
   }
   fclose(fp); // closing files
   fclose(fp2);
   return(0);



}

int charAt(String *s, int index){ // this function returns the character in the given index
    int i;
    for(i = 0; i<=sizeof(s->char_array);i++){
        if(i == index)
            return s->char_array[i];
    }
}


String *concat (String *s1,String *s2){
    int i,j;
    String *pResult;
    pResult = (String*) malloc(sizeof(String)); // had to declare malloc otherwise i lost the value when returning to main
    for(i = 0;s1->char_array[i] != '\0';++i)
        pResult->char_array[i] = s1->char_array[i];
    for(j = 0;s2->char_array[j] != '\0';++j)
        pResult->char_array[i+j] = s2->char_array[j];


       pResult->char_array[i+j]='\0';
    return pResult;

}


unsigned int strSearch(String *s1,String *s2){ // this was very hard to understand from given pdf hw file but figure it out this way.
                                                // i created a string array so that i can store the seperated given string and check word by word
    int i=0 ,j=0, y=0;
    String array[50];
    while(s1->char_array[j] != '\0'){
            while(s1->char_array[i] != ' '){
                array[j].char_array[y] = s1->char_array[i];
                i++;
                y++;
                if(s1->char_array[i] == ' '){
                    i++;
                    y=0;
                    break;
                }
                if(s1->char_array[i] == '\0')
                    break;
            }
        j++;
    }
    int k = 0 ,x = 0,flag = 0;
    while(array[x].char_array != NULL ){
        while(array[x].char_array[k]==s2->char_array[k]){
            k++;
            if((k+1)==strlen(s2->char_array)){
            flag =1;
            break;
            }
        }
        if(flag ==1)
            break;
    x++;
    }
       return strlen(array[x].char_array);
}


int findScore(String *s1){ // char by char finding the score
    int i,score=0,j=0;
    while(s1->char_array[j]){
        s1->char_array[j]=toupper(s1->char_array[j]);
        j++;
    }
    for(i=0;s1->char_array[i] != '\0';i++){
        if(s1->char_array[i] == 'A' || s1->char_array[i] == 'E' || s1->char_array[i] == 'I' || s1->char_array[i] == 'O' || s1->char_array[i] == 'U'
           || s1->char_array[i] == 'L' || s1->char_array[i] == 'N' || s1->char_array[i] == 'R' || s1->char_array[i] == 'S' || s1->char_array[i] == 'T')
            score += 1;
        else if(s1->char_array[i] == 'D' || s1->char_array[i] == 'G')
            score += 2;
        else if(s1->char_array[i] == 'B' || s1->char_array[i] == 'C' || s1->char_array[i] == 'M' || s1->char_array[i] == 'P')
            score += 3;
        else if(s1->char_array[i] == 'F' || s1->char_array[i] == 'H' || s1->char_array[i] == 'W' || s1->char_array[i] == 'V' || s1->char_array[i] == 'Y')
            score += 4;
        else if(s1->char_array[i] == 'K')
            score += 5;
        else if(s1->char_array[i] == 'J' || s1->char_array[i] == 'X')
            score += 8;
        else if(s1->char_array[i] == 'Q' || s1->char_array[i] == 'Z')
            score += 10;
    }
    return score;
}






