#include<bits/stdc++.h>
using namespace std;
//直接插入排序
void InsertSort(int a[], int n)
{
    for(int i = 1;i < n; ++i)
    {
        //i位置为待排序的元素，0-i-1的元素为已排序的元素
        if(a[i] < a[i - 1])
        //若当前元素比他前面的元素要小就向前遍历，找到比他小的元素插到其前面
        {
        //保存当前要插入的数
            int temp = a[i], j;
        //若是没有找到插入的位置就将当前元素后移
            for(j = i - 1;j >= 0 && temp < a[j];--j) a[j + 1] = a[j];
        //j位置为刚好比a[i]小，插入到其前面(j + 1)
            a[j + 1] = temp;
        }
    }
}

//直接插入排序优化（带哨兵）
void InsertSortSoldier(int a[], int n)
{
    for(int i = 2;i < n; ++i)
    {
        //i位置为待排序的元素，0-i-1的元素为已排序的元素
        if(a[i] < a[i - 1])
        //若当前元素比他前面的元素要小就向前遍历，找到比他小的元素插到其前面
        {
        //哨兵位置0保存当前要插入的数
            a[0] = a[i];
            int j;
        //若是没有找到插入的位置就将当前元素后移
        //当元素走到哨兵位置时j = 0,a[0] = a[j]一定会跳出循环
            for(j = i - 1;a[0] < a[j];--j) a[j + 1] = a[j];
        //j位置为刚好比a[i]小，插入到其前面(j + 1)
            a[j + 1] = a[0];
        }
    }
}

//折半插入排序
void InsertSortbinary(int a[], int n)
{
    for(int i = 2;i < n; ++i)
    {
        //i位置为待排序的元素，0-i-1的元素为已排序的元素
        if(a[i] < a[i - 1])
        //若当前元素比他前面的元素要小就向前遍历，找到比他小的元素插到其前面
        {
        //哨兵位置0保存当前要插入的数
            a[0] = a[i];
        //若是没有找到插入的位置就将当前元素后移
        //当元素走到哨兵位置时j = 0,a[0] = a[j]一定会跳出循环
        //在1-(i-1)的区间折半查找插入位置
            int low = 1, high = i - 1;
            while(low <= high)
            {
                int mid = (low + high) >> 1;
                //当a[mid] = a[0]时为了保证算法的稳定性，要继续向右查找插入位置
                if(a[mid] > a[i]) high = mid - 1;
                else low = mid + 1; 
            }
            //将low-(i-1)位置的元素全部右移，在low位置插入元素
            for(int j = i - 1;j > high;--j) a[j + 1] = a[j];
        //j位置为刚好比a[i]小，插入到其前面(j + 1)
            a[low] = a[0];
        }
    }
}

//希尔排序
void ShellSort(int a[], int n)
{
    //输入的n为数据元素个数，a[0]空出
    int d;
    //开始时规定增量d = n / 2
    //每次对分出来的子表排序完成后就将d / 2，直到d = 1为止
    for(d = n >> 1;d >= 1;d >>= 1)
    {
    //对子表当中的元素进行插入排序
        int i, j;
    //插入排序从表中的第二个元素开始，表中第一个元素为1，故将i初始化为1 + d
        for(i = d + 1;i <= n;++i)
        {
    //表中元素间隔为d，故下标映射为i - d
    //表中元素下标依次为i,i + d,i + 2d...
    //a[i - d]为当前元素在当前子表当中的前面一个元素
            if(a[i] < a[i - d])
            {
            //将当前位置元素存入a[0]位置中(这里a[0]不是哨兵)
                a[0] = a[i];
            //位置i的元素为待插入元素，因此寻找插入元素的位置从i - d开始
                for(j = i - d;j > 0 && a[0] < a[j];j -= d)
            //将子表中元素右移
                    a[j + d] = a[j];
                a[j + d] = a[0];
            }
        }
    }
}

