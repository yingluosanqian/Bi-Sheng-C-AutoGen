/*
4_无栈协程.md
async函数处理音频播放模拟
*/
#include <stdio.h>
#include <stdlib.h>

void play_audio(int duration, void (*callback)(int)) {
    printf("Playing audio for %dms\n", duration);
    callback(duration);
}

void audio_callback(int duration) {
    printf("Finished playing %dms of audio\n", duration);
}

int main() {
    play_audio(1000, audio_callback);
    return 0;
}