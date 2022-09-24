#include<bits/stdc++.h>
using namespace std;

float coordinate[100][2];
float xmax=0, xmin=0, ymax=50, ymin=35;
int node;
float afterclip[10][10];

void left_clipping()
{
    float temp[100][2];
    float x1,y1,x2,y2;
    int j = 0,i;
    for(i=0; i<node; i++)
    {
        x1=coordinate[i][0];
        y1=coordinate[i][1];
        x2=coordinate[i+1][0];
        y2=coordinate[i+1][1];
        if(x1>=xmin&&x2>=xmin)
        {
            //in-in
            temp[j][0] = x2;
            temp[j][1] = y2;
            j++;
        }
        else if(x1<xmin&&x2<xmin)
        {
            //out out do nothing
        }
        else if(x1>xmin&&x2<=xmin)
        {
            //in-out
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 1;
            float b2 = 0;
            float c2 = -xmin;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            j++;

        }
        else if(x1<xmin&&x2>=xmin)
        {
            //out-in
            int flag = 0;
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 1;
            float b2 = 0;
            float c2 = -xmin;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            if(temp[j][0] == x2 && temp[j][1]==y2)
            {
                flag = -1;
            }
            j++;
            if(flag==0)
            {
                temp[j][0] = x2;
                temp[j][1] = y2;
                j++;
            }

        }
    }
    for(i=0; i<j; i++)
    {
        coordinate[i][0]=temp[i][0];
        coordinate[i][1]=temp[i][1];
    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];
    node = j;

}
void right_clipping()
{
    float temp[100][2];
    float x1,y1,x2,y2;
    int j = 0,i;
    for(i=0; i<node; i++)
    {
        x1=coordinate[i][0];
        y1=coordinate[i][1];
        x2=coordinate[i+1][0];
        y2=coordinate[i+1][1];
        if(x1<=xmax&&x2<=xmax)
        {
            //in-in
            temp[j][0] = x2;
            temp[j][1] = y2;
            j++;
        }
        else if(x1>xmax&&x2>xmax)
        {
            //out out do nothing
        }
        else if(x1<xmax&&x2>=xmax)
        {
            //in-out
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 1;
            float b2 = 0;
            float c2 = -xmax;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            j++;

        }
        else if(x1>xmax&&x2<=xmax)
        {
            //out-in
            int flag = 0;
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 1;
            float b2 = 0;
            float c2 = -xmax;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            if(temp[j][0] == x2 && temp[j][1]==y2)
            {
                flag = -1;
            }
            j++;
            if(flag==0)
            {
                temp[j][0] = x2;
                temp[j][1] = y2;
                j++;
            }

        }
    }
    for(i=0; i<j; i++)
    {
        coordinate[i][0]=temp[i][0];
        coordinate[i][1]=temp[i][1];
    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];
    node = j;

}
void top_clipping()
{
    float temp[100][2];
    float x1,y1,x2,y2;
    int j = 0,i;
    for(i=0; i<node; i++)
    {
        x1=coordinate[i][0];
        y1=coordinate[i][1];
        x2=coordinate[i+1][0];
        y2=coordinate[i+1][1];
        if(y1<=ymax&&y2<=ymax)
        {
            //in-in
            temp[j][0] = x2;
            temp[j][1] = y2;
            j++;
        }
        else if(y1>ymax&&y2>ymax)
        {
            //out out do nothing
        }
        else if(y1<ymax&&y2>=ymax)
        {
            //in-out
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 0;
            float b2 = 1;
            float c2 = -ymax;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            j++;

        }
        else if(y1>ymax&&y2<=ymax)
        {
            //out-in
            int flag = 0;
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 0;
            float b2 = 1;
            float c2 = -ymax;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            if(temp[j][0] == x2 && temp[j][1]==y2)
            {
                flag = -1;
            }
            j++;
            if(flag==0)
            {
                temp[j][0] = x2;
                temp[j][1] = y2;
                j++;
            }

        }
    }
    for(i=0; i<j; i++)
    {
        coordinate[i][0]=temp[i][0];
        coordinate[i][1]=temp[i][1];
    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];
    node = j;

}
void bottom_clipping()
{
    float temp[100][2];
    float x1,y1,x2,y2;
    int j = 0,i;
    for(i=0; i<node; i++)
    {
        x1=coordinate[i][0];
        y1=coordinate[i][1];
        x2=coordinate[i+1][0];
        y2=coordinate[i+1][1];
        if(y1>=ymin&&y2>=ymin)
        {
            //in-in
            temp[j][0] = x2;
            temp[j][1] = y2;
            j++;
        }
        else if(y1<ymin&&y2<ymin)
        {
            //out out do nothing
        }
        else if(y1>ymin&&y2<=ymin)
        {
            //in-out
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 0;
            float b2 = 1;
            float c2 = -ymin;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            j++;

        }
        else if(y1<ymin&&y2>=ymin)
        {
            //out-in
            int flag = 0;
            float a1 = y1 - y2;
            float b1 = x2-x1;
            float c1 = y1*(x1-x2) - x1*(y1-y2);
            float a2 = 0;
            float b2 = 1;
            float c2 = -ymin;
            temp[j][0] = (b1*c2-b2*c1)/(a1*b2-a2*b1);
            temp[j][1] = (c1*a2 - c2*a1)/(a1*b2 - a2*b1);
            if(temp[j][0] == x2 && temp[j][1]==y2)
            {
                flag = -1;
            }
            j++;
            if(flag==0)
            {
                temp[j][0] = x2;
                temp[j][1] = y2;
                j++;
            }

        }
    }
    for(i=0; i<j; i++)
    {
        coordinate[i][0]=temp[i][0];
        coordinate[i][1]=temp[i][1];
    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];
    node = j;

}
void print()
{
    cout<<endl<<"New sequence :";
    for(int i = 0; i<node; i++)
    {
        cout<<" (";
        for(int j = 0; j<2; j++)
        {
            if(j==1)
            {
                cout<<coordinate[i][j];

            }
            else
            {
                cout<<coordinate[i][j];
                cout<<",";
            }

        }

        cout<<")";
        //  cout<<endl;
    }
}



