
#include <stdio.h>
#include <stdlib.h>

double computeCircle(double radius)
{
    return 3.141593 * radius * radius;
}

double computeTriangle(double side)
{
    return 0.433013 * side * side;
}

double computeSquare(double side)
{
    return side * side;
}

double computePentagon(double side)
{
    return 1.720477 * side * side;
}

double computeHexagon(double side)
{
    return 2.598076 * side * side;
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc < 2)
        printf("usage PA1 <double>\n");

    // Assign parameters passed in to variables 
    double circleRadius = atof(argv[1]);
    double triangleSide = atof(argv[2]);
    double squareSide = atof(argv[3]);
    double pentagonSide = atof(argv[4]);
    double hexagonSide = atof(argv[5]);

    // Print areas by calling methods in print statement
    printf("CIRCLE, radius = %.5f, area = %.5f.\n", circleRadius, computeCircle(circleRadius));
    printf("TRIANGLE, length = %.5f, area = %.5f.\n", triangleSide, computeTriangle(triangleSide));
    printf("SQUARE, length = %.5f, area = %.5f.\n", squareSide, computeSquare(squareSide));
    printf("PENTAGON, length = %.5f, area = %.5f.\n", pentagonSide, computePentagon(pentagonSide));
    printf("HEXAGON, length = %.5f, area = %.5f.\n", hexagonSide, computeHexagon(hexagonSide));

    return 0;
}
    
