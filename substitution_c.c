#include <stdio.h> //printf, fgets
#include <string.h> //strlen
#include <ctype.h> //isalpha
#include <unistd.h> //sleep
#include <stdlib.h> //system

void typewriter() {

}

struct CharFrequency {
    char character;
    int frequency;
};

struct Data_Text {
    char ciphertext;
    char plaintext;
};


int compareDescending(const void *a, const void *b) {
    return ((struct CharFrequency*)b)->frequency - ((struct CharFrequency*)a)->frequency; //Sort Descending
}

int main() {
    char inputString[1000];
    struct CharFrequency charFrequencies[26];
    int frequency[26] = {0};

    printf("Please enter string: ");

    if (fgets(inputString, sizeof(inputString), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    printf("\n");
    printf("\n");
    
    int len = strlen(inputString) - 1; // Why -1 ?? IDK
    printf("Cryptogram length: %d \n", len);

    // Check if the input exceeded the buffer size (999 characters)
    if (len >= sizeof(inputString) - 1) {
        printf("Input exceeds the maximum allowed length.\n");
        return 1;
    }

    // Initialize struct
    for (int i = 0; i < 26; i++) {
        charFrequencies[i].character = 'A' + i;
        charFrequencies[i].frequency = 0; 
    }

    // Define Text struct and Initalize 
    struct Data_Text Data_Text[len];
    for (int i = 0; i < len; i++) {
        Data_Text[i].ciphertext = inputString[i];
        Data_Text[i].plaintext = '_';
    }


    
    for (int i = 0; i < len; i++) {
        char currentChar = inputString[i];

        // Process only alphabetic characters
        if (isalpha(currentChar)) {
            currentChar = tolower(currentChar); // Convert to lowercase
            frequency[currentChar - 'a']++; // Increment the frequency of the character
        }
        else {
            printf("Alphabetic Only! What is %c at %d ??\n", currentChar, i);
            return 1;
        }
    }

    // Frequency to Struct Array
     for (int i = 0; i < 26; i++) {
        charFrequencies[i].frequency = frequency[i];
    }

    // Sort Descending
    qsort(charFrequencies, 26, sizeof(struct CharFrequency), compareDescending);


    //sleep(2);
    //system("clear");
    printf("\n");
    printf("\n");
    

    printf("Frequency of each character (descending order) :\n");
    for (int i = 0; i < 26; i++) 
        printf("%c: %d\n", charFrequencies[i].character, charFrequencies[i].frequency);

    //sleep(1);

    
    //sleep(2);
    //system("clear");
    printf("\n");
    printf("\n");

    // Start Decryption
    // Estimate most frequent letter as e
    printf("Estimate %c as e \n", charFrequencies[0].character);
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == charFrequencies[0].character)
            Data_Text[i].plaintext = 'e';
    }

    //sleep(2);
    //system("clear");
    printf("\n");
    printf("\n");

    // Check Digram near e
    int e_digram[50] = {0};
    for(int k = 1; k < 26; k++) {
        for(int i = 1; i < len -1; i++){
            if(Data_Text[i].ciphertext == charFrequencies[k].character && Data_Text[i+1].plaintext == 'e')
                e_digram[k-1]++;
            else if(Data_Text[i].ciphertext == charFrequencies[k].character && Data_Text[i-1].plaintext == 'e')
                e_digram[k+24]++;
        }
        // First and Last case
        if(Data_Text[0].ciphertext == charFrequencies[k].character && Data_Text[1].plaintext == 'e')
            e_digram[k-1]++;
        else if(Data_Text[len-1].ciphertext == charFrequencies[k].character && Data_Text[len-2].plaintext == 'e')
            e_digram[k+24]++;
        printf("%c%c(?e) : %d\n", charFrequencies[k].character, charFrequencies[0].character, e_digram[k-1]);
        printf("%c%c(e?) : %d\n", charFrequencies[0].character, charFrequencies[k].character, e_digram[k+24]);
        printf("\n");
    }

    //sleep(3);


    // Estimate 8 next frequent letter as t,a,o,i,n,s,h,r
    printf("Estimate %c, %c, %c, %c, %c, %c, %c, %c as t, a, o, i, n, s, h, r \n", charFrequencies[1].character,charFrequencies[2].character,charFrequencies[3].character,charFrequencies[4].character,charFrequencies[5].character,charFrequencies[6].character,charFrequencies[7].character,charFrequencies[8].character);

    // Estimate d ("ed" is frequent, but "de" is not. And D itself is not that frequent)
    int tmp_d = 8;
    for(int i = 9; i < 25; i++) {
        if(e_digram[tmp_d] - e_digram[tmp_d+25] > e_digram[i] - e_digram[i+25])
            tmp_d = i;
        else if(e_digram[tmp_d] - e_digram[tmp_d+25] == e_digram[i] - e_digram[i+25])
            printf("Warning: %c can be 'd', too \n", charFrequencies[i+1].character);
    }

    printf("Estimate %c as d \n", charFrequencies[tmp_d+1].character);
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == charFrequencies[tmp_d+1].character)
            Data_Text[i].plaintext = 'd';
    }


    printf("\n");
    printf("\n");

    
    /*

    printf("Frequent Digrams w D(e): ");
    for(int k = 1; k < 26; k++){
        if(digram[k-1]+digram[k+24] >= 5)
            printf("%c ", charFrequencies[k].character);
    }

    printf("\n");
    
    int digram_freq[22] = {0};
    
    for(int k = 1; k <= 11; k++) {
        for(int i = 1; i < len-1; i++){
            if(Data_Text[i].ciphertext == charFrequencies[k].character && Data_Text[i+1].plaintext == 'e')
                digram_freq[k-1]++;
            else if(Data_Text[i].ciphertext == charFrequencies[k].character && Data_Text[i-1].plaintext == 'e')
                digram_freq[k+10]++;
        }
        // First and Last case
        if(Data_Text[0].ciphertext == charFrequencies[k].character && Data_Text[1].plaintext == 'e')
            digram_freq[k-1]++;
        else if(Data_Text[len-1].ciphertext == charFrequencies[k].character && Data_Text[len-2].plaintext == 'e')
            digram_freq[k+10]++;
        printf("%c%c(?E) : %d\n", charFrequencies[k].character, charFrequencies[0].character, digram_freq[k-1]);
        printf("%c%c(E?) : %d\n", charFrequencies[0].character, charFrequencies[k].character, digram_freq[k+10]);
        printf("\n");
    }

    // Estimate h ("he" is frequent, but "eh" is not)
    int tmp_h = 0;
    for(int i = 1; i < 11; i++){
        if(digram_freq[tmp_h] - digram_freq[tmp_h+11] < digram_freq[i] - digram_freq[i+11])
            tmp_h = i;
        else if(digram_freq[tmp_h] - digram_freq[tmp_h+11] == digram_freq[i] - digram_freq[i+11])
            printf("Warning: %c can be 'h', too \n", charFrequencies[i+1].character);
    }

    printf("Estimate %c as h \n", charFrequencies[tmp_h+1].character);
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == charFrequencies[tmp_h+1].character)
            Data_Text[i].plaintext = 'h';
    }

    */

   /*
    // Estimate Q as t ("QED" is very frequent and seems to be 'the')
    printf("Estimate %c as t \n", 'Q');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'Q')
            Data_Text[i].plaintext = 't';
    }

    */

   // Estimate P as c (Last word 'de__ded' seems to be 'decided' or 'decoded')
   printf("Estimate %c as c \n", 'P');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'P')
            Data_Text[i].plaintext = 'c';
    }
    printf("%c might be i or o \n", 'C');

    // If C is o, "do_od" appears. If C is i, "di_id" seems to be "divid"
    printf("Estimate %c as i \n", 'C');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'C')
            Data_Text[i].plaintext = 'i';
    }
    printf("Estimate %c as v \n", 'H');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'H')
            Data_Text[i].plaintext = 'v';
    }
    

    printf("\n");
    printf("\n");

    // Estimate n ("e_d" seems to be "end")
    for (int i = 0; i < len - 2; i++) {
        if(Data_Text[i].plaintext == 'e' && Data_Text[i+2].plaintext == 'd' && Data_Text[i+1].plaintext == '_')
            printf("%c seems to be 'n'\n", Data_Text[i+1].ciphertext);
    }
  
    printf("\n");
    printf("\n");
   
    // Estimate L as n ('i_divid___' seems to be 'individual')
    printf("Estimate %c as n \n", 'L');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'L')
            Data_Text[i].plaintext = 'n';
    }

    // Estimate G, A, N as u, a, l ('indiviual')
    printf("Estimate %c as u \n", 'G');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'G')
            Data_Text[i].plaintext = 'u';
    }
    printf("Estimate %c as a \n", 'A');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'A')
            Data_Text[i].plaintext = 'a';
    }
    printf("Estimate %c as l \n", 'N');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'N')
            Data_Text[i].plaintext = 'l';
    }

    // Estimate T as b ('_een' at last seems to be 'been')
    printf("Estimate %c as b \n", 'T');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'T')
            Data_Text[i].plaintext = 'b';
    }

    // Estimate X and U as r and y (Word 'al_ead_' seems to be 'already')
    printf("Estimate %c as r \n", 'X');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'X')
            Data_Text[i].plaintext = 'r';
    }
    printf("Estimate %c as y \n", 'U');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'U')
            Data_Text[i].plaintext = 'y';
    }

    // Estimate M and V as s and p (Word 'e__ecially' seems to be 'especially')
    printf("Estimate %c as s \n", 'M');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'M')
            Data_Text[i].plaintext = 's';
    }
    printf("Estimate %c as p \n", 'V');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'V')
            Data_Text[i].plaintext = 'p';
    }

    // Estimate W as g (Word 'durin_' seems to be 'during')
    printf("Estimate %c as g \n", 'W');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'W')
            Data_Text[i].plaintext = 'g';
    }

    // Estimate O, Q and B as f, t and o (Word 'signi_ican_dr_p' seems to be 'significantdrop')
    printf("Estimate %c as f \n", 'O');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'O')
            Data_Text[i].plaintext = 'f';
    }
    printf("Estimate %c as t \n", 'Q');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'Q')
            Data_Text[i].plaintext = 't';
    }
    printf("Estimate %c as o \n", 'B');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'B')
            Data_Text[i].plaintext = 'o';
    }

    // Estimate S as q (Word 'fre_uently' seems to be 'frequently')
    printf("Estimate %c as q \n", 'S');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'S')
            Data_Text[i].plaintext = 'q';
    }

    // Estimate E as h (Word 't_efactt_at' seems to be 'thefactthat')
    printf("Estimate %c as h \n", 'E');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'E')
            Data_Text[i].plaintext = 'h';
    }

    // Estimate I as m (Word 'itsna_e' seems to be 'itsname')
    printf("Estimate %c as m \n", 'I');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'I')
            Data_Text[i].plaintext = 'm';
    }

    // Estimate J as w (Word '_hichteam_ill' seems to be 'whichteamwill')
    printf("Estimate %c as w \n", 'J');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'J')
            Data_Text[i].plaintext = 'w';
    }

    // Estimate F as k (Word 'mar_edby' seems to be 'markedby')
    printf("Estimate %c as k \n", 'F');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'F')
            Data_Text[i].plaintext = 'k';
    }

    // Estimate K as x (Word 'e_perience' seems to be 'experience')
    printf("Estimate %c as x \n", 'K');
    for (int i = 0; i < len; i++) {
        if(Data_Text[i].ciphertext == 'K')
            Data_Text[i].plaintext = 'x';
    }



    //sleep(3);

    printf("\n");
    printf("\n");


  
    

    // Result
    printf("Plain Text: ");
    for (int i = 0; i < len; i++) {
        printf("%c", Data_Text[i].plaintext);
    }

    //sleep(3);

    printf("\n");
    printf("\n");
    printf("\n");

    printf("Plain Text w Cipher: ");
    for (int i = 0; i < len; i++) {
        if (Data_Text[i].plaintext == '_')
            printf("[%c]", Data_Text[i].ciphertext);
        else
            printf("%c", Data_Text[i].plaintext);
    }

    printf("\n");

    return 0;
}
