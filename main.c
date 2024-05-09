#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <conio.h>
#define maxNameOfProduct 20
#define maxNameOfCategory 20
#define maxNumOfProductsPerCategory 20
#define maxNumOfCategorysInMarket 20
typedef struct product product;
typedef struct category category;
typedef struct market market;

struct product
{
    char productName[maxNameOfProduct];
    int productQuantity;
    float productPrice;

};



struct category
{
    char categoryName[maxNameOfCategory];
    product products[maxNumOfProductsPerCategory];
    int productCount;
};

struct market
{
    category categories[maxNumOfCategorysInMarket];
    int categoryCount;
};

void initialMarket(market *market)
{
    market->categoryCount=2;

    for(int i=0; i<2; i++)
    {
        market->categories[i].productCount=2;
    }


    strcpy(market->categories[0].categoryName,"fruits");
    strcpy(market->categories[1].categoryName,"vegetables");

    strcpy(market->categories[0].products[0].productName,"apples");
    market->categories[0].products[0].productPrice=15;
    market->categories[0].products[0].productQuantity=15;

    strcpy(market->categories[0].products[1].productName,"orange");
    market->categories[0].products[1].productPrice=15;
    market->categories[0].products[1].productQuantity=10;


    strcpy(market->categories[1].products[0].productName,"tomatos");
    market->categories[1].products[0].productPrice=6;
    market->categories[1].products[0].productQuantity=10;

    strcpy(market->categories[1].products[1].productName,"botatos");
    market->categories[1].products[1].productPrice=5;
    market->categories[1].products[1].productQuantity=20;

}

void displayMarket(market *market)
{
    if(market->categoryCount!=0)
    {
        for(int i=0; i<market->categoryCount; i++)
        {
            printf("\n\n");
            SetColor(11);
            printf("(%d) Category Name : %s \n",i+1,market->categories[i].categoryName);
            SetColor(15);
            for(int j=0; j<market->categories[i].productCount; j++)
            {
                printf("    (%d) product Name : %s  | product Quantity : %d  | one product price : %.2f  | product Total price : %.2f\n"
                       ,j+1,market->categories[i].products[j].productName,
                       market->categories[i].products[j].productQuantity,
                       market->categories[i].products[j].productPrice,
                       market->categories[i].products[j].productQuantity *(market->categories[i].products[j].productPrice ));
            }
        }
    }
    else
    {
        SetColor(12);

        printf("Error:  there is no data to display please add data and display it \n");
        SetColor(15);
    }

}

void addCategory(market *market)
{

    char c;
    do
    {

        if (market->categoryCount < maxNumOfCategorysInMarket)
        {
            char cName[20];

            while (1)
            {
                SetColor(11);
                printf("please Enter name of category that you want to add : ");
                SetColor(15);
                scanf(" %[^\n]s", cName);
                trimSpaces(cName);

                int findIndex = -1;
                for (int i = 0; i < market->categoryCount; i++)
                {
                    if (strcmp(market->categories[i].categoryName, cName) == 0)
                    {
                        findIndex = i;
                        break;
                    }
                }

                if (findIndex != -1)
                {
                    SetColor(12);
                    printf("Error: This category already exists. Please enter a new category.\n");
                    SetColor(15);
                    printf("do you want to enter another category name Y|N \n ");
                    char key=getch();
                    if(key=='n'||key=='N')
                    {
                        return;
                    }
                }
                else
                {
                    strcpy(market->categories[market->categoryCount].categoryName, cName);
                    market->categories[market->categoryCount].productCount = 0;
                    market->categoryCount++;
                    SetColor(10);
                    printf("Category \"%s\" added successfully.\n",cName);
                    SetColor(15);
                    break;
                }
            }
        }
        else
        {
            SetColor(12);
            printf("Error: You cannot add more categories.\n");
            SetColor(15);
        }

        printf("\n\n");
        printf("Do you want to add another category in the Market? (Y|N)  \n");
        printf("\n");
        c = getch();


    }
    while (c == 'y' || c == 'Y');
}


