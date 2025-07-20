/*
3_trait.md
为struct DB实现Queryable trait执行SQL
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In standard C, we simulate traits using function pointers
struct DB {
    char* (*execute_query)(struct DB* this, const char* query);
    void (*free_result)(struct DB* this, char* result);
};

// MySQL implementation
char* mysql_execute(struct DB* this, const char* query) {
    printf("MySQL executing: %s\n", query);
    return strdup("MySQL result");
}

void mysql_free_result(struct DB* this, char* result) {
    free(result);
}

struct DB create_mysql_db() {
    struct DB db;
    db.execute_query = mysql_execute;
    db.free_result = mysql_free_result;
    return db;
}

// SQLite implementation
char* sqlite_execute(struct DB* this, const char* query) {
    printf("SQLite executing: %s\n", query);
    return strdup("SQLite result");
}

void sqlite_free_result(struct DB* this, char* result) {
    free(result);
}

struct DB create_sqlite_db() {
    struct DB db;
    db.execute_query = sqlite_execute;
    db.free_result = sqlite_free_result;
    return db;
}

int main() {
    struct DB mysql_db = create_mysql_db();
    struct DB sqlite_db = create_sqlite_db();
    
    char* result1 = mysql_db.execute_query(&mysql_db, "SELECT * FROM users");
    printf("Result: %s\n", result1);
    mysql_db.free_result(&mysql_db, result1);
    
    char* result2 = sqlite_db.execute_query(&sqlite_db, "SELECT * FROM products");
    printf("Result: %s\n", result2);
    sqlite_db.free_result(&sqlite_db, result2);
    
    return 0;
}
