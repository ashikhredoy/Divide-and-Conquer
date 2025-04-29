#include <stdio.h>
#include "io.h"

#define BUFFER_SIZE 64

#define MIN     0
#define MAX     1
#define ODD     2
#define EVEN    3
#define MINMAX  4
#define ODDEVEN 5

// prototypes
void reading(int inputBuffer[]);
void transferring(int sourceBuffer[], int destinationBuffer[]);
void processing(int localBuffer[]);
void submitting(int outputBuffer[]);

int main(void) {
    int inputBuffer[BUFFER_SIZE] = {0};
    int localBuffer[BUFFER_SIZE] = {0};
    int outputBuffer[BUFFER_SIZE] = {0};

    // initial read
    reading(inputBuffer);

    // process until opID == -1
    while (inputBuffer[0] != -1) {
        transferring(inputBuffer, localBuffer);
        processing(localBuffer);
        transferring(localBuffer, outputBuffer);
        submitting(outputBuffer);

        // clear buffers for next cycle
        for (int i = 0; i < BUFFER_SIZE; i++) {
            inputBuffer[i] = 0;
            localBuffer[i] = 0;
            outputBuffer[i] = 0;
        }
        reading(inputBuffer);
    }
    return 0;
}

// reads operation ID, count, and data values into inputBuffer
// prints the buffer content
void reading(int inputBuffer[]) {
    int opID = get_value();
    inputBuffer[0] = opID;

    // if -1, end of data
    if (opID == -1) {
        printf("Reading: Input Buffer: %d\n", opID);
        return;
    }

    int count = get_value();
    inputBuffer[1] = count;
    for (int i = 0; i < count; i++) {
        inputBuffer[2 + i] = get_value();
    }

    // print input buffer content
    printf("Reading: Input Buffer:");
    for (int i = 0; i < 2 + count; i++) {
        printf(" %d", inputBuffer[i]);
    }
    printf("\n");
}

// copies length elements from source to destination based on opID and count
// prints both source and destination buffers
void transferring(int sourceBuffer[], int destinationBuffer[]) {
    int opID = sourceBuffer[0];
    int length = 1;
    if (opID != -1) {
        int count = sourceBuffer[1];
        length = 2 + count;
    }
    for (int i = 0; i < length; i++) {
        destinationBuffer[i] = sourceBuffer[i];
    }

    printf("Transferring: Source Buffer:");
    for (int i = 0; i < length; i++) {
        printf(" %d", sourceBuffer[i]);
    }
    printf("\n");

    printf("Transferring: Destination Buffer:");
    for (int i = 0; i < length; i++) {
        printf(" %d", destinationBuffer[i]);
    }
    printf("\n");
}

// processes data in localBuffer and overwrites with result format
// prints processing summary and updated local buffer
void processing(int localBuffer[]) {
    int opID = localBuffer[0];
    int count = localBuffer[1];
    int resultCount = 0;
    int result[2] = {0, 0};

    switch (opID) {
        case MIN: {
            int min = localBuffer[2];
            for (int i = 1; i < count; i++) {
                if (localBuffer[2 + i] < min) min = localBuffer[2 + i];
            }
            result[0] = min;
            resultCount = 1;
            printf("Processing: Min = %d\n", min);
            break;
        }
        case MAX: {
            int max = localBuffer[2];
            for (int i = 1; i < count; i++) {
                if (localBuffer[2 + i] > max) max = localBuffer[2 + i];
            }
            result[0] = max;
            resultCount = 1;
            printf("Processing: Max = %d\n", max);
            break;
        }
        case ODD: {
            int oddCount = 0;
            for (int i = 0; i < count; i++) {
                if (localBuffer[2 + i] % 2 != 0) oddCount++;
            }
            result[0] = oddCount;
            resultCount = 1;
            printf("Processing: Odd count = %d\n", oddCount);
            break;
        }
        case EVEN: {
            int evenCount = 0;
            for (int i = 0; i < count; i++) {
                if (localBuffer[2 + i] % 2 == 0) evenCount++;
            }
            result[0] = evenCount;
            resultCount = 1;
            printf("Processing: Even count = %d\n", evenCount);
            break;
        }
        case MINMAX: {
            int min = localBuffer[2];
            int max = localBuffer[2];
            for (int i = 1; i < count; i++) {
                int val = localBuffer[2 + i];
                if (val < min) min = val;
                if (val > max) max = val;
            }
            result[0] = min;
            result[1] = max;
            resultCount = 2;
            printf("Processing: Min = %d, Max = %d\n", min, max);
            break;
        }
        case ODDEVEN: {
            int oddCount = 0, evenCount = 0;
            for (int i = 0; i < count; i++) {
                if (localBuffer[2 + i] % 2 == 0) evenCount++;
                else oddCount++;
            }
            result[0] = oddCount;
            result[1] = evenCount;
            resultCount = 2;
            printf("Processing: Odd = %d, Even = %d\n", oddCount, evenCount);
            break;
        }
        default:
            printf("Processing: Unknown operation ID %d\n", opID);
    }

    // overwrite localBuffer with result format
    localBuffer[0] = opID;
    localBuffer[1] = resultCount;
    for (int i = 0; i < resultCount; i++) {
        localBuffer[2 + i] = result[i];
    }

    // print updated local buffer
    printf("Processing: Local Buffer:");
    for (int i = 0; i < 2 + resultCount; i++) {
        printf(" %d", localBuffer[i]);
    }
    printf("\n");
}

// prints output buffer and submits results for validation
void submitting(int outputBuffer[]) {
    int resultCount = outputBuffer[1];
    printf("Submitting: Output Buffer:");
    for (int i = 0; i < 2 + resultCount; i++) {
        printf(" %d", outputBuffer[i]);
    }
    printf("\n");

    // validate and display test result
    submit_results(outputBuffer);
}
