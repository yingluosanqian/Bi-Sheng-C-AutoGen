/*
0_成员函数.md
为struct Time添加add_seconds成员函数，增加秒数
*/
#include <stdio.h>
#include <stdlib.h>

// Define Time struct
typedef struct {
    int hours;
    int minutes;
    int seconds;
} Time;

// Global function to add seconds to a Time struct
void add_seconds(Time *time, int seconds_to_add) {
    // Add the seconds
    time->seconds += seconds_to_add;
    
    // Handle overflow
    while (time->seconds >= 60) {
        time->seconds -= 60;
        time->minutes += 1;
    }
    
    while (time->minutes >= 60) {
        time->minutes -= 60;
        time->hours += 1;
    }
    
    // Wrap hours after 24
    while (time->hours >= 24) {
        time->hours -= 24;
    }
}

int main() {
    // Create a Time instance
    Time current_time = {10, 45, 30}; // 10:45:30
    
    // Add 100 seconds
    add_seconds(&current_time, 100);
    
    // Print the result
    printf("{\"hours\": %d, \"minutes\": %d, \"seconds\": %d}", 
           current_time.hours, current_time.minutes, current_time.seconds);
    
    return 0;
}
