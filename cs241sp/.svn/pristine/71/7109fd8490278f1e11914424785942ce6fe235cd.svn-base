#include "editor.h"
#include "document.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *get_filename(int argc, char *argv[]) {
    
    // take a look at editor_main.c to see what this is used for
    return argv[1];
}

char space = ' ';
char dollar = '$';

void handle_display_command(Document *document, const char *command) {
    if (Document_size(document) <= 0) {
        print_document_empty_error();
    }
    
    size_t numtokens;
    char **tokens = strsplit(command, &space, &numtokens);
    
    int first_line = 0;
    int last_line = (int)Document_size(document);
    
    if (numtokens > 1) {
        int line_number = atoi(tokens[1]) - 1;
        if (line_number >= last_line) {
            invalid_line();
        }
        
        first_line = first_line > line_number - 5 ? first_line : line_number - 5;
        last_line = last_line < line_number + 6 ? last_line : line_number + 6;
    }
    
    for (size_t line = (size_t)first_line; line < (size_t)last_line; line++) {
        print_line(document, line);
    }
}

void handle_write_command(Document *document, const char *command) {
    size_t numtokens;
    char **tokens = strsplit(command, &space, &numtokens);
    size_t start_line = (size_t)(atoi(tokens[1]) - 1);
    
    size_t num_lines;
    char **lines = strsplit(command + 3 + strlen(tokens[1]), &dollar, &num_lines);
    
    if (start_line >= Document_size(document)) {
        Document_insert_line(document, start_line, "");
    }
    
    for (size_t line = 0; line < num_lines; line++) {
        if (line == 0) {
            Document_set_line(document, start_line, lines[0]);
        } else {
            Document_insert_line(document, start_line + line, lines[line]);
        }
    }
}

void handle_append_command(Document *document, const char *command) {
    size_t numtokens;
    char **tokens = strsplit(command, &space, &numtokens);
    size_t start_line = (size_t)(atoi(tokens[1]) - 1);
    
    size_t num_lines;
    char **lines = strsplit(command + 3 + strlen(tokens[1]), &dollar, &num_lines);
    int new_line = 0;
    
    if (start_line >= Document_size(document))
    {
        //Document_insert_line(document, start_line, "");
        new_line = 1;
    }
    
    for (size_t line = 0; line < num_lines; line++) {
        if (line == 0 && new_line == 0) {
            size_t length = strlen(Document_get_line(document, start_line));
            length += strlen(lines[0]);
            
            char *temp = malloc(length + 1);
            strcpy(temp, Document_get_line(document, start_line));
            strcat(temp, lines[0]);
            
            Document_set_line(document, start_line, temp);
            free(temp);
        } else {
            Document_insert_line(document, start_line + line, lines[line]);
        }
    }
}

void handle_delete_command(Document *document, const char *command) {
    size_t numtokens;
    char **tokens = strsplit(command, &space, &numtokens);
    size_t delete_line = (size_t)(atoi(tokens[1]) - 1);
    if (delete_line > Document_size(document)) {
        invalid_line();
    }
    else {
        Document_delete_line(document, delete_line);
    }
}

void handle_search_command(Document *document, const char *command) {
    //char *strstr(const char *haystack, const char *needle);
    
    const char *search_term = command + 1;
    size_t num_lines = Document_size(document);
    for (size_t line = 0; line < num_lines; line++) {
        const char *line_content = Document_get_line(document, line);
        char *found = strstr(line_content, search_term);
        
        if (found != NULL) {
            print_search_line(line + 1, line_content, found, search_term);
        }
    }
}

void handle_save_command(Document *document, const char *filename) {
    Document_write_to_file(document, filename);
}