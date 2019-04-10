#include<bits/stdc++.h>
#include<graphics.h>
using namespace std;

unordered_map<string,vector<float>> db;
unordered_map<string,vector<float>>::iterator it;
vector<vector<float>>p(8);         // population
vector<float>fit,max_fit;                 //fitness of all parameters in a chromosome
vector<float>ff;
int n;               //fitness value of all population
int C=1800;


void printgraph(vector<float> v)
{   cout<< endl<< "points";
    int n=v.size(),i;
    for(i=0;i<n-1;i++)
    {   cout<<v[i]<<" "<<v[i+1]<<endl;
        line(20*i+100,500-(200*v[i]),20*(i+1)+100,500-(200*v[i+1]));
    }
}

void obj(int i,vector<float>p,vector<float>&fit)
{
    float f=0;int j=0;
    for(it=db.begin();it!=db.end();it++,j++)
       {
         f+=it->second[i]*p[j];
       }
    fit.push_back(f);
}


float fitness(vector<float>fit)
{  int w0=2, w1=2,w2=2,w3=5,w4=4,w5=2,w6=3,w7=2;
   float f;
   f= ((w1*fit[1] )+ (w2*fit[2])+(w6*fit[6]))/( abs(w0*fit[0])  + abs(w5*fit[5]) +(w3*fit[3] )+ (w4*fit[4]) +w7   );
   return 1-f;
}


 void selection(vector<int>&index)
{
      vector<float>r;
      vector<float>ff1;

      float tot=0;
      for(int i=0;i<8;i++)
      {
          ff1.push_back(1/(1+ff[i]));
          tot+=ff1[i];
      }

      ff1[0]=ff1[0]/tot;
      for(int i=1;i<8;i++)
      { ff1[i]=ff1[i-1]+ff1[i]/tot;
      }

  for(int i=0;i<4;i++)
  {   float t=(float)rand()/(RAND_MAX+1);
      r.push_back(t);
      r.push_back(1-t);

  }

   for(int i=0;i<8;i++)
   {   if(r[i]>=0 && r[i]<ff1[0])
       {
           index.push_back(0);
               continue;
       }

       for(int j=0;j<8;j++)
       {
           if(r[i]>=ff1[j]&& r[i]<ff1[j+1])
           {  index.push_back(j+1);
               break;
           }
       }
   }






}

void mutation(vector<vector<float> > &v)
{
    int length = n * 8;
    float mr = .15 * length;    //mutation rate
    mr = (int)mr;
    int r,i;
    for(i=0;i<mr;i++)
    {
        r = 1 + (rand() % (int)(length));
        int which_chr = ceil((float)r/n) - 1;
        int gen = r%n;
        if(gen == 0)
            gen = n-1;
        else
            gen--;

     it=db.begin();
     for(int i=0;i<gen;i++)
        it++;
     float xi = it->second[5];
     r=(float)rand()*xi/RAND_MAX;
     v[which_chr][gen] = r;  //change the gene of that chromosome
    }
}






void crossover(vector<vector<float>>&par,vector<float>&nfit)
{   int n=nfit.size();
    float rho=0.25;
    vector<int>ind;
    float t;
    for(int i=0;i<8;i++)
   {

    t=(float)rand()/(RAND_MAX+1);
    if(t<=rho)
     ind.push_back(i);

   }
   srand(time(0));
  vector<vector<float>>ch;
  vector<int>re;
  vector<float>fittt;
     cout<<"\nindexes\n";
   for(int i=0;i<ind.size();i++)
       {
           cout<<ind[i]<<" ";
       }
  for(int i=0;i<ind.size();i++)
  {
      int k=(i+1)%ind.size();
       vector<float>v;
       int r= rand()%(n+1);
       for(int j=0;j<=r;j++)
       {
         v.push_back(par[ind[i]][j]);
       }
       for(int j=r+1;j<n;j++)
       {
         v.push_back(par[ind[k]][j]);
       }



       for(int l=0;l<7;l++)
       {obj(l,v,fittt);
       }
       fittt[0]=(6/10*C)-fittt[0];
       fittt[5]=C-fittt[5];
       if(fitness(fittt)>ff[ind[i]])
        {
            ch.push_back(v);
         re.push_back(i);
        }
  }

  for(int i=0;i<re.size();i++)
  {  par[ re[i]].clear();
     par[ re[i]]=ch[i];

  }


}
void insertdb()
{ vector<float>d;
  d.insert(d.end(),{20,60,12,8,3,100,3});
  db.insert(make_pair("fi1",d));
  d.clear();
  d.insert(d.end(),{60,20,22,20,5,260,5});
  db.insert(make_pair("fi2",d));
  d.clear();
  d.insert(d.end(),{80,30,32,80,5,300,7});
  db.insert(make_pair("fi3",d));
  d.clear();
  d.insert(d.end(),{100,40,62,50,8,900,4});
  db.insert(make_pair("fi4",d));
  d.clear();
  d.insert(d.end(),{500,200,22,200,1,400,8});
  db.insert(make_pair("fi5",d));
  d.clear();
  d.insert(d.end(),{80,20,62,50,4,65,9});
  db.insert(make_pair("fi6",d));
  d.clear();
  d.insert(d.end(),{120,20,62,50,4,65,9});
  db.insert(make_pair("fi7",d));
  d.clear();
  d.insert(d.end(),{60,20,22,20,5,260,5});
  db.insert(make_pair("fi8",d));
  d.clear();
  d.insert(d.end(),{400,20,22,510,6,700,6});
  db.insert(make_pair("fi9",d));
  d.clear();
  d.insert(d.end(),{60,20,42,20,2,260,9});
  db.insert(make_pair("fi10",d));
  d.clear();
 /* d.insert(d.end(),{660,20,42,20,2,260,9});
  db.insert(make_pair("fi11",d));
  d.clear();
  d.insert(d.end(),{100,10,82,20,6,20,9});
  db.insert(make_pair("fi12",d));
  d.clear();
 /* d.insert(d.end(),{200,60,42,20,2,260,9});
  db.insert(make_pair("fi13",d));
  d.clear();
  d.insert(d.end(),{300,20,42,50,9,300,9});
  db.insert(make_pair("fi14",d));
  d.clear();
  d.insert(d.end(),{560,60,67,80,4,500,3});
  db.insert(make_pair("fi15",d));
  d.clear();
  d.insert(d.end(),{430,50,72,45,5,260,7});
  db.insert(make_pair("fi16",d));
  d.clear();
  d.insert(d.end(),{670,100,142,20,4,260,4});
  db.insert(make_pair("fi17",d));
  d.clear();
  d.insert(d.end(),{450,120,156,80,4,260,6});
  db.insert(make_pair("fi18",d));
  d.clear();
 /* d.insert(d.end(),{640,90,87,20,2,260,9});
  db.insert(make_pair("fi19",d));
  d.clear();
  d.insert(d.end(),{870,50,74,98,28,260,9});
  db.insert(make_pair("fi20",d));
  d.clear();
  d.insert(d.end(),{843,60,120,460,2,260,6});
  db.insert(make_pair("fi21",d));
  d.clear();
  d.insert(d.end(),{760,870,42,220,2,260,7});
  db.insert(make_pair("fi22",d));
*/
}


