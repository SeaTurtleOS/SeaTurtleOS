void int_to_string(char str[], int num){
    int i, rem, len = 0, n;

    n = num;
    // Firstly, find the length of the number.
    while (n != 0) {
        len++;
        n /= 10;
    }

    for (i = 0; i < len; i++) {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
        // rem + '0', essentially converting rem from digit to string
        // '0' has an ascii code of 48. If rem is 0, the whole character (rem + '0') evaluates out to the character '0'
        // Similarly, if rem is 7, the character (rem + '0') would evaluate to the character '7'
    }
    str[len] = '\0';
    // Can't forget to cap the string with a '\0' !
}