void removeCategory(market *market)
{
    char c;
    do
    {

        if(market->categoryCount>0)
        {

            char catName[20];
            while(1)
            {
                SetColor(11);
                printf("Enter name of category that you want to remove it : ");
                SetColor(15);
                scanf(" %[^\n]s", catName);
                trimSpaces(catName);

                int findIndex=-1;
                for(int i=0; i<market->categoryCount; i++)
                {
                    if(strcmp(market->categories[i].categoryName,catName)==0)
                    {
                        findIndex=i;
                        break;
                    }

                }

                if(findIndex!=-1)
                {
                    for(int i=findIndex; i<market->categoryCount-1; i++)
                    {
                        market->categories[i]=market->categories[i+1];
                    }

                    market->categoryCount--;
                    SetColor(10);
                    printf("Category \"%s\" removed successfully.\n",catName);
                    SetColor(11);
                    break;
                }
                else
                {
                    SetColor(12);
                    printf("Error : this category not found \n");
                    SetColor(11);

                    printf("do you want to enter another category name Y|N \n ");
                    char key=getch();
                    if(key=='n'||key=='N')
                    {
                        return;
                    }
                }
            }


        }
        else
        {
            SetColor(12);
            printf("Error: there is no categories \n");
            SetColor(15);
        }

        printf("\n\n");
        printf("Do you want to remove another category from the Market? (Y|N)  \n");
        printf("\n");
        c = getch();
    }
    while(c=='y'||c=='Y');

}

void addProduct(market *market)
{
    char c;
    do
    {
        char pName[maxNameOfProduct],cName[maxNameOfCategory];
        float price;
        int quantity;
        int findIndexOfCategory=-1;

        SetColor(11);
        printf("please Enter Product Name : ");
        SetColor(15);
        scanf(" %[^\n]s", pName);
        trimSpaces(pName);

        while(1)
        {
            SetColor(11);
            printf("please Enter Category Name That you want to add Product on it : ");
            SetColor(15);
            scanf(" %[^\n]s", cName);
            trimSpaces(cName);

            for(int i=0; i<market->categoryCount; i++)
            {
                if( strcmp(market->categories[i].categoryName,cName)==0)
                {
                    findIndexOfCategory=i;
                    break;
                }
            }

            if (findIndexOfCategory != -1)
            {
                break;
            }

            else
            {
                SetColor(12);
                printf("Error : this category not found please try to enter correct Category Name\n");
                SetColor(15);

                printf("do you want to enter another category name Y|N \n ");
                char key=getch();
                if(key=='n'||key=='N')
                {
                    return;
                }
            }

        }

        if(market->categories[findIndexOfCategory].productCount<maxNumOfProductsPerCategory)
        {
            strcpy(market->categories[findIndexOfCategory].products[market->categories[findIndexOfCategory].productCount].productName,pName);

            int productIndex=-1;

            for(int i=0; i<market->categories[findIndexOfCategory].productCount; i++)
            {
                if(strcmp(market->categories[findIndexOfCategory].products[i].productName,pName)==0)
                {
                    productIndex=i;
                    break;
                }
            }

            if(productIndex!=-1)
            {
                char c ;
                do
                {
                    SetColor(14);
                    printf("Warning : this product was found please do you want to edit in its Quantity and price ? Y|N : ");
                    SetColor(15);
                    c = getch();
                    if(c=='n'||c=='N')
                        break;

                    SetColor(11);
                    printf("\n please Enter Additional Quantity for this product : ");
                    SetColor(15);

                    do
                    {
                        if (scanf("%d", &quantity) == 1 && quantity > 0)
                        {
                            break;
                        }
                        else
                        {
                            SetColor(12);
                            printf("Error: Please enter a valid positive quantity.\n");
                            SetColor(15);

                            while (getchar() != '\n');
                        }
                    }
                    while (1);

                    market->categories[findIndexOfCategory].products[productIndex].productQuantity+=quantity;
                    SetColor(11);
                    printf("please Enter New Price for this product Note : (old price for one is %.2f) : ",market->categories[findIndexOfCategory].products[productIndex].productPrice);
                    SetColor(15);
                    do
                    {
                        if (scanf("%f", &price) == 1 && price > 0)
                        {
                            break;
                        }
                        else
                        {
                            SetColor(12);
                            printf("Error: Please enter a valid positive price.\n");
                            SetColor(15);

                            while (getchar() != '\n');
                        }
                    }
                    while (1);

                    market->categories[findIndexOfCategory].products[productIndex].productPrice=price;

                    SetColor(10);
                    printf("you Edited this product successfully \n");
                    SetColor(15);


                }
                while(c=='n'||c=='N');

            }
            else
            {

                SetColor(11);
                printf("please Enter quantity of this product : ");
                SetColor(15);
                do
                {
                    if (scanf("%d", &quantity) == 1 && quantity > 0)
                    {
                        break;
                    }
                    else
                    {
                        SetColor(12);
                        printf("Error: Please enter a valid positive quantity.\n");
                        SetColor(15);

                        while (getchar() != '\n');
                    }
                }
                while (1);
                market->categories[findIndexOfCategory].products[market->categories[findIndexOfCategory].productCount].productQuantity=quantity;
                SetColor(11);
                printf("please Enter price of one product : ");
                SetColor(15);
                do
                {
                    if (scanf("%f", &price) == 1 && price > 0)
                    {
                        break;
                    }
                    else
                    {
                        SetColor(12);
                        printf("Error: Please enter a valid positive price.\n");
                        SetColor(15);

                        while (getchar() != '\n');
                    }
                }
                while (1);

                market->categories[findIndexOfCategory].products[market->categories[findIndexOfCategory].productCount].productPrice=price;

                market->categories[findIndexOfCategory].productCount++;
                SetColor(10);
                printf("you added %s in %s Successfully",pName,cName);
                SetColor(15);

            }

        }

        printf("\n\n");
        printf("Do you want to add another product ? (Y|N)  \n");
        printf("\n");
        c = getch();

    }
    while(c=='y'||c=='Y');

}