void setup()
{
	ifstream input;
    input.open("inp.txt");
    if(input.fail())
        cout<<"Failed!"<<endl;
    string value,seq[4], s1, s2, s3, s4;

    int c = 0,i;
    while(input>>value)
    {
        c++;
        if(c<=4)
        {
            if(c==1)
            {
                stringstream s(value);
                s >> xmin;
            }
            else if(c==2)
            {
                stringstream s(value);
                s >> xmax;
            }
            else if(c==3)
            {
                stringstream s(value);
                s >> ymin;
            }
            else
            {
                stringstream s(value);
                s >> ymax;
            }
        }
        else if(c>=5 && c<=8)
        {
            if(c==5)
            {
                seq[c-5] = value;
                s1=seq[c-5];
            }
            else if(c==6)
            {
                seq[c-5]= value;
                s2=seq[c-5];
            }
            else if(c==7)
            {
                seq[c-5] = value;
                s3=seq[c-5];
            }
            else if(c==8)
            {
                seq[c-5] = value;
                s4=seq[c-5];
            }

        }
        else if(c==9)
        {
            stringstream s(value);
            s >> node;
            for( i = 0; i<node; i++)
            {

                for(int j = 0; j<2; j++)
                {
                    float x = 0;
                    input>>value;
                    stringstream s(value);
                    s >> x;
                    coordinate[i][j] = x;

                }
            }
        }

    }
    coordinate[i][0]= coordinate[0][0];
    coordinate[i][1]= coordinate[0][1];


    cout<<"Xmin = "<<xmin<<endl;
    cout<<"Xmax = "<<xmax<<endl;
    cout<<"Ymin = "<<ymin<<endl;
    cout<<"Ymax = "<<ymax<<endl;

    cout<<"Clipping edge sequence: "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;

    for(int i = 0; i<node; i++)
    {
        cout<<"P"<<i+1<<": (";
        for(int j = 0; j<2; j++)
        {
            if(j==1)
            {
                cout<<coordinate[i][j];

            }
            else
            {
                cout<<coordinate[i][j];
                cout<<",";
            }

        }

        cout<<")";
        cout<<endl;
    }
    cout<<endl;
    for(i=0; i<4; i++)
    {
        //if(!strcmp(seq[i],"L"))
        if(seq[i]=="L")
        {
            left_clipping();
            cout<<"Clipping with respect to LEFT edge... ";
            cout<<endl;
            print();


            cout<<endl;
        }
        else if(seq[i]=="R")
        {
            right_clipping();
            cout<<endl;
            cout<<"Clipping with respect to Right edge... ";
            print();
            cout<<endl;
        }
        else if(seq[i]=="T")
        {
            top_clipping();
            cout<<endl;
            cout<<"Clipping with respect to TOP edge... ";
            print();
            cout<<endl;
        }
        else if(seq[i]=="B")
        {
            bottom_clipping();
            cout<<endl;
            cout<<"Clipping with respect to BOTTOM edge... ";
            cout<<endl;
            print();
            cout<<endl;
        }
    }
}


int main(int argc, char** argv)
{
    setup();
}
