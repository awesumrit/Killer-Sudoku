
/*
Program: Killer Sudoku Solver
Created by: Moein Owhadi Kareshk
Description: This Program reads from 'input.txt' and writes on 'output.txt'
*/

/*!  Name Spaces  !*/
using namespace std;

/*!  Header Files  !*/
#include<fstream>
#include<iostream>
#include<dos.h>
#include<time.h>
#include<stdlib.h>

/*!  Function Prototypes  !*/
void input();
bool IsRowOk(int i,int j);
bool IsColOk(int i,int j);
bool IsKillerOk(int i,int j);
void AnotherCapacity(int,int);
void SudokuSolver(int,int);
void PrintSudoku();

/*!  Global Varible  !*/
int N=5;
int Sudoku_T[10][10];
bool flag [10][10];
unsigned int counter=0;
char Operator;
ifstream inputFile("input.txt");
struct Block
{
    int x[80],y[80],maxX,maxY,value,pointNum;
};
Block block[100];
int blockNum;
time_t t1,t2;

/*!  Main  !*/
int main()
{
    t1=time(0);
    input();
    for(int i=1; i<N; i++)
    {
        for(int j=1; j<N; j++)
        {
            flag[i][j]=0;
            Sudoku_T[i][j]=0;
        }
        SudokuSolver(1,1);
    }
    cout<<"Could not find the solution."<<endl;
}

/*!  Print  !*/
void PrintSudoku()
{
    ofstream outputFile("output.txt",ios::app);
    for(int i=1; i<N; i++)
    {
        for(int j=1; j<N; j++)
        {
            outputFile<<Sudoku_T[i][j];
            if(j!=N-1)
            {
                outputFile<<"-";
            }
        }
        outputFile<<endl;
    }
    outputFile<<endl;
    t2=time(0);
    cout<<"Execution Time: "<<t2-t1<<endl;
    exit(0);
}

/*!  Solver  !*/
void SudokuSolver(int i,int j)
{
    counter++;
    int temp_a,temp_b;
    if(flag[i][j]==0)
    {
        for(int c=1; c<N; c++)
        {
            Sudoku_T[i][j]=c;
            if(IsRowOk(i,j) && IsColOk(i,j))
            {
                if(IsKillerOk(i,j))
                {
                    AnotherCapacity(i,j);
                }
            }
            for(temp_b=j+1; temp_b<N; temp_b++)
            {
                if(flag[i][temp_b]==0)
                {
                    Sudoku_T[i][temp_b]=0;
                }
            }
            for(temp_a=i+1; temp_a<N; temp_a++)
            {
                for(temp_b=0; temp_b<N; temp_b++)
                {
                    if(flag[temp_a][temp_b]==0)
                    {
                        Sudoku_T[temp_a][temp_b]=0;
                    }
                }
            }

        }
    }
    else AnotherCapacity(i,j);
}


void AnotherCapacity(int i,int j)
{
    j++;
    if(j>=N)
    {
        j=1;
        i++;
    }
    if(i>=N)
    {
        PrintSudoku();
    }
    else
    {
        SudokuSolver(i,j);
    }
}

/*!  Checkers  !*/
bool IsRowOk(int i,int j)
{
    for(int c=1; c<=9; c++)
    {
        if(Sudoku_T[i][c]==Sudoku_T[i][j] && c!=j)
        {
            return false;
        }
    }
    return true;
}
bool IsColOk(int i,int j)
{
    for(int c=1; c<=9; c++)
    {
        if(Sudoku_T[c][j]==Sudoku_T[i][j] && c!=i)
        {
            return false;
        }
    }
    return true;
}

bool IsKillerOk(int ii,int jj)
{
    int r1=0,r2=1;
    for(int i=0; i<blockNum; i++)
    {
        if(ii>block[i].maxX && jj>block[i].maxY)
        {
            r1=0;
            r2=1;
            for(int j=0; j<block[i].pointNum; j++)
            {
                if(Operator=='+')
                {
                    r1+=Sudoku_T[block[i].x[j]][block[i].y[j]];
                }
                if(Operator=='-')
                {
                    r1-=Sudoku_T[block[i].x[j]][block[i].y[j]];
                }
                if(Operator=='*')
                {
                    r2*=Sudoku_T[block[i].x[j]][block[i].y[j]];
                }
                if(Operator=='/')
                {
                    r2/=Sudoku_T[block[i].x[j]][block[i].y[j]];
                }
            }
            if((r1!=block[i].value&& (Operator=='+' || Operator=='-')) ||  (r2!=block[i].value&& (Operator=='*' || Operator=='/')) )
            {
                return false;
            }
        }

    }
    return true;
}

void input()
{

    int temp;
    inputFile>>Operator;
    inputFile>>N;
    N++;
    inputFile>>blockNum;
    for(int i=0; i<blockNum; i++)
    {
        inputFile>>block[i].pointNum;
        for(int j=0; j<block[i].pointNum; j++)
        {
            inputFile>>block[i].x[j];

            inputFile>>block[i].y[j];
        }
        inputFile>>block[i].value;
    }
    for(int i=0; i<blockNum; i++)
    {
        block[i].maxX=0;
        block[i].maxY=0;
        for(int j=0; j<block[i].pointNum; j++)
        {
            if(block[i].x[j]>=block[i].maxX)
            {
                block[i].maxX= block[i].x[j];

            }
            if(block[i].y[j]>=block[i].maxY)
            {
                block[i].maxY= block[i].y[j];
            }
        }
    }
}
