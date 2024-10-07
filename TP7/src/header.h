/* Function prototype */
int getArraySize(int iteration) {
    int size;
    printf("\nNumber to test : ");
    scanf("%d", &size);
    return size;
}
int getBiggestValueInArray(int array) {
    int* p;
    int* index = 0;
    int tmp = array[index];
    for(p=1;p<strlen(array);p++) {
        if(tmp<array[p]) {
            tmp = array[p];
        }
    }
    return tmp;
}

/*
int getUserValue(char * expValue) {
    int userValue;
    printf("\nValue of %s : ", expValue);
    scanf("%d", &userValue);
    return userValue;
}

int testBiggestValue(int value1, int value2, int value3) {
    int maxValue;
    if(value1 > value2) {
        if(value1 > value3) {
            maxValue = value1;
        }
        else {
            maxValue = value3;
        }
    }
    else {
        if(value2>value3) {
            maxValue = value2;
        }
        else {
            maxValue = value3;
        }
    }
    return maxValue;
}

*/