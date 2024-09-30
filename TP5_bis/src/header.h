/* Function prototype */
int allIntegersSum(int n);


int allIntegersSum(int n) {
    int sum = 0;
    int i;
    for(i = 1; i <= n; i++){
        sum = sum + i;
    }
    return sum;
};

int peerSum(int n) {
    int sum = 0;
    int i;
    for(i = 1; i <= n; i++) {
        if(i % 2 == 0){
            printf("%d + ", i);
            sum = sum + i;
        }
    };
    return sum;
};

int oddSum(int n) {
    int sum = 0;
    int i;
    for(i = 1; i <= n; i++) {
        if(i % 2 == 1){
            printf("%d + ", i);
            sum = sum + i;
        }
    };
    return sum;
}

