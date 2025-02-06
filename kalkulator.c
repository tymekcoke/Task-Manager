#include <stdio.h>
#include <math.h>

double calc_delta(double a, double b, double c){
    /*Funkcja obliczająca deltę*/
    
    double wynik;

    wynik = (b*b) - (4*(a*c));


    return wynik;

}

double calc_deltasqrt(double a, double b, double c) {
    /*Funkcja obliczająca pierwiastek z delty*/
    
    double wynik;

    wynik = sqrt(calc_delta(a, b, c));

    if (wynik < 0) {
        return NAN;  
    }


    return wynik;
}

double calc_x1(double a, double b, double c) {
    /*Funkcja obliczająca 1-wsze miejsce zerowe*/
    
    double sqrt_delta = calc_deltasqrt(a, b, c);
    double x1 = (-b - sqrt_delta) / (2 * a);  
    
    if (isnan(sqrt_delta)) { 
        printf("    Równanie nie ma rozwiązań rzeczywistych (delta < 0).\n");
        double z1 = (-b - sqrt_delta) / (2 * a);  
        return NAN;
    }
    
    printf("    x1 wynosi: %lf\n", x1);
    
    return x1; 
}

double calc_x2(double a, double b, double c) {
    /*Funkcja obliczająca 1-wsze miejsce zerowe*/
    
    double sqrt_delta = calc_deltasqrt(a, b, c);
    double x2 = (-b + sqrt_delta) / (2 * a); 

    if (isnan(sqrt_delta)) { 
        printf("    Równanie nie ma rozwiązań rzeczywistych (delta < 0).\n");
        return NAN;
    } 
    
    printf("    x2 wynosi: %lf\n", x2);
    
    return x2; 
}

double calc_p(double a, double b, double c) {
    /*Funkcja obliczająca p*/
    
    double p = -(b / (2 * a));

    if (p == 0){
        p = 0;
    }

    printf("    p wynosi: %lf\n", p);
    
    return p; 
}

double calc_q(double a, double b, double c) {
    /*Funkcja obliczająca q*/
    
    double delta = calc_delta(a, b, c);
    double q = -(delta / (4 * a));

    if (q == 0){
        q = 0;
    }

    printf("    q wynosi: %lf\n", q);
    
    return q; 
}

double monotonicznosc(double a, double b, double c) {
    /*Funkcja analizująca monotoniczność*/
    
    
    double tab[2];
    double wspolczynnik;
    double p = calc_p(a, b, c);
    
    printf("\nMonotoniczność\n");


    if (a > 0){

        wspolczynnik = 1;
        printf("    Wspołczynnik jest > 0 (a > 0).\n");

    } else if (a == 0){
        
        printf("    Wspołczynnik a wynosi 0 (a == 0).\n");
        return NAN;

    } else {
        
        printf("    Wspołczynnik jest < 0 (a < 0).\n");
        wspolczynnik = 0;
    }
    

    if (wspolczynnik == 1){
        
        printf("    Ramiona funkcji są skierowane w górę\n");
        printf("    Funkcja maleje w przedziale od x = (-∞ , %lf)\n", p);
        printf("    Funkcja rośnie w przedziale od x = (%lf , ∞)\n", p);

    } else if (wspolczynnik == 0){

        printf("    Ramiona funkcji są skierowane w dół\n");
        printf("    Funkcja rośnie w przedziale od x = (-∞ , %lf)\n", p);
        printf("    Funkcja maleje w przedziale od x = (%lf , ∞)\n", p);

    }
    
    
    return 0;
}

int is_irrational_sqrt(double n) {
    double root = sqrt(n);
    int int_root = (int)root;

    if (root == int_root) {
        printf("Pierwiastek z jest wymierny");
        return 0;
    } else {
        printf("Pierwiastek z jest niewymierny");   
        return 1;
    }
}

int main() {
    /*Kalkulator funkcji kwadratowych*/
    
    double a, b ,c ,sqrt_delta;
    printf("Kalkulator funkcji (póki co prostych kwadratowych)!\n\n");

    a = 6; b = 8; c = 26;
    
    printf("a = %lf b = %lf c = %lf\n\n", a , b , c);

    calc_delta(a, b, c);
    printf("\nMiejsca zerowe\n");
    calc_x1(a, b, c);
    calc_x2(a, b, c);
    printf("\nWierzcholek\n");
    calc_p(a, b, c);
    calc_q(a, b, c);
    monotonicznosc(a, b, c);

    is_irrational_sqrt(169);
}