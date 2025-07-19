/*
3_trait.md
为struct Button实现Clickable trait
*/
#include <stdio.h>

// In standard C, we simulate traits using function pointers
struct Button {
    int clicks;
    void (*click)(struct Button*);
    void (*show_clicks)(const struct Button*);
};

void button_click(struct Button* this) {
    this->clicks++;
    printf("Button clicked! Total clicks: %d\n", this->clicks);
}

void button_show_clicks(const struct Button* this) {
    printf("Current clicks: %d\n", this->clicks);
}

struct Button create_button() {
    struct Button btn = {
        .clicks = 0,
        .click = button_click,
        .show_clicks = button_show_clicks
    };
    return btn;
}

int main() {
    struct Button btn = create_button();
    
    btn.click(&btn);
    btn.show_clicks(&btn);
    
    btn.click(&btn);
    btn.show_clicks(&btn);
    
    return 0;
}
