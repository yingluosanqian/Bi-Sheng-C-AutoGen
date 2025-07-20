/*
4_无栈协程.md
async函数处理视频播放模拟
*/
#include <stdio.h>
#include <stdlib.h>

void play_frame(int frame_num) {
    printf("Playing frame %d\n", frame_num);
}

int main() {
    // Simulate playing 3 frames sequentially
    for (int i = 1; i <= 3; i++) {
        play_frame(i);
    }
    return 0;
}