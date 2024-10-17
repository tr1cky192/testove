#include <stdio.h>
#include <stdlib.h>

void copyImage(int *source, int *destination, int frame_width, int frame_height, int pic_width, int pic_height, int pic_x, int pic_y) {
    for (int i = 0; i < pic_height; i++) {
        for (int j = 0; j < pic_width; j++) {

            int source_index = (pic_y + i) * frame_width + (pic_x + j);
            int destination_index = i * pic_width + j;
            

            destination[destination_index] = source[source_index];
        }
    }
}

int main() {
    int frame_width, frame_height, pic_width, pic_height, pic_x, pic_y;


    printf("Enter frame_width: ");
    scanf("%d", &frame_width);
    printf("Enter frame_height: ");
    scanf("%d", &frame_height);
    printf("Enter pic_width: ");
    scanf("%d", &pic_width);
    printf("Enter pic_height: ");
    scanf("%d", &pic_height);
    printf("Enter pic_x: ");
    scanf("%d", &pic_x);
    printf("Enter pic_y: ");
    scanf("%d", &pic_y);


    int *source = (int *)malloc(frame_width * frame_height * sizeof(int));
    int *destination = (int *)malloc(pic_width * pic_height * sizeof(int));


    for (int i = 0; i < frame_width * frame_height; i++) {
        source[i] = rand() % 256;
    }


    printf("\n====================\n");
    printf("Source array (Full Frame):\n");
    printf("====================\n");
    for (int i = 0; i < frame_height; i++) {
        for (int j = 0; j < frame_width; j++) {
            printf("%3d ", source[i * frame_width + j]); 
        }
        printf("\n");
    }

    copyImage(source, destination, frame_width, frame_height, pic_width, pic_height, pic_x, pic_y);

    printf("\n====================\n");
    printf("Destination array (Copied Section):\n");
    printf("====================\n");
    for (int i = 0; i < pic_height; i++) {
        for (int j = 0; j < pic_width; j++) {
            printf("%3d ", destination[i * pic_width + j]); 
        }
        printf("\n");
    }

    free(source);
    free(destination);

    return 0;
}
