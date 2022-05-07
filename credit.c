//#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *take_digits(char *str, int str_len, int which)
{
	char	*digits;
	int		count;
	int		i;
	int		_idx;
	count = str_len / 2;
	digits = (char *)malloc(sizeof(char) * count);
	_idx = 0;
	if (which == 1)
	{
		i = 2;
		while (count--)
		{
			digits[_idx++] = str[str_len - i];
			i += 2;
		}
	}
	else if (which == 0)
	{
		if (str_len == 13 || str_len == 15)
			count += 1;
		i = 1;
		while (count--)
		{
			digits[_idx++] = str[str_len - i];
			i += 2;
		}
	}
	return (digits);
}

static int	len(long nb)
{
	int	l;
	l = 0;
	if (nb == 0)
		l = 1;
	else if (nb < 0)
	{
		nb = -nb;
		l++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(long n)
{
	long	nb;
	char	*string;
	int		i;
	nb = n;
	i = len(nb);
	string = (char *)malloc (sizeof(char) * (len(nb) + 1));
	if (!string)
		return (NULL);
	string[i--] = '\0';
	if (nb == 0)
		string[0] = '0';
	if (nb < 0)
	{
		string[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		string[i--] = 48 + (nb % 10);
		nb = nb / 10;
	}
	return (string);
}

int	ft_atoi(char c)
{
	int number;
	number = 0;
	if (c >= '0' && c <= '9')
		number = number * 10 + (c - '0');
	return (number);
}

int main(void)
{
	char	*str;
	char	*digits;
	char	*other_digits;
	long 	number;
	int		str_len;
	int		digit_len;
	int		*multiplied_number;
	int		*other_multiplied_number;
	int		_idx;
	int		temp_len;
	int		digit_sum;
	int		other_digit_len;
	printf("Number: ");
	scanf("%ld", &number);
	str  = ft_itoa(number);
	str_len = ft_strlen(str);
	digits = take_digits(str, str_len, 1);
	other_digits = take_digits(str, str_len, 0);
	digit_len = ft_strlen(digits);
	other_digit_len = ft_strlen(other_digits);
	temp_len = digit_len;
	multiplied_number = (int *)malloc(sizeof(int) * digit_len);
	other_multiplied_number = (int *)malloc(sizeof(int) * other_digit_len);
	_idx = 0;
	while (temp_len--)
	{
		multiplied_number[_idx] = ft_atoi(digits[_idx]) * 2;
		_idx++;
	}
	_idx = 0;
	temp_len = other_digit_len;
	while (temp_len--)
	{
		other_multiplied_number[_idx] = ft_atoi(other_digits[_idx]);
		_idx++;
	}
	_idx = 0;
	temp_len = digit_len;
	digit_sum = 0;
	while (temp_len--)
	{
		if (multiplied_number[_idx] >= 10)
			digit_sum += (1 + (multiplied_number[_idx] % 10));
		else
			digit_sum += multiplied_number[_idx];
		_idx++;
	}
	_idx = 0;
	temp_len = other_digit_len;
	while (temp_len--)
		digit_sum += other_multiplied_number[_idx++];
	if ((digit_sum % 10) == 0)
	{
		if (str_len == 15)
		{
			if (str[0] == '3' && (str[1] == '4' || str[1] == '7'))
				printf("AMEX\n");
			else
				printf("INVALID\n");
		}
		else if (str_len == 16)
		{
			if ((str[0] == '5' || str[0] == '2') && (str[1] == '1' || str[1] == '2' || str[1] == '3' || str[1] == '4' || str[1] == '5'))
				printf("MASTERCARD\n");
			else if (str[0] == '4')
				printf("VISA\n");
			else
				printf("INVALID\n");
		}
		else if (str_len == 13)
			printf("VISA\n");
		else
			printf("INVALID\n");
	}
	else
		printf("INVALID\n");
}
//16 digit: 4 0 0 3 6 0 0 0 0 0 0 0 0 0 1 4
//got: 		4   0   6   0   0   0   0   1  --> 8
//other:	  0   3   0   0   0   0   0   4
//13 digit: 4 0 0 3 6 0 0 0 0 0 0 0 0
//got:        0   3   0   0   0   0 --> 6
//15 digit: 4 0 0 3 6 0 0 0 0 0 0 0 0 0 1
//got:        0   3   0   0   0   0   0 --> 7
//AMEX: 3 7 8 2 8 2 2 4 6 3 1 0 0 0 5