//两元素交换
void swap(int &a, int &b)
{
    if(a != b)
    {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}

//冒泡排序
void BubbleSort(int a[], int n)
{
    for(int i = 0;i < n - 1;++i)
    {
    //i为开头元素
        bool flag = false;
    //设置标记，判断每趟排序是否进行交换，若没有发生交换则可以结束排序
        for(int j = n - 1;j > i;--j)
        {
        //从后往前交换数据元素，依次把最小的元素放在前面
            if(a[j - 1] > a[j]) 
            {
                swap(a[j - 1], a[j]);
                flag = true;
                //交换了元素，设置标记
            }
        }
        if(!flag) return;
        //没有发生元素交换可直接退出排序
    }
}

//将一个区间以头为基准划分为两部分（左边小于，右边大于）
//返回划分完毕后基准元素所在的最终位置
int Partition(int a[], int low, int high)
{
    //取首元素为基准
    int pivot = a[low];
    while(low < high)
    {
        //从右往左找小于基准的元素的位置
        while (low < high && pivot <= a[high]) --high;
        a[low] = a[high];//将找到的右边比基准元素小的元素换到左边去
        //从左往右找大于基准元素的位置
        while (low < high && pivot >= a[low]) ++low;
        //将左边大于基准元素位置的元素右边小于基准元素的位置交换
        a[high] = a[low];//将找到的左边比基准元素大的元素换到右边去
    }
    //最后的low/high位置为基准下标
    a[low] = pivot;
    return low;
}

//快速排序，low和high为区间的首末位置
void QuickSort(int a[], int low, int high)
{
    if(low < high)
    {
        //划分区间，并得到其最终下标
        int k = Partition(a, low, high);
        QuickSort(a, low, k - 1);
        //递归的对左区间L[low…k-1]排序
        QuickSort(a, k + 1, high);
        //递归的对右区间L[k+1…high]排序
    }
}

//选择排序
void SelectSort(int a[], int n)
{
    //只进行n - 1趟排序，当右区间剩余一个元素的时候即为最大值
    for(int i = 0;i < n - 1;++i)
    {
    //初始化区间内最小元素所在下标
        int Min = i;
        for(int j = i + 1;j < n;++j)
        //在剩余的区间内寻找最小元素，若找到最小元素就更新最小元素所在下标
            if(a[j] < a[Min]) Min = j;
        //若当前位置不为最小元素所在下标，将最小元素换到当前位置
        if(Min != i) swap(a[i], a[Min]); 
    }
}

//建立大根堆
void HeadAdjust(int a[],int k, int n);
void BuildMaxHeap(int a[],int n)
{
    for(int i = n >> 1;i > 0;--i)
     //从后往前（二叉树自底向上进行调整），保证在对根结点进行调整时左右子树一定为大根堆
        HeadAdjust(a, i, n);
}

//把以下标为k的根结点的子树调整为大根堆
void HeadAdjust(int a[],int k, int n)
{ 
    a[0] = a[k];   //空出的a[0]用于暂存子树的根结点
    //思路：
    //选择左右子树当中结点值较大的那个与根结点进行比较
    //根结点与子树进行交换，即大的元素被换上去，小的元素被换下来（小元素下坠）
    //被交换的那个子树其根结点值变小了，可能会破坏下面的大根堆
    //因此要移动到被交换的子树处以其为根继续向下检查调整

    //下标指针i为遍历比较指针，从根结点的左孩子（2 * k）开始遍历
    for(int i = k << 1;i <= n;i <<= 1)
    {
        //选择左右子树当中结点值较大的那个与根结点进行比较，i+1为右子树结点
        //若右子树比左子树大则选择右子树与根结点比较
        if(i < n && a[i] < a[i + 1]) ++i;
        //根结点比左右子树都大，不需要向下调整了，退出循环
        if(a[0] >= a[i]) break; 
        else
        {
            //子树的值比根大，将大的那个子树值移动到根结点
            a[k] = a[i];
            //调整根为被交换子树的下标继续向下调整
            k = i;
        }
    }
    a[k] = a[0];   //将被筛选的结点放入最终位置
}

//堆排序
void HeapSort(int a[], int n)
{
    //构建一个大根堆
    BuildMaxHeap(a, n);
    for(int i = n;i > 1;--i)
    {
        //交换根结点与最末端叶子结点的值
        swap(a[1], a[i]);
        //将剩余的待排序序列重新调整成大根堆
        HeadAdjust(a, 1, i - 1);
    }
}


//合并两个子序列，low为第一个序列的起始下标，mid为第一个序列的尾下标
//mid + 1为第二个序列的起始下标
void merge(int a[], int low, int mid, int high)
{
    //初始化一个辅助数组，用于存储两个数组当中的值
    int *b = new int[high - low + 1];
    int n = 0;
    //将两个数组复制到辅助数组当中
    for(int i = low;i <= high;++i) b[n++] = a[i];
    int i, j, m = mid - low, k = low;
    //i指向第一个数组的起始下标，j指向第二个数组的起始下标
    for(i = 0, j = m + 1;i <= m && j < n;++k)
    {
    //将两个数组（辅助数组内）当中最小的一个放入合并数组（原数组）当中，并移动对应指针
        if(b[i] < b[j]) a[k] = b[i++];
        else a[k] = b[j++]; 
    }
    //将没有合并的数组合并进去
    while(i <= m) a[k++] = b[i++];
    while(j < n) a[k++] = b[j++];
    delete b;
}

//归并排序（递归）
void mergesort(int a[],int low,int high)
{
    //采用分治算法的思想，从中间开始拆分合并
    if(low < high)
    {
        int mid = (low + high) >> 1;
        //递归的对左半部分的数组进行排序
        mergesort(a, low, mid);
        //递归的对右半部分的数组进行排序
        mergesort(a,mid + 1,high);
        //将其两边拆分完毕的数组合并
        merge(a, low, mid, high);
    }
}

//归并排序（非递归）
void mergesort(int a[],int n)
{
    //i为每个子区间的长度
    for(int i = 1;i < n;i <<= 1)
    //j为第一个子区间的起始下标
        for(int j = 0;j < n;j += 2*i) 
            merge(a,j,j + i - 1,(j + 2*i - 1) < n ? (j + 2*i - 1) : n - 1);
}

int main()
{
    int a[] = {49, 38, 65, 97, 76, 13, 27};
    //mergesort(a, 7);
    mergesort(a, 0, 6);
    for(int i = 0;i < 7;++i) cout << a[i] << " ";
}