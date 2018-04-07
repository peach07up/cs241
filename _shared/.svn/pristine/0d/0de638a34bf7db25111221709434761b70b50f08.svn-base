char* read_last_half(const char* filename) { // returns NULL if file could not be loaded
    FILE* file = fopen(filename, "r"); 
    if (!file) { printf("%s:%s", filename, strerror( errno )); return NULL; }

    fseek(file, 0, SEEK_END);
    long posn = ftell(file);
    long size = posn/2; // we want half the file!

    //fseek(file, - size , SEEK_END);
    fseek(file, size, SEEK_SET);
    char*buffer = malloc( size +1);

    // always close resources - watch out for early-returns...
    if(!buffer) { fclose(file);  return NULL; }

    fread(buffer, 1, size, file);
    fclose(file);

    buffer[ size ] = 0; // terminate the buffer so that it can be used as a C string
    return buffer;
}