void trimSpaces(char *str)
{
    int start = 0, end;


    while (isspace((unsigned char)str[start]))
        start++;
    end = strlen(str) - 1;
    while (end > start && isspace((unsigned char)str[end]))
        end--;


    memmove(str, str + start, end - start + 1);


    str[end - start + 1] = '\0';
}

void removeProduct(market *market)
{
    char c;
    do
    {
        char pName[maxNameOfProduct],cName[maxNameOfCategory];
        int categoryIndex=-1;
        while (1)
        {
            SetColor(11);
            printf("please Enter Category Name That you want to delete Product from it : ");
            SetColor(15);
            scanf(" %[^\n]s", cName);
            trimSpaces(cName);

            for (int i = 0; i < market->categoryCount; i++)
            {
                if (strcmp(market->categories[i].categoryName, cName) == 0)
                {
                    categoryIndex = i;
                    break;
                }
            }

            if (categoryIndex != -1)
            {
                break;
            }
            else
            {
                SetColor(12);
                printf("Error: This category does not exist. Please enter a valid category name.\n");
                SetColor(15);

                printf("do you want to enter another category name Y|N \n ");
                char key=getch();
                if(key=='n'||key=='N')
                {
                    return;
                }
            }
        }


        int productIndex=-1;
        if(categoryIndex!=-1)
        {
            while(1)
            {
                SetColor(11);
                printf("please Enter Product Name to delete it: ");
                SetColor(15);
                scanf(" %[^\n]s", pName);
                trimSpaces(pName);


                SetColor(11);
                for(int i=0; i<market->categories[categoryIndex].productCount; i++)
                {
                    if(strcmp(market->categories[categoryIndex].products[i].productName,pName)==0)
                    {
                        productIndex=i;
                        break;
                    }
                }

                if(productIndex!=-1)
                {
                    for(int i=productIndex; i<market->categories[categoryIndex].productCount-1; i++)
                    {
                        market->categories[categoryIndex].products[i]=market->categories[categoryIndex].products[i+1];
                    }
                    market->categories[categoryIndex].productCount--;
                    SetColor(10);
                    printf("you removed %s from %s \n",pName,cName);
                    SetColor(15);
                    break;
                }
                else
                {
                    SetColor(12);
                    printf("Error %s not found in %s \n",pName,cName);
                    SetColor(15);

                    printf("do you want to enter another product name Y|N \n ");
                    char key=getch();
                    if(key=='n'||key=='N')
                    {
                        return;
                    }
                }

            }
        }


        printf("\n\n");
        printf("Do you want to remove another product ? (Y|N)  \n");
        printf("\n");
        c = getch();
    }
    while(c=='y'||c=='Y');

}


