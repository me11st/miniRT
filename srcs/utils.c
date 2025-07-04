#include "minirt.h"

// Custom atof implementation since it's not in allowed functions
double ft_atof(const char *str)
{
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;
    int decimal_places = 0;
    int i = 0;
    
    // Skip whitespace
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    
    // Handle sign
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    
    // Parse integer part
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }
    
    // Parse decimal part
    if (str[i] == '.')
    {
        i++;
        while (str[i] >= '0' && str[i] <= '9')
        {
            fraction = fraction * 10.0 + (str[i] - '0');
            decimal_places++;
            i++;
        }
    }
    
    // Combine integer and fractional parts
    while (decimal_places > 0)
    {
        fraction /= 10.0;
        decimal_places--;
    }
    
    return sign * (result + fraction);
}

// Custom strcmp implementation
int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

// Custom tokenization without strtok (which modifies the string)
int ft_tokenize_line(char *line, char **tokens, int max_tokens)
{
    int count = 0;
    int i = 0;
    int start;
    
    while (line[i] && count < max_tokens)
    {
        // Skip whitespace and delimiters
        while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            i++;
        
        if (!line[i])
            break;
        
        start = i;
        
        // Find end of token
        while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            i++;
        
        // Null-terminate the token
        if (line[i])
        {
            line[i] = '\0';
            i++;
        }
        
        tokens[count] = &line[start];
        count++;
    }
    
    return count;
}

// Custom sscanf replacement for parsing vectors
int ft_parse_vector_values(const char *str, double *x, double *y, double *z)
{
    char temp[256];
    int i = 0, j = 0, field = 0;
    double values[3] = {0, 0, 0};
    
    // Copy string to temp buffer
    while (str[i] && i < 255)
    {
        temp[i] = str[i];
        i++;
    }
    temp[i] = '\0';
    
    i = 0;
    while (temp[i] && field < 3)
    {
        j = 0;
        char number[64];
        
        // Skip to next number
        while (temp[i] && (temp[i] < '0' || temp[i] > '9') && temp[i] != '-' && temp[i] != '.')
            i++;
        
        // Extract number
        while (temp[i] && ((temp[i] >= '0' && temp[i] <= '9') || temp[i] == '.' || temp[i] == '-') && j < 63)
        {
            number[j] = temp[i];
            i++;
            j++;
        }
        number[j] = '\0';
        
        if (j > 0)
        {
            values[field] = ft_atof(number);
            field++;
        }
    }
    
    *x = values[0];
    *y = values[1];
    *z = values[2];
    
    return field;
}

// Custom sscanf replacement for parsing colors (integers)
int ft_parse_color_values(const char *str, int *r, int *g, int *b)
{
    char temp[256];
    int i = 0, j = 0, field = 0;
    int values[3] = {0, 0, 0};
    
    // Copy string to temp buffer
    while (str[i] && i < 255)
    {
        temp[i] = str[i];
        i++;
    }
    temp[i] = '\0';
    
    i = 0;
    while (temp[i] && field < 3)
    {
        j = 0;
        char number[64];
        
        // Skip to next number
        while (temp[i] && (temp[i] < '0' || temp[i] > '9'))
            i++;
        
        // Extract number
        while (temp[i] && temp[i] >= '0' && temp[i] <= '9' && j < 63)
        {
            number[j] = temp[i];
            i++;
            j++;
        }
        number[j] = '\0';
        
        if (j > 0)
        {
            // Simple atoi replacement
            int num = 0;
            int k = 0;
            while (number[k])
            {
                num = num * 10 + (number[k] - '0');
                k++;
            }
            values[field] = num;
            field++;
        }
    }
    
    *r = values[0];
    *g = values[1];
    *b = values[2];
    
    return field;
}
