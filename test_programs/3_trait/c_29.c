/*
3_trait.md
为struct Window实现Closable trait
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we simulate traits using function pointers
struct Window {
    int is_open;
    void (*close)(struct Window*);
    void (*print_status)(const struct Window*);
};

void window_close(struct Window* this) {
    this->is_open = 0;
    printf("Window closed\n");
}

void window_print_status(const struct Window* this) {
    printf("Window is %s\n", this->is_open ? "open" : "closed");
}

struct Window* create_window() {
    struct Window* w = malloc(sizeof(struct Window));
    w->is_open = 1;
    w->close = window_close;
    w->print_status = window_print_status;
    return w;
}

int main() {
    struct Window* win = create_window();
    win->print_status(win);
    win->close(win);
    win->print_status(win);
    free(win);
    return 0;
}
