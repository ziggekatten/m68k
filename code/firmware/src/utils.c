/*
* @Author: Mats Brorson
* @Date: 2023-02-03
* 
* @Description: Functions for various utilities needed to make life easier when not using stdlibc.
*/

/* Function to provide hex rpresentation for ASCII output */
static char *itohexa_helper(char *dest, unsigned x) {
  if (x >= 16) {
    dest = itohexa_helper(dest, x/16);
  }
  *dest++ = "0123456789abcdef"[x & 15];
  return dest;
}

char *itohexa(char *dest, unsigned x) {
  *itohexa_helper(dest, x) = '\0';
  return dest;
}