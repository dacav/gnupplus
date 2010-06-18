#ifndef __defined_test_environ_h
#define __defined_test_environ_h
#ifdef __cplusplus
extern "C" {
#endif

/* Builds the test environment:
 *
 * -> export PATH="$PATH:."
 */
void build_environment ();

#ifdef __cplusplus
}
#endif
#endif // __defined_test_environ_h