void sellProduct(market *market)
{
    int tprice=0;
    char c;
    do
    {
        char pName[maxNameOfProduct],cName[maxNameOfCategory];
        int price,quantity;
        int categoryIndex=-1;

        while(1)
        {
            SetColor(11);
            printf("please Enter Category Name That you want to sell Product from it : ");
            SetColor(15);
            scanf(" %[^\n]s", cName);
            trimSpaces(cName);


            for(int i=0; i<market->categoryCount; i++)
            {
                if(strcmp(market->categories[i].categoryName,cName)==0)
                {
                    categoryIndex=i;
                    break;
                }
            }

            if(categoryIndex!=-1)
            {
                break;
            }
            else
            {
                SetColor(12);
                printf("Error : this category %s not found please enter valid name : \n",cName);
                SetColor(15);
                printf("do you want to enter another cat name Y|N \n ");
                char key=getch();
                if(key=='n'||key=='N')
                {
                    return;
                }
            }
        }


        int productIndex=-1;
        if(categoryIndex!=-1)
        {

            while(1)
            {

                SetColor(11);
                printf("please Enter Product Name to sell it: ");
                SetColor(15);
                scanf(" %[^\n]s", pName);
                trimSpaces(pName);

                for(int i=0; i<market->categories[categoryIndex].productCount; i++)
                {
                    if(strcmp(market->categories[categoryIndex].products[i].productName,pName)==0)
                    {
                        productIndex=i;
                        break;
                    }
                }

                if(productIndex!=-1)
                {
                    break;
                }
                else
                {
                    SetColor(12);
                    printf("Error : this product %s not found in %s please enter valid name \n",pName,cName);
                    SetColor(15);

                    printf("do you want to enter another product name Y|N \n ");
                    char key=getch();
                    if(key=='n'||key=='N')
                    {
                        return;
                    }
                }


            }

            if(market->categories[categoryIndex].products[productIndex].productQuantity>0)
            {


                SetColor(11);
                printf("please Enter quantity of this product : ");
                SetColor(15);
                do
                {
                    if (scanf("%d", &quantity) == 1 && quantity > 0)
                    {
                        break;
                    }
                    else
                    {
                        SetColor(12);
                        printf("Error: Please enter a valid positive quantity.\n");
                        SetColor(15);

                        while (getchar() != '\n');
                    }
                }
                while (1);

                if(quantity <= market->categories[categoryIndex].products[productIndex].productQuantity)
                {
                    market->categories[categoryIndex].products[productIndex].productQuantity-=quantity;
                    SetColor(10);
                    printf("you soled %s with quantity %d and its total price is %.2f",pName,quantity,quantity*market->categories[categoryIndex].products[productIndex].productPrice);
                    SetColor(15);
                    tprice+=quantity*market->categories[categoryIndex].products[productIndex].productPrice;
                }
                else
                {

                    while(quantity> market->categories[categoryIndex].products[productIndex].productQuantity)
                    {
                        SetColor(12);
                        printf("Error : there is just %d quantity for %s please enter right quantity :",market->categories[categoryIndex].products[productIndex].productQuantity,market->categories[categoryIndex].products[productIndex].productName);
                        SetColor(15);
                        scanf("%d",&quantity);

                    }
                    market->categories[categoryIndex].products[productIndex].productQuantity-=quantity;
                    SetColor(10);
                    printf("you soled %s with quantity %d and its total price is %.2f",pName,quantity,quantity*market->categories[categoryIndex].products[productIndex].productPrice);
                    SetColor(15);
                                        tprice+=quantity*market->categories[categoryIndex].products[productIndex].productPrice;



                }

            }
            else
            {
                printf("this product found but there is no quantity now \n");
            }
        }

        SetColor(10);
         printf("\n\ntotal price for orders :%d  \n",tprice);
         SetColor(15);

        printf("\n\n");
        printf("Do you want to sell another product ? (Y|N)  \n");
        printf("\n");
        c = getch();
    }
    while(c=='y'||c=='Y');
}

