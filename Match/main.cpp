#include <fstream>
#include <cmath>
#include <iostream>

int main()
{
    std::fstream fin("INPUT.txt");
    int numb;
    fin >> numb;
    fin.close();

    int result;
    float sqrt_numb = sqrt(numb);
    int sqrt_int = sqrt_numb;

    if (numb == 0)
        result = 0;
    else if ((sqrt_numb/(int)(sqrt_numb))==1)
        result = 2 * (sqrt_int + 1) * sqrt_int ;
    else
    {
        numb -= (pow(sqrt_int, 2));
        result = 2 * (sqrt_int + 1) * (sqrt_int) ;

        result +=3;
        --numb;
        while (numb > 0)
        {
            if (numb == sqrt_int)
                result += 3;
            else
                result += 2;
            --numb;
        }

    }

    std::ofstream out("OUTPUT.TXT");
    out << result << "\n";
    out.close();
    return 0;
}

