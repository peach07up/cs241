#include "editor.h"
#include "document.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * You can programatically test your text editor.
 */
int main() {
    // Setting up a docment based on the file named 'filename'.
    char *filename = "test.txt";
    Document *document = Document_create_from_file(filename);
    
    handle_display_command(document, "p");
    handle_write_command(document, "w 1 hello");
    handle_display_command(document, "p");
    handle_display_command(document, "p 2");
    
    handle_write_command(document, "w 2 world");
    handle_display_command(document, "p");
    
    handle_write_command(document, "w 4 Skip Line");
    handle_display_command(document, "p");
    
    handle_write_command(document, "w 2 Overwrite$And$MultiLine");
    handle_display_command(document, "p");
    
    handle_append_command(document, "a 1 world");
    handle_display_command(document, "p");
    handle_append_command(document, "a 4 Append$Multi$Line");
    handle_display_command(document, "p");
    
    handle_delete_command(document, "d 10");
    handle_delete_command(document, "d 2");
    handle_display_command(document, "p");
    
    handle_search_command(document, "/Line");
    handle_search_command(document, "/Blargh");
    
    handle_append_command(document, "a 8 L$L$L$L");
    handle_display_command(document, "p 8");
    handle_display_command(document, "p 2");
    handle_display_command(document, "p 5");
    
    handle_display_command(document, "p");
    handle_save_command(document, "test.txt");
}

