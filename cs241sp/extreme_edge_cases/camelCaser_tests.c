#include "camelCaser_tests.h"

#include "camelCaser.h"

/*
 * Testing function for various implementations of camelCaser.
 *
 * @param  camelCaser   A pointer to the target camelCaser function.
 * @return              Correctness of the program (0 for wrong, 1 for correct).
 */
int test_camelCaser (char ** (* camelCaser)(const char *))
{
    char * input = "The Heisenbug is an incredible creature. Facenovel servers get their power from its indeterminism. Code smell can be ignored with INCREDIBLE use of air freshener. God objects are the new religion.";
    char ** n = camel_caser(input);
    printf("%s\n", *(n+1) );
// TODO: Return 1 if the passed in function works properly; 0 if it doesn't.
    return 1;
}
