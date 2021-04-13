#include "../includes/Philosophers_42.h"

static  int     nb_length(unsigned long n)
{
    int     count;
    
    count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count = count + 1;
	}
    return (count);
}

static  int    ft_itoa_on_buffer(unsigned long timestamp, char *str)
{
    int nb_len;
    int index;

    nb_len = nb_length(timestamp);
    index = --nb_len;
    while (nb_len >= 0)
    {
        str[nb_len] = timestamp % 10 + '0';
        timestamp /= 10;
        nb_len--;
    }
    return (index);
}

void    print_log(unsigned long timestamp, int id, char *log, t_philo *p)
{
    char str[254];
    int     index;
    
    if (g_stop != -1)
         return ;
    timestamp -= g_beginning;
    index = ft_itoa_on_buffer(timestamp, str);
    index++;
    str[index++] = ' ';
    index += ft_itoa_on_buffer(id, &str[index]);
    index++;
    str[index++] = ' ';
    ft_strcpy(&str[index], log);
	sem_wait(p->print);
    write(1, str, ft_strlen(str));
    sem_post(p->print);
}
