#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partition(char *str[], int front, int back){
    int middle = front;
    char *pivot = str[front];
    int i;
    char* tmp;
    for (i = front+1; i <= back; i++) {
        if(strcasecmp(pivot,str[i]) > 0){
            tmp = str[++middle];
            str[middle] = str[i];
            str[i] = tmp;
        }
    }
    str[front] = str[middle];
    str[middle] = pivot;

    return middle;
}

void quickSort(char *str[], int front, int back){
    if (front+1 == back) {
        if(strcasecmp(str[front], str[back]) > 0) {
            char *tmp = str[front];
            str[front] = str[back];
            str[back] = tmp;
        }
        return;
    }
    else if (front >= back)
        return;
    int middle = partition(str, front, back);
    quickSort(str, front, middle-1);
    quickSort(str, middle+1, back);
}

//example
/*
void main() {
	char* be_sorted[5] = {"hi", "Good", "hello", "bye", "aperiodic"};
	quickSort(be_sorted,0,4);

	for (int i = 0 ; i < 5; i++){
		printf("%s\n",be_sorted[i]);
	}

}
*/