int main()
{  int gd=DETECT,gm;
   initgraph(&gd,&gm,"");
  srand(time(0));
  int  c=20;      //calorie total

  insertdb();
  n=db.size();
  int chrom[n];
  float r;

  int xi,k=0;
  for(it=db.begin();it!=db.end();it++)
 {
 cout<<it->first <<" ";
 for(int i=0;i<7;i++)
    cout<<it->second[i]<<" ";
 }
 cout<<endl;
    for(int j=0;j<8;j++)
     {
         for(it=db.begin();it!=db.end();it++)
      {   xi= C/it->second[5];

          r=(float)rand()*xi/RAND_MAX;                                   //xi=C/Ci
          p[j].push_back(r);

     }
     }
     cout<< "pop:";
for(int i=0;i<8;i++)
{
    for(int j=0;j<n;j++)
        cout<<p[i][j]<<" ";
    cout<<endl;
}

while(c--)
  {  cout<<"gen"<<c-19<<" ";
      ff.clear();
   for(int i=0;i<8;i++)
   {   for(int j=0;j<7;j++)
         obj(j,p[i],fit);                      // ff contains fitness of all generations

       fit[0]=(6/10*C)-fit[0];
       fit[5]=C-fit[5];
       ff.push_back(fitness(fit));
       fit.clear();
   }
    cout<<"fitness"<<endl;
   for(int i=0;i<8;i++)
    cout<<ff[i]<< " ";
   cout<< endl;

   vector<int>in;
   selection(in);               cout<<"indices"<<endl;      for(int i=0;i<8;i++) cout<<in[i]<<" ";
   vector<vector<float>>parent;
   vector<float>nfit;

   for(int i=0;i<8;i++)
   {
       /* for(int j=0;j<n;j++)
         cout<<p[in[i]][j]<<" ";
         cout<<endl;
         */
       parent.push_back(p[in[i]]);
       nfit.push_back(ff[in[i]]);
   }
  cout<<endl<<"new fitness"<<endl;
 for(int i=0;i<8;i++)
    cout<<nfit[i]<< " ";

 cout<<endl<<"parent\n";
   for(int i=0;i<8;i++)
 {
    for(int j=0;j<n;j++)
        cout<<parent[i][j]<<" ";
    cout<<endl;
 }


   crossover(parent,nfit);
   p=parent;
   mutation(p);
   cout<<endl<<"new population\n";
   for(int i=0;i<8;i++)
 {
    for(int j=0;j<n;j++)
        cout<<p[i][j]<<" ";
    cout<<endl;
 }

   float max=ff[0];
  for(int i=1;i<n;i++)
  {  if(ff[i]>max)
     {max=ff[i];
     k=i;
     }

  }
  cout<<"max"<<max<<endl;

max_fit.push_back(max);
  }
printgraph(max_fit);
for(int i=0;i<max_fit.size();i++)
    cout<<max_fit[i]<<" ";

    cout<<endl<<endl;
    cout<<"diet plan:"<<endl;

    int l=0;
    it=db.begin();
    for(;l<n;l++,it++)
    {    if(p[k][l]>2)
        cout<<it->first<<" "<<p[k][l]<<"g"<<endl;
    }





getch();
closegraph();

}
