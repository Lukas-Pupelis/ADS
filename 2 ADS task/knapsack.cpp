/* knapsack  problem using backtracking*/
/* Variable Description….
n   – Total no. of items available
weight[] – Weight of each item
value[] – Profit of each item
capacity   – Maximum Capacity of the Sack
unit[] – Profit of each item per Unit value[]/weight[]
finalSack[] – Final list of items put into the Sack
intermediate[] – Intermediate list of selected items
fp  – Final Profit
fw  – Final Weight
cp  – Current Profit
cw  – Current Weight
*/
#include<bits/stdc++.h>
using namespace std;

int weight[100];
int value[100];
int intermediate[100],finalSack[100];
int fp = -1, fw;
int capacity;
int n;
int finalPrice = 0;
int finalWeight = 0;
int variants = 0;
int depth = 0;
bool best;
	

void show()
{	
	ofstream out("protocol.txt", ios::app);
	
	out << "THIRD PART. Results" << endl;
	
	printf("\n\n Item numbers : ");
	out << "\n\n Item numbers : ";
	
	for(int i = 1; i <= n; i++){
		if(finalSack[i] == 1)
		{
			cout << setw(4) << right << i << " ";
			out << setw(4) << right << i << " ";
			
			finalPrice +=  value[i] * finalSack[i];
			finalWeight +=  weight[i] * finalSack[i];
		}
			

	}

	printf("\n Item weights  : ");
	out << "\n Item weights  : ";
		for(int i = 1; i <= n; i++){
		if(finalSack[i] == 1)
			{
			cout << setw(4) << right << weight[i] << " ";
			out << setw(4) << right << weight[i] << " ";
			}
		}
		
	printf("\n Item prices   : ");
	out << "\n Item prices   : ";
		for(int i = 1; i <= n; i++){
		if(finalSack[i] == 1)
			{
			cout << setw(4) << right << value[i] << " ";
			out << setw(4) << right << value[i] << " ";
			}
		}
		
	cout << " \n\nVariants sorted out: " << setw(4) << right << variants-1 << endl;
	out << " \n\nVariants sorted out: " << setw(4) << right << variants-1 << endl;	
	cout << "\n\n Selection's price : " << setw(4) << right << finalPrice << endl;
	cout << " Selection's weight: " << setw(4) << right << finalWeight << endl;
	out << "\n\n Selection's price : " << setw(4) << right << finalPrice << endl;
	out << " Selection's weight: " << setw(4) << right << finalWeight << endl;

}
/*Arrange the item based on high profit per Unit*/
int bound(int cp, int cw, int k)
{
	int b = cp;
	int c = cw;
	
	for(int i = k+1; i <= n; i++)
	{
		c = c + weight[i];
	if (c < capacity)
		b = b + value[i];
	else
		return (b+(1-(c-capacity)/ (int)weight[i])*value[i]);
	}
	return b;
}
void knapsack(int k,int cp,int cw)
{
	int iterationWeight = 0;
	ofstream out("protocol.txt", ios::app);
	
	if (variants > 0){
	out << setw(4) << right << variants << ")";
	int z = 0;
	
	for (int i = 1; i <= k; i++){
		if (intermediate[i] == 1)
		z++;
	}
	depth = z;
	for (int i = 1; i <= depth; i++)
	out << "-";

	out << " " << "Item numbers: ";
	for (int i = 1; i <= k; i++){
		if (intermediate[i] == 1)
		out << i << " ";
	}
	int loopWeight = 0;
	for (int i = 1; i <= k; i++){
		if (intermediate[i] == 1)
		loopWeight += weight[i];
	}
	iterationWeight = loopWeight;
	out << "Selection's weight: " << iterationWeight;
	if (iterationWeight > capacity){
		out << " --- Exceeding weight, not suitable";
	}
	else out << " --- OK";

	out << endl;
	}
	variants++;
	best = false;
	if(cw + weight[k] <= capacity)
	{
		intermediate[k] = 1;
		if(k < n){
			
			knapsack(k+1,cp + value[k],cw + weight[k]);
		}
		if(((cp+value[k]) > fp) && ( k == n))
		{
			fp = cp+value[k];
			fw = cw+weight[k];
				for(int j = 1; j <= k ; j++)
				finalSack[j] = intermediate[j];
		}
	}
	if(bound(cp,cw,k) >= fp)
	{
		intermediate[k] = 0;
		if(k < n){
			knapsack(k+1,cp,cw);
		}
		if((cp > fp) && (k == n))
		{
			best = true;
			fp = cp;
			fw = cw;
			for(int j = 1; j <= k; j++)
			finalSack[j] = intermediate[j];
		}
	}
}

int main()
{
	system("cls");
	cout << "Program solving a knapsack problem" << endl;
	cout << "Enter the data file name " << endl;
	string name;
	string txt = ".txt";
	cin >> name;
	name.append(txt);
	
	ofstream out("protocol.txt", ios::trunc);
	ifstream in(name);
	
	out << "FIRST PART. Data:" << endl;
	out << endl;
	
	while(!in.eof())
	{
		in >> n >> capacity;
		out << "N = " << n << "," << " " << "S = " << capacity << "." << endl;
		int k = 0;
		for (int i = 1; i <= n; i++)
		{
			k++;
			in >> weight[i] >> value[i];
			out << "S" << k << " = " << weight[i] << ", " << "K" << k << " = " << value[i] << "." << endl;
		}
	}
	
	out << endl;
	out << "SECOND PART. Execution." << endl;
	out << endl;
	out << endl;

knapsack(1,0,0);
show();
in.close();
out.close();
return 0;
}