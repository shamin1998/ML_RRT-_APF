#include<bits/stdc++.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<ctime>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

int isValid(int i , int j , Mat img, int r)
{
    if ( i < img.rows-r/2 && j < img.cols-r/2 && i > r/2 && j > r/2)
        return 1;
    return 0;
}

Mat circle(Mat a, int i, int j, int r)
{
    int p,q;
    i = i-r;
    j = j-r;
    for(p=i-r;p<i+r;p++)
        for(q=j-sqrt(pow(r,2)-pow(p-i,2));q<j+sqrt(pow(r,2)-pow(p-i,2));q++)
        {
            if(isValid(q,p,a,r))
            a.at<uchar>(p,q)=255;
        }

    return a;
}

Mat square(Mat a , int j , int k , int r )
{
    int m,n;
    for(m = j - r; m <= j + r; m++)
    {
        for(n = k - r; n <= k + r; n++)
        {
            if(isValid(m, n, a,r))
            {
                a.at<uchar>(m,n) = 255;
            }
        }
    }
    return a;
}

Mat triangle(Mat a , int j , int k , int r )
{
    int m,n;
    for(m = j - r; m <= j + r; m++)
    {
        for(n = m; n <= k + r; n++)
        {
            if(isValid(m, n, a,r))
            {
                a.at<uchar>(m,n) = 255;
            }
        }
    }
    return a;
}

int main()
{
    int a[3] = {0,1,2};
    srand(time(0));
    int number = 10000;
    //int num[10000];
    ofstream myfile1;
    myfile1.open("number.txt");

    ofstream myfile2;
    myfile2.open("obst.txt");
    while(number--)
    {
        int obs_number = 4+ rand()%8;
        Mat img(100,100,CV_8UC1,Scalar(0));
        // vector<int> x(obs_number);
        // vector<int> y(obs_number);
        // vector<float> area(obs_number);
        int max1 = obs_number;
        //num[10000-number]=max;
        myfile1 << max1 << endl;
        while(obs_number--)
        {
            int shape = rand()%3;
            if(shape == 0)
            {
                int x = rand()%(img.rows);
                int y = rand()%(img.cols);
                int r = 5+rand()%10;
                img = circle(img,x,y,r);
                float area = 3.14*r*r;
                myfile2 << x << " " << y << " " << area << endl;
            }
            else if(shape == 1)
            {
                int x = rand()%(img.rows);
                int y = rand()%(img.cols);
                int r = 5+rand()%10;
                img = square(img,x,y,r);
                float area = 4*r*r;
                myfile2 << x << " " << y << " " << area << endl;
          }
            else if(shape == 2)
            {
                int x = rand()%(img.rows);
                int y = rand()%(img.cols);
                int r = 5+rand()%10;
                img = triangle(img,x,y,r);
                float area = 0.5*r*r;
                myfile2 << x << " " << y << " " << area << endl;
            }
        }
        //std::string s = std::to_string(number);
        stringstream ss;
        ss<<number;
        string s = "dataset/";
        string s1 = "img";
        string s2 = ss.str();
        string s3 = ".jpg";
        //string s4 = "1";
        imwrite(s+s1+s2+s3,img); 
    }
    return 0;
}