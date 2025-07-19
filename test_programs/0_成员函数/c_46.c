/*
0_成员函数.md
为struct Regex添加match和replace成员函数
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Regex {
    char* pattern;
    int flags;
};

// Global functions for regex operations in standard C
struct Regex* create_regex(const char* pattern, int flags) {
    struct Regex* regex = malloc(sizeof(struct Regex));
    if (regex) {
        regex->pattern = malloc(strlen(pattern) + 1);
        strcpy(regex->pattern, pattern);
        regex->flags = flags;
    }
    return regex;
}

int regex_match(struct Regex* regex, const char* text) {
    if (!regex || !text) return 0;
    // Simplified pattern matching - just check if pattern exists in text
    return strstr(text, regex->pattern) != NULL;
}

char* regex_replace(struct Regex* regex, const char* text, const char* replacement) {
    if (!regex || !text || !replacement) return NULL;
    
    char* found = strstr(text, regex->pattern);
    if (!found) {
        // No match, return copy of original text
        char* result = malloc(strlen(text) + 1);
        strcpy(result, text);
        return result;
    }
    
    // Calculate new string length
    int pattern_len = strlen(regex->pattern);
    int replacement_len = strlen(replacement);
    int text_len = strlen(text);
    int new_len = text_len - pattern_len + replacement_len + 1;
    
    char* result = malloc(new_len);
    
    // Copy part before match
    int prefix_len = found - text;
    strncpy(result, text, prefix_len);
    result[prefix_len] = '\0';
    
    // Add replacement
    strcat(result, replacement);
    
    // Add part after match
    strcat(result, found + pattern_len);
    
    return result;
}

void free_regex(struct Regex* regex) {
    if (regex) {
        free(regex->pattern);
        free(regex);
    }
}

int main() {
    struct Regex* email_regex = create_regex("@", 0);
    
    const char* test_text = "Contact us at support@example.com";
    
    printf("Testing regex pattern: %s\n", email_regex->pattern);
    printf("Test text: %s\n", test_text);
    
    // Test match function
    if (regex_match(email_regex, test_text)) {
        printf("Pattern matched!\n");
    } else {
        printf("Pattern not found.\n");
    }
    
    // Test replace function
    char* replaced = regex_replace(email_regex, test_text, " [EMAIL] ");
    if (replaced) {
        printf("After replacement: %s\n", replaced);
        free(replaced);
    }
    
    free_regex(email_regex);
    return 0;
}
