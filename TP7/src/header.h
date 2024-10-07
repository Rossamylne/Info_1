/* Function prototype */
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