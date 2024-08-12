/*
 * 1.一张1000*1000的白色图片，任意输入三个点的坐标(x1,y1),(x2,y2),(x3,y3)，将三个点组成的三角形涂成黑色。注：白色用0表示，黑色用1表示。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1001
#define MAX_WIDTH 1001
#define POINT_NUM 3

#define MIN(x1, x2) ((x1) < (x2) ? (x1) : (x2))
#define MAX(x1, x2) ((x1) > (x2) ? (x1) : (x2))

#define GET_COORDINATE_VALUES(xPoint, yPoint, x1, y1, x2, y2, x3, y3) \
    do                                                                \
    {                                                                 \
        x1 = xPoint[0];                                               \
        y1 = yPoint[0];                                               \
        x2 = xPoint[1];                                               \
        y2 = yPoint[1];                                               \
        x3 = xPoint[2];                                               \
        y3 = yPoint[2];                                               \
    } while (0)

static int Global_Picture[MAX_LENGTH][MAX_WIDTH];
static const char *IMG_DIR = "img/";
static char *DEFAULT_IMG_FILENAME = "pic.txt";

/**
 * Function declaration
 */
int isCoordinateOutOfRange(const int x, const int y);
int isTriangle(int *xPoint, int *yPoint);

void initPicture();
void printPicture();
void drawTriangle(int *xPoint, int *yPoint, int num);

void displayDrawTrianglePage();
void showMenu();

char *concatenateStrings(const char *str1, const char *str2);
void saveToTxt(const char *filename);

/**
 * Check if the specified coordinate point(x,y) is out of range
 */
int isCoordinateOutOfRange(const int x, const int y)
{
    return (x < 0 || x > MAX_LENGTH || y < 0 || y > MAX_WIDTH);
}

/**
 * Check that the three coordinate points form a triangle
 */
int isTriangle(int *xPoint, int *yPoint)
{
    int x1, x2, x3, y1, y2, y3;
    int crossProduct;
    GET_COORDINATE_VALUES(xPoint, yPoint, x1, y1, x2, y2, x3, y3);

    crossProduct = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    return !(crossProduct == 0);
}

void initPicture()
{
    memset(Global_Picture, 0, sizeof(Global_Picture));
}

void printPicture()
{
    for (int y = MAX_WIDTH - 1; y >= 0; y--)
    {
        for (int x = 0; x < MAX_LENGTH; x++)
        {
            printf("%d", Global_Picture[x][y]);
        }
        printf("\n");
    }
}

void drawTriangle(int *xPoint, int *yPoint, int num)
{
    int minX, minY;
    int maxX, maxY;
    int i, j;
    int crossProduct1, crossProduct2, crossProduct3;
    int x1, x2, x3, y1, y2, y3;

    GET_COORDINATE_VALUES(xPoint, yPoint, x1, y1, x2, y2, x3, y3);

    minX = MIN(MIN(x1, x2), x3);
    minY = MIN(MIN(y1, y2), y3);
    maxX = MAX(MAX(x1, x2), x3);
    maxY = MAX(MAX(y1, y2), y3);

    for (j = minY; j <= maxY; ++j)
    {
        for (i = minX; i <= maxX; ++i)
        {
            crossProduct1 = (x2 - x1) * (j - y1) - (y2 - y1) * (i - x1);
            crossProduct2 = (x3 - x2) * (j - y2) - (y3 - y2) * (i - x2);
            crossProduct3 = (x1 - x3) * (j - y3) - (y1 - y3) * (i - x3);

            if ((crossProduct1 >= 0 && crossProduct2 >= 0 && crossProduct3 >= 0) || (crossProduct1 <= 0 && crossProduct2 <= 0 && crossProduct3 <= 0))
            {
                Global_Picture[i][j] = 1;
            }
        }
    }
}

/**
 * Concatenate two strings into a new string.
 */
char *concatenateStrings(const char *str1, const char *str2)
{
    size_t totalLen = strlen(str1) + strlen(str2) + 1;

    char *newStr = (char *)malloc(totalLen * sizeof(char));
    if (newStr == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    strcpy(newStr, str1);
    strcat(newStr, str2);
    return newStr;
}

/**
 * Save the generated image to the specified file
 */
void saveToTxt(const char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Failure to open file: %s.\n", filename);
        exit(1);
    }

    for (int y = MAX_WIDTH - 1; y >= 0; y--)
    {
        for (int x = 0; x < MAX_LENGTH; x++)
        {
            fprintf(fp, "%d ", Global_Picture[x][y]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Successfully written to file: %s\n", filename);
}

void flushInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void displayDrawTrianglePage()
{
    int i;
    int xPoint[POINT_NUM]; // Stores the horizontal coordinates of the three coordinate points
    int yPoint[POINT_NUM]; // Stores the vertical coordinates of the three coordinate points

    printf("\n\n================请依次输入三个点的坐标（以左下角为坐标原点构图）================\n");
    i = 0;
    while (1)
    {
        flushInputBuffer();
        if (i == 3)
        {
            // Checks that the three points fulfil the conditions for forming a triangle
            if (!isTriangle(xPoint, yPoint))
            {
                fprintf(stderr, "输入的三个点不能组成三角形！\n");
                break;
            }
            initPicture();
            drawTriangle(xPoint, yPoint, POINT_NUM);
            printPicture();
            char *fileName = concatenateStrings(IMG_DIR, DEFAULT_IMG_FILENAME);
            saveToTxt(fileName);
            free(fileName);
            break;
        }
        printf("请输入第%d个点的坐标(横纵坐标之间用单个空格分隔):", i + 1);
        if (scanf("%d %d", &xPoint[i], &yPoint[i]) != 2)
        {
            printf("输入格式有误，请重新输入！\n");

            continue;
        };
        if (isCoordinateOutOfRange(xPoint[i], yPoint[i]))
        {
            printf("坐标值有误，横纵坐标的范围（0~1000），请重新输入！\n");
            continue;
        }
        ++i;
    }
}

/**
 * Show menu items.
 */
void showMenu()
{
    char op[2];

    while (1)
    {
        printf("\n==========================请选择您的操作=======================\n");
        printf("================1、通过三点坐标画三角形(请输入1)================\n");
        printf("================2、退出程序(请输入q)===========================\n");
        printf("请输入您的操作：");
        scanf("%s", op);
        if (strlen(op) > 1)
        {
            printf("===================输入有误，请重新输入！=================\n\n");
            continue;
        }
        switch (op[0])
        {
        case '1':
            displayDrawTrianglePage();
            break;
        case 'q':
            printf("成功退出程序！\n");
            exit(0);
        default:
            printf("\n===================输入有误，请重新输入！=================\n\n");
            break;
        }
    }
}

int main(int args, char **argv)
{
    if (args == 2)
    {
        DEFAULT_IMG_FILENAME = argv[1];
    }
    showMenu();
    return 0;
}