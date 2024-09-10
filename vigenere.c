#include <stdio.h>
#include <string.h>
#include <ctype.h> //tolower

struct CipherData {
    char ciphertext[1000];
    char key[100];
    char plaintext[1000];
};

// Calculate Function of Index of Coincidence
float calculateCoincidence(char* text, int textLength) {
    int frequency[26] = {0};
    int total = 0;
    int i;

    for (i = 0; i < textLength; i++) {
        char c = text[i];
        if ('A' <= c && c <= 'Z') {
            frequency[c - 'A']++;
            total++;
        }
    }

    float coincidence = 0;

    for (i = 0; i < 26; i++) {
        coincidence += (frequency[i] * (frequency[i] - 1));
    }

    return coincidence / (total * (total - 1));
}

// Function to decrypt
void decryptFunc(int groupnum, int length, int keylen, char* key, char* ciphertext, char* decryptedText) {
    int i;
    int iteration = length/keylen;
    printf("Iteration: %d\n",iteration);

    for (i = 0; i < iteration; i++) {
        char c = ciphertext[groupnum + i * keylen];
        c = c - key[groupnum] + 'A';
        if (c < 'A')
            c += 26;
        decryptedText[groupnum + i * keylen] = tolower(c);
    }
    
}

// Function to find the most frequent character in a string
char findMostFrequentChar(char* text) {
    int frequency[26] = {0};
    int maxFrequency = 0;
    char mostFrequentChar = 'A';

    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        char c = text[i];
        if ('A' <= c && c <= 'Z') {
            frequency[c - 'A']++;
            if (frequency[c - 'A'] > maxFrequency) {
                maxFrequency = frequency[c - 'A'];
                mostFrequentChar = c;
            }
        }
    }

    return mostFrequentChar;
}

int main() {
    struct CipherData data;

    printf("Vigenere Cipher Text: ");
    fgets(data.ciphertext, sizeof(data.ciphertext), stdin);

    data.ciphertext[strcspn(data.ciphertext, "\n")] = '\0';

    int textLength = strlen(data.ciphertext);

    int bestKeyLength = 0;
    float highestAvgIOC = 0.0;

    printf("\n");
    printf("Cipher Length: %d\n", textLength);

    for (int keyLength = 1; keyLength <= 10; keyLength++) {
        printf("Key Length: %d\n", keyLength);
        float ioc = 0.0;

        for (int i = 0; i < keyLength; i++) {
            char groupText[1000];
            int groupTextLength = 0;

            for (int j = i; j < textLength; j += keyLength) {
                groupText[groupTextLength++] = data.ciphertext[j];
            }

            groupText[groupTextLength] = '\0';

            ioc += calculateCoincidence(groupText, groupTextLength);

            printf("Group %d: %s\n", i + 1, groupText);
        }

        ioc /= keyLength;
        printf("Average Index of Coincidence of All Group: %.4f\n\n", ioc);

        if (ioc > highestAvgIOC) {
            highestAvgIOC = ioc;
            bestKeyLength = keyLength;
        }
    }

    printf("Best Key Length: %d with Highest Average IOC: %.4f\n", bestKeyLength, highestAvgIOC);

    printf("\nDecrypting using Best Key Length...\n");
    printf("Best Key Length: %d\n", bestKeyLength);

    data.plaintext[0] = '\0';

    for (int i = 0; i < bestKeyLength; i++) {
        char groupText[1000];
        int groupTextLength = 0;
        for (int j = i; j < textLength; j += bestKeyLength) {
            groupText[groupTextLength++] = data.ciphertext[j];
        }
        groupText[groupTextLength] = '\0';
        char mostFrequentChar = findMostFrequentChar(groupText);
        printf("Most Frequent Character: %c\n", mostFrequentChar);
        if (mostFrequentChar >= 'E') {
            data.key[i] = 'A' + mostFrequentChar - 'E';
            printf("Key is %c\n", data.key[i]);
        } else {
            data.key[i] = 'A' + 26 + mostFrequentChar - 'E';
            printf("Key is %c\n", data.key[i]);
        }

        decryptFunc(i, textLength, bestKeyLength, data.key, data.ciphertext, data.plaintext);
        printf("\n");
    }

    printf("KEY:\n%s\n", data.key);
    printf("Decrypted Text:\n%s\n", data.plaintext);
    printf("\n");
    printf("\n");

    for (int w = 0; w < textLength; w++)
    {
        printf("%c", data.plaintext[w]);
        if ((w+1) % bestKeyLength == 0)
            printf(" ");
    }
    
    printf("\n");
    printf("Update key to IFLMZAM\n");
    data.key[3] = 'S';
    for (int i = 0; i < bestKeyLength; i++) {
        decryptFunc(i, textLength, bestKeyLength, data.key, data.ciphertext, data.plaintext);
    }
    printf("KEY:\n%s\n", data.key);
    printf("Decrypted Text:\n%s\n", data.plaintext);
    printf("\n");
    printf("\n");

    for (int w = 0; w < textLength; w++)
    {
        printf("%c", data.plaintext[w]);
        if ((w+1) % bestKeyLength == 0)
            printf(" ");
    }

    printf("\n");
    printf("Update key to YFLSZAM\n");
    data.key[0] = 'Y';
    for (int i = 0; i < bestKeyLength; i++) {
        decryptFunc(i, textLength, bestKeyLength, data.key, data.ciphertext, data.plaintext);
    }
    printf("KEY:\n%s\n", data.key);
    printf("Decrypted Text:\n%s\n", data.plaintext);
    printf("\n");
    printf("\n");

    for (int w = 0; w < textLength; w++)
    {
        printf("%c", data.plaintext[w]);
        if ((w+1) % bestKeyLength == 0)
            printf(" ");
    }

    
    
    
    printf("\n");

    

    return 0;
}
