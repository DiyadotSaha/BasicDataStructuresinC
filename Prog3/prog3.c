// Implement the text process application
// The output function is provided to you.
#include "Dictionary.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

//This is used internally by the output function. You don't need to change this value
#define WORD_BUFFER_SIZE 50



/**
 * @brief Checks if a character is in the char array.
 * 
 * @param ch The character to check
 * @param charArr The ckaracter array to compare against
 * @return true ch is in charArr
 * @return false ch is not in charArr
 */
bool any_char(char ch, char *charArr) {
    while (*charArr != 0) {
        if (ch == *charArr++) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Gets the distance to the closest delimeter.
 * 
 * @param word The string to look through
 * @param delim The delimeter(s) to search for
 * @return uint8_t The number of characters in the word 
 */
uint8_t word_length(char *str, char *delims) {
    int i = 0;
    while (!any_char(str[i], delims) && str[i] != 0) {
        i++;
    }
    return i;
}

void *dataPrinter(void *data){
    KVPair *object = data; 
    printf("%s:%d\n", object->key, object -> value);  
}

void *freeData(KVPair *kvPair){
    free(kvPair); 
}

int *ListdataCompare(void *obj1, void *obj2){ 
    KVPair *object1 = (KVPair*)obj1; 
    KVPair *object2 = (KVPair*)obj2; 
    if((object1-> value == object2-> value)){           
        return strcmp(object1 -> key, object2 -> key)*-1;  //if the values are the same then return the strcmp value for the two words
    }
    else if (object1 -> value <  object2 -> value){
        return -1;                                      // if the obj1 is lesser then return < 0
    }
    else if (object1 -> value >  object2 -> value)
    {
        return 1;                                       // if the obj1 is greater return >0
    }    
}


/**
 * @brief Prints the output to stdout. Accepts one line of output at a time.
 * 
 * @param wordFreqs A dictionary of words to format according to their frequency
 * @param wordLengths A dictionary of words to format according to their length
 * @param text One output line to format
 */
void printOutput(Dictionary *wordFreqs, Dictionary *wordLengths, char *text) {
    char wordBuffer[WORD_BUFFER_SIZE] = {0};
    while (*text != 0) {
        uint8_t length = word_length(text, " \n");
        assert(length < WORD_BUFFER_SIZE - 1);
        memcpy(wordBuffer, text, length);
        text = text + length;
        wordBuffer[length] = 0;
        KVPair *freq = dictionary_find(wordFreqs, wordBuffer);
        KVPair *len = dictionary_find(wordLengths, wordBuffer);
        if (freq == NULL && len == NULL) {
            printf("%s ", wordBuffer);
        } else {
            printf("<span style=\"");
            if (freq != NULL) {
                uint8_t r = (intptr_t)freq->value * 23;
                uint8_t g = (intptr_t)freq->value * 29;
                uint8_t b = (intptr_t)freq->value * 31;
                printf("color:#%02x%02x%02x;font-weight:bold;", r, g, b);
            }
            if (len != NULL) {
                printf("font-size:%ldpx;", 2 * (intptr_t)len->value);
            }
            printf("\">%s</span> ", wordBuffer);
        }

        if (*text != 0) { // If delimiter is not null byte, then skip over it. 
            text += 1;
        }
    }
    printf("<br/>\n");
}

int main(void) {
    // TODO: Read in stopwords from stdin. Treat spaces as word delimiters.
    
    // creating the 2 dictionaries and 2 lists for frequency and length 
    // 1 list for each sentence in the file 
    // 1 list for the stop words
    Dictionary* frequencyDictionary = dictionary_create(100, dataPrinter, freeData); 
    Dictionary* lengthDictionary = dictionary_create(100, dataPrinter, freeData); 
    ListPtr frequencyList = list_create(ListdataCompare, dataPrinter, freeData);
    ListPtr lengthList = list_create(ListdataCompare, dataPrinter, freeData);
    ListPtr sentenceList = list_create(ListdataCompare, dataPrinter, freeData); 
    ListPtr stopwords = list_create(ListdataCompare, dataPrinter, freeData); 

    char *STOPWORD = "===="; 
    int stopChecker = 0; 
    char *white = " "; 
    char sentence[5000]; 
    //looping through file until all lines are read
    while(fgets(sentence, 5000, stdin) != NULL){   
        char* word = (char*)malloc((50));
        char *store_token;
        //deletes the last new line space in the sentence stackoverflow: https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
        sentence[strcspn(sentence, "\n")] = '\0';
        KVPair* sentencePair = (KVPair*) malloc(sizeof(KVPair));
        char *temp = strdup(sentence); 
        sentencePair -> key = temp;
        sentencePair -> value = 1;
        list_append(sentenceList, sentencePair); 
        //free(sentencePair); 

        store_token = strtok(sentence, white); // storing each token into a char*
        char *firsttok = strdup(store_token);  //duplicating the token recieved 
        
        //------------adding the first word/token collected -------------------
        KVPair* first_kq = (KVPair*) malloc(sizeof(KVPair));
        first_kq -> key = firsttok;
        first_kq -> value = 1;

        KVPair* first_kq2 = (KVPair*) malloc(sizeof(KVPair));
        first_kq2 -> key = firsttok;
        first_kq2 -> value = word_length(firsttok, "");
        
        KVPair* Ffirst_tok_kq = dictionary_find(frequencyDictionary, firsttok);
        if(dictionary_find(frequencyDictionary, firsttok)!= NULL){ 
            Ffirst_tok_kq -> value = (Ffirst_tok_kq -> value) + 1;
            //free(Ffirst_tok_kq); 
        }
        else{
            dictionary_insert(frequencyDictionary, first_kq);
            list_append(frequencyList, first_kq); 
            //free(first_kq); 
        }
                
        if(dictionary_find(lengthDictionary, firsttok)==NULL){
            dictionary_insert(lengthDictionary, first_kq2);
            list_append(lengthList, first_kq2); 
            //free(first_kq2); 
        }
        //------------adding the first word/token collected ------------------- 

        while (store_token != NULL){ 
            // ----------adding all the stop words to a Stoplist---------------
            while (stopChecker == 0)
            {
                char *tempword = strdup(store_token); 
                char *find = strchr(tempword, "\n"); 
                if(strcmp(STOPWORD, tempword)==0){
                    stopChecker = 1; 
                    break; 
                }
                else{
                    KVPair* temppair = (KVPair*) malloc(sizeof(KVPair)); 
                    char* tempword = strdup(store_token); 
                    temppair -> key = tempword; 
                    temppair -> value = 1;
                    list_append(stopwords, temppair);
                    break; 
                }
            }
            // ----------adding all the stop words to a Stoplist---------------
            store_token = strtok(NULL, white); 
            if(store_token!=NULL){
                char *token_dup = strdup(store_token);
                KVPair* freq_Kq = (KVPair*) malloc(sizeof(KVPair)); 
                KVPair* length_kq = (KVPair*) malloc(sizeof(KVPair));                 
                freq_Kq ->key = token_dup; 
                freq_Kq -> value = 1; 
                length_kq -> key = token_dup; 
                length_kq -> value = word_length(token_dup, "");
                // adding every token as a KVPair into dictionary of lengths & list of lengths  
                if(dictionary_find(frequencyDictionary, token_dup)==NULL){
                    dictionary_insert(lengthDictionary, length_kq); 
                    list_append(lengthList, length_kq); 
                }
                // adding every token as a KVPair into dictionary of frequencies & list of frequencies 
                KVPair* found = dictionary_find(frequencyDictionary, token_dup);
                if(dictionary_find(frequencyDictionary, token_dup)!=NULL){
                    found -> value = (found -> value)+1; 
                }
                else{
                    dictionary_insert(frequencyDictionary, freq_Kq);
                    list_append(frequencyList, freq_Kq);
                }
            }
        }         
    }
    KVPair* sp = (KVPair*) malloc(sizeof(KVPair));
    sp -> key = STOPWORD;
    sp -> value = 1;
    int sentenceStop = list_find_element(sentenceList, sp); //finding out at which index "====" exists 
    int i; 
    // looping through and deleting the stop words from the sentenceList 
    for(i=0; i<= sentenceStop; i++){
        list_del_index(sentenceList,0); 
    }
    
    int j; 
    for(j =0; j < list_length(stopwords); j++){
        KVPair *temp = list_get_index(stopwords, j);
        //removing the stop words from both lists  
        list_del_index(frequencyList, 0); 
        list_del_index(lengthList, 0); 
        //removing the stop words from both dictionaries 
        if(dictionary_find(lengthDictionary, temp->key) != NULL){
            dictionary_delete(lengthDictionary, temp-> key); 
        }
        if(dictionary_find(frequencyDictionary, temp->key) != NULL){
            dictionary_delete(frequencyDictionary, temp-> key); 
        }
    }
    //-------removing "====" from all 4 data structures--------
    list_del_index(lengthList, 0); 
    list_del_index(frequencyList, 0);
    if(dictionary_find(lengthDictionary, STOPWORD) != NULL){
            dictionary_delete(lengthDictionary, STOPWORD); 
    }
    if(dictionary_find(frequencyDictionary, STOPWORD) != NULL){
            dictionary_delete(frequencyDictionary, STOPWORD); 
    }
    //-------removing "====" from all 4 data structures--------

    // ---------sorting both lists(descending)----- 
    list_sort(lengthList, false); 
    list_sort(frequencyList, false); 
    // ---------sorting both lists(descending)----- 

     //------------keeping first 25 for frequency and 20 for length----
    //getting first 25 words in dictionary of frequencies
    while(list_length(frequencyList)>25){
        KVPair *delpair = list_del_index(frequencyList, list_length(frequencyList)-1); 
        dictionary_delete(frequencyDictionary, delpair->key); 
    }
    //getting first 20 words in dictionary of lengths
    while(list_length(lengthList)>20){
        KVPair *delpair = list_del_index(lengthList, list_length(lengthList)-1); 
        dictionary_delete(lengthDictionary, delpair->key); 
    }
    
    // using the function given to print output into the HTML file 
    int k; 
    for(k =0; k< list_length(sentenceList); k++){
        KVPair *holder = list_get_index(sentenceList, k); 
        printOutput(frequencyDictionary, lengthDictionary, holder->key); 
    }

    // Hint: You can try keeping the same KV elements in both dictionary and list.
    //       Give the list a comparator function which takes into account both word frequency and alphabetic order of word.
    //       Sort list once all words have been processed by the dictionary
    //       Then you can remove the ones not needed form the dictionary before passing it in.
}