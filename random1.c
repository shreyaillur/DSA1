#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void bubblesort(int a[4],int m)
{
   int i,j,temp;
   for(i=0;i<m;i++)
    {
        for(j=0;j<m-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
              temp=a[j];
              a[j]=a[j+1];
              a[j+1]=temp;
            }
        }
    }
}
void selection(int n,int a[n])
{
    int ex,temp;
    for(int i=0;i<n-1;i++)
    {
        ex=i;
        for(int j=i+1;j<n;j++)
        {
            if(a[j]<a[ex])
            {
               ex=j;
            }
        }
        temp=a[ex];
        a[ex]=a[i];
        a[i]=temp;
    }
}
void merge(int arr[],int temp[],int left,int mid,int right)
{

    int i,left_end,size,temp_pos;
    left_end=mid-1;
    temp_pos=left;
    size=right-left+1;
    while(left<=left_end&&mid<=right)
    {
        if(arr[left]<=arr[mid])
        {
            temp[temp_pos]=arr[left];
            temp_pos++;
            left++;
        }
        else{
            temp[temp_pos]=arr[mid];
            temp_pos++;
            mid++;
        }
    }
    while(left<=left_end)
    {
         temp[temp_pos]=arr[left];
            temp_pos++;
            left++;
    }
       while(mid<=right)
    {
         temp[temp_pos]=arr[mid];
            temp_pos++;
            mid++;
    }
    for(int i=0;i<=size;i++)
    {
        arr[right]=temp[right];
         right--;
    }
}

void mergeSort(int arr[],int temp[],int low,int high)
{

    if(low<high)
    {
         int mid=low+(high-low)/2;

        mergeSort(arr,temp,low,mid);
        mergeSort(arr,temp,mid+1,high);
        merge(arr,temp,low,mid+1,high);
    }
}
int main()
{
    int i,n;
    clock_t start,end;
    double total;
    start=clock();
    scanf("%d",&n);
    FILE *file = fopen("input.txt","w+");
    FILE *file2=fopen("log.txt","w");
    int a[n];
    for(int i=0;i<n;i++)
       {
           a[i]=rand()%10000;
       }
       for(i=0;i<n;i++)
       {
          fprintf(file,"%d",a[i]);
       }
        for(i=0;i<n;i++)
        {
        fscanf(file,"%d",a[i]);
        }
    printf("\n");
    bubblesort(a,n);
    FILE *file1 = fopen("output.txt", "w");
    fprintf(file1,"BUBBLE SORT: \n");
    for(i=0;i<n;i++)
       {
          fprintf(file1,"%d ",a[i]);
       }
       fprintf(file1,"\n");
    end=clock();
    total=(double)(end-start)/CLOCKS_PER_SEC;
    fprintf(file2,"bubblesort:%f\n ",total);
    start=clock();
    for(i=0;i<n;i++)
        {
            fscanf(file,"%d",a[i]);
        }
    printf("\n");
    selection(n,a);
    fprintf(file1,"SELECTION SORT: \n");
    for(i=0;i<n;i++)
       {
          fprintf(file1,"%d ",a[i]);
       }
    end=clock();
    total=(double)(end-start)/CLOCKS_PER_SEC;
    printf("\n");
    fprintf(file2,"selectionsort:%f\n ",total);
    start=clock();
    for(i=0;i<n;i++)
        {
            fscanf(file,"%d",a[i]);
        }
    printf("\n");
    int temp[n];
    mergeSort(a,temp,0,n-1);
     fprintf(file1,"\nMERGE SORT: \n");
    for(i=0;i<n;i++)
       {
          fprintf(file1,"%d ",a[i]);
       }
        end=clock();
    total=(double)(end-start)/CLOCKS_PER_SEC;
    printf("\n");
    fprintf(file2,"mergesort:%f\n ",total);
    fclose(file);
fclose(file1);
fclose(file2);
    return 0;
}\
