#include "unistd.h"
#include "stdarg.h"

void put_str(char *str, int *len)
{
    if(!str)
        str = "(null)";
    while(*str)
        *len += write(1, str++, 1);
}

void put_digit(long long int nbr, int base, int *len)
{
    char *hexa;

    hexa = "0123456789abcdef";
    if(nbr < 0)
    {
        nbr *= -1;
        *len += write(1, "-", 1);
    }
    if(nbr >= base)
        put_digit((nbr/base), base, len);
    *len += write(1, &hexa[nbr % base], 1);
}

int ft_printf(const char *format, ... )
{
    int len;
    va_list lst;

    len = 0;
    va_start(lst, format);
    while(*format)
    {
        if (*format == '%' && *(format + 1))
        {
            format++;
            if(*format == 's')
                put_str(va_arg(lst, char *), &len);
            else if(*format == 'd')
                put_digit((long long int)va_arg(lst, int), 10, &len);
            else if(*format == 'x')
                put_digit((long long int)va_arg(lst, unsigned int), 16, &len);
        }
        else
            len += write(1, format, 1);
        format++;
    }
    return(va_end(lst), len);
}
