
#include <iostream>
using namespace std;

const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8; // 1000


const int x_max = 10;
const int y_max = 8;
const int x_min = 4;
const int y_min = 4;

int computeCode(double x, double y)
{
    int code = INSIDE;

    if (x < x_min) // to the left of rectangle
        code |= LEFT;
    else if (x > x_max) // to the right of rectangle
        code |= RIGHT;
    if (y < y_min) // below the rectangle
        code |= BOTTOM;
    else if (y > y_max) // above the rectangle
        code |= TOP;

    return code;
}


void cohenSutherlandClip(double x1, double y1,
                         double x2, double y2)
{
    // Compute region codes for P1, P2
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    // Initialize line as outside the rectangular window
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2) {
            // If both endpoints are outside rectangle,
            // in same region
            break;
        }
        else {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP) {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM) {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT) {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT) {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Now intersection point x, y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept) {
        cout << "Line accepted from " << x1 << ", "
             << y1 << " to " << x2 << ", " << y2 << endl;
        // Here the user can add code to display the rectangle
        // along with the accepted (portion of) lines
    }
    else
        cout << "Line rejected" << endl;
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
// Driver code
int main()
{
    // First Line segment
    // P11 = (5, 5), P12 = (7, 7)
    cohenSutherlandClip(5, 5, 7, 7);

    // Second Line segment
    // P21 = (7, 9), P22 = (11, 4)
    cohenSutherlandClip(7, 9, 11, 4);

    // Third Line segment
    // P31 = (1, 5), P32 = (4, 1)
    cohenSutherlandClip(1, 5, 4, 1);

    return 0;
}