void moveProduct(market *market)
{
    char c;
    do
    {
        if (market->categoryCount > 1)
        {
            char proName[maxNameOfProduct], sourceCatName[maxNameOfCategory], destinationCatName[maxNameOfCategory];

            int sourceCatIndex = -1;
            while (1)
            {
                SetColor(11);
                printf("Please Enter source category name that you want to move product from it: ");
                SetColor(15);
                scanf(" %[^\n]s", sourceCatName);
                trimSpaces(sourceCatName);

                for (int i = 0; i < market->categoryCount; i++)
                {
                    if (strcmp(market->categories[i].categoryName, sourceCatName) == 0)
                    {
                        sourceCatIndex = i;
                        break;
                    }
                }

                if (sourceCatIndex != -1)
                {
                    break;
                }
                else
                {
                    SetColor(12);
                    printf("Error: The source category \"%s\" was not found. Please enter a valid source name.\n", sourceCatName);
                    SetColor(15);
                    printf("Do you want to enter another source cat name? (Y|N)\n");
                    char key = getch();
                    if (key == 'n' || key == 'N')
                    {
                        return;
                    }
                }
            }

            int productIndex = -1;
            int destinationCatIndex = -1;
            while (1)
            {
                if (sourceCatIndex != -1)
                {
                    if (market->categories[sourceCatIndex].productCount == 0)
                    {
                        SetColor(12);
                        printf("Error: There is no product in the source category. Press any key to exit.\n");
                        SetColor(15);

                        getch();
                        return;
                    }

                    SetColor(11);
                    printf("Please Enter product name that you want to move: ");
                    SetColor(15);
                    scanf(" %[^\n]s", proName);
                    trimSpaces(proName);

                    for (int i = 0; i < market->categories[sourceCatIndex].productCount; i++)
                    {
                        if (strcmp(market->categories[sourceCatIndex].products[i].productName, proName) == 0)
                        {
                            productIndex = i;
                            break;
                        }
                    }

                    if (productIndex != -1)
                    {
                        break;
                    }
                    else
                    {
                        SetColor(12);
                        printf("Error: This product \"%s\" was not found in \"%s\". Please enter a valid product name.\n", proName, sourceCatName);
                        SetColor(15);

                        printf("Do you want to enter another product name? (Y|N)\n");
                        char key = getch();
                        if (key == 'n' || key == 'N')
                        {
                            return;
                        }
                    }
                }
            }

            while (1)
            {
                SetColor(11);
                printf("Please enter destination category name that you want to move product in it: ");
                SetColor(15);
                scanf(" %[^\n]s", destinationCatName);
                trimSpaces(destinationCatName);


                for (int i = 0; i < market->categoryCount; i++)
                {
                    if (strcmp(market->categories[i].categoryName, destinationCatName) == 0)
                    {
                        destinationCatIndex = i;
                        break;
                    }
                }

                if (destinationCatIndex != -1)
                {
                    break;
                }
                else
                {
                    SetColor(12);
                    printf("Error: The destination category \"%s\" was not found. Please enter a valid destination name.\n", destinationCatName);
                    SetColor(15);
                    printf("Do you want to enter another destination cat name? (Y|N)\n");
                    char key = getch();
                    if (key == 'n' || key == 'N')
                    {
                        return;
                    }
                }
            }

            int destinationProductIndex = -1;
            if (destinationCatIndex != -1)
            {
                for (int i = 0; i < market->categories[destinationCatIndex].productCount; i++)
                {
                    if (strcmp(market->categories[destinationCatIndex].products[i].productName, proName) == 0)
                    {
                        destinationProductIndex = i;
                        break;
                    }
                }
            }

            if (destinationProductIndex == -1)
            {


                market->categories[destinationCatIndex].products[market->categories[destinationCatIndex].productCount] =
                    market->categories[sourceCatIndex].products[productIndex];
                market->categories[destinationCatIndex].productCount++;

                for (int i = productIndex; i < market->categories[sourceCatIndex].productCount - 1; i++)
                {
                    market->categories[sourceCatIndex].products[i] = market->categories[sourceCatIndex].products[i + 1];
                }

                market->categories[sourceCatIndex].productCount--;
                SetColor(10);
                printf("You moved %s from %s to %s successfully.\n", proName, sourceCatName, destinationCatName);
                SetColor(15);
            }
            else
            {
                SetColor(14);
                printf("Warning: This product is already in the destination category. I moved it with just its quantity, but the price is the price of the product in the destination category.\n");
                SetColor(15);

                market->categories[destinationCatIndex].products[destinationProductIndex].productQuantity +=
                    market->categories[sourceCatIndex].products[productIndex].productQuantity;

                for (int i = productIndex; i < market->categories[sourceCatIndex].productCount - 1; i++)
                {
                    market->categories[sourceCatIndex].products[i] = market->categories[sourceCatIndex].products[i + 1];
                }

                market->categories[sourceCatIndex].productCount--;
                SetColor(10);
                printf("You moved %s from %s to %s successfully.\n", proName, sourceCatName, destinationCatName);
                SetColor(15);
            }
        }
        else
        {
            SetColor(12);
            printf("Error: Not enough categories to perform a product move.\n");
            SetColor(15);
        }

        printf("\nDo you want to move another product? (Y|N)\n");
        c = getch();
        printf("\n");
    }
    while (c == 'y' || c == 'Y');
}

COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
int main()
{
    market market;
    initialMarket(&market);

    int selectedOption = 0;

    char menu[10][60] =
    {
        "Display market Data",
        "Add Category",
        "Remove Category",
        "Add Product or Edit Product",
        "Remove Product",
        "Move Product to Another Category",
        "Sell",
        "Exit",
    };
    while (1)
    {
        system("cls");

        SetColor(11);
        printf("\n\t\t\t\t\t\t\" Mohammed Ali Market \"\n");

        SetColor(15);
        for (int i = 0; i < 8; i++)
        {

            gotoxy(45, 3 + i);

            if (selectedOption == i)
            {

                SetColor(11);
                printf("->>%s", menu[i]);

            }
            else
            {

                SetColor(15);
                printf("    %s", menu[i]);

            }
        }


        char key = _getch();

        switch (key)
        {
        case 72:

            if (selectedOption <= 0)
            {
                selectedOption = 7;
            }
            else
            {
                selectedOption--;
            }

            break;

        case 80:

            if (selectedOption >= 7)
            {
                selectedOption = 0;
            }
            else
            {
                selectedOption++;
            }

            break;

        case 13:
            switch (selectedOption)
            {
            case 0:
                system("cls");
                SetColor(11);
                printf("\n\n\n\t\t\t\t\t\" this is the menu that we have \" \n");
                SetColor(15);
                displayMarket(&market);
                _getch();
                system("cls");
                break;

            case 1:
                system("cls");
                SetColor(11);
                printf("\n\t\t\t\t\" this is the menu that we have {Add Category} \" \n");
                SetColor(15);
                displayMarket(&market);
                printf("\n\n");

                addCategory(&market);
                system("cls");
                break;

            case 2:

                system("cls");
                SetColor(11);
                printf("\n\t\t\t\t\" Select the category that you want to remove \"\n");
                SetColor(15);
                displayMarket(&market);
                printf("\n\n");
                removeCategory(&market);

                system("cls");
                break;

            case 3:
                system("cls");
                SetColor(11);
                printf("\n\t\t\t\t\" Select product name to edit or Enter new product \"\n");
                SetColor(15);
                displayMarket(&market);
                printf("\n\n");
                addProduct(&market);
                break;

            case 4:
                system("cls");
                SetColor(11);
                printf("\n\t\t\t\t\t\" Select product name to remove \"\n");
                SetColor(15);
                displayMarket(&market);
                printf("\n\n");
                removeProduct(&market);
                break;

            case 5:
                system("cls");
                system("cls");
                SetColor(11);
                printf("\n\t\t\t\t\" Select product name to move it to another categoty \"\n");
                SetColor(15);
                displayMarket(&market);
                printf("\n\n");
                moveProduct(&market);
                break;
            case 6:
                system("cls");
                SetColor(11);
                printf("\n\t\t\t\t\t\" Select product name to sell \"\n");
                SetColor(15);
                displayMarket(&market);
                printf("\n\n");
                sellProduct(&market);
                break;

            case 7:
                system("cls");
                return 0;
                break;
            }

            break;
        case 27:
            system("cls");
            return 0;
            break;



        }
    }

    return 0;
}
