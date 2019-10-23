#include<iostream>
#include<fstream>
using namespace std;



bool is_reducedEche_form(int **x, int row, int col) {
	// your code here
	// access **matrix like this matrix[i][j]
	bool lead_entry_right=true;
	bool pivot_entry_1=true;
	bool lead_only_col=true;
	bool zero_row_below=true;
	int temp=-1;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if (x[i][j]==0)
			{
                continue;
			}
			
			else if (x[i][j]==1)
			{
                if (temp<j)
				{		 
                    temp=j;
                    break;
                }
            	else
				{			 
            	lead_entry_right= false;
				}			  
			}
		}
	}
	
	
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if (x[i][j]==0)
			{
                continue;
			}
			else if (x[i][j]==1)
			{	
				break;
			}
			else{
				pivot_entry_1=false;
			}
		}
		
		}
		
	
	
		for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if (x[i][j]==0)
			{
                continue;
			}
			else if (x[i][j]==1)
			{
				for(int p=0;p<row;p++){
					if((x[p][j]==0) || (p==i)){
						continue;
					}
					else{
						lead_only_col=false;
					}
				}
				break;
			}
		}
	}
	
	bool element_below=false;
	for(int i=0;i<row;i++){
		bool zero_row=true;
		for(int j=0;j<col;j++){
				if (x[i][j]==0)
				{
                continue;
				}
				else{
					if(element_below==true){
						zero_row_below=false;
					}
					zero_row=false;
				}
				
		}
		if(zero_row==true){
			element_below=false;
		}
		
	}
	
	
	if ((lead_entry_right) && (pivot_entry_1) && (lead_only_col) && (zero_row_below)){
		return true;
	}
	else{
		return false;
	}
	

	
}




int pls(int x[],int **y,int row,int col)

{
	
	for(int i=0;i<col;i++)
	{
		y[row][i]=y[row][i]+x[i];		
	}	
	
}

void zero(int **x,int rw, int cl)
{	
	
		
	int temp[rw][cl+1];
	for(int i=0;i<rw;i++)
	{
		for(int j=0;j<cl;j++)
		{
			temp[i][j]=x[i][j];
			
		}
	
	}
	
	int count;
	for(int i=0;i<rw;i++)
	{
		count=0;
		for(int j=0;j<cl;j++)
		{
			if(temp[i][j]==0)
			{
				count+=1;
				continue;	
			}
			else{
				break;
			}
		}
		
		temp[i][rw+1]=count;
	}
	
	int i,t;
	for(int k=0;k<rw;k++)
	{
		i=0;
		while(i<(rw-1))
		{
			if(temp[i][cl]>temp[i+1][cl])
			{	
			
				t=temp[i][cl];
				temp[i][cl]=temp[i+1][cl];
				temp[i+1][cl]=t;
				
				for(int kk;kk<cl;kk++)
				{	
					t=x[i][kk];
					x[i][kk]=x[i+1][kk];
					x[i+1][kk]=t;
				}			
			}
			
			i+=1;
			
		}
			
			
	}
	
}


bool functi(int **matrix, int row , int col)  // check zero rows at bottom or free variables
{
	int last_row=row-1;
	bool check=false;
	for(int i=0;i<col;i++)
	{
		if (matrix[ last_row ] [i] !=0)
		{
			check=true;
		}
	}
	return check;
}

void reduce(int **matrix, int row,int col,string &msg)
{
	int temp_rw=0,temp_cl=0;
	
	for(int i=0;i<row;i++)
	{	
		bool is_value=true;
		zero(matrix,row,col);
		
		
		if((matrix[temp_rw][temp_cl]!=1) && (matrix[temp_rw][temp_cl]!=0))
		{	
			float num=matrix[temp_rw][temp_cl];
			for(int jj=0;jj<col;jj++)
			{
				matrix[temp_rw][jj]/=num;
			}
			
		}
		
		if(matrix[temp_rw][temp_cl]!=0)
		{
			is_value=false;
		}
		
		int down=temp_rw+1,tp[col];
		for(int j=down;j<row;j++)
		{	
			
			for(int kc=0;kc<col;kc++)
			{
				tp[kc]=matrix[temp_rw][kc]*(-matrix[j][ temp_cl ]);		
			}
			
			pls(tp,matrix,j,col);
			
		}
		
			
				
		int up=0;
		while(up<temp_rw)
		{	
			for(int kc=0;kc<col;kc++)
			{
				tp[kc]=matrix[temp_rw][kc]*(-matrix[up][ temp_cl ]);		
			}
			pls(tp,matrix,up,col);
			up+=1;
		}
		if(is_value==true)
		{
			temp_cl+=1;
		}
		else
		{
			temp_rw+=1;
			temp_cl+=1;
		}
	}
	if(functi(matrix,row,col))
	{
		msg="it is linearly independent ";
	}
	else
	{
		msg="it is linearly dependent ";
	}
}


//Don't touch this function
void alloca_memory(int **matrix, int row, int col) {
	for (int i = 0; i < row; i++)
		matrix[i] = new int[col];
}

//Don't touch this function
void free_memory(int **matrix, int row) {
	for (int i = 0; i > row; i++)
		delete[] matrix[i];
	delete[] matrix;
}

int main() {

	int row = 0, col = 0, tmatrix = 0;
	int **matrix = 0;
	string msg;
	ifstream in("in.txt");
	ofstream out("out.txt"); // will automatically created if not present

	if (!in.is_open()) {
		cout << "Error in opening file" << endl;
		return 0;
	}

	in >> tmatrix;
	cout<<"open out.txt file to see results"<<endl;
	for (int i = 0; i < tmatrix; i++) {
		in >> row >> col;
		matrix = new int*[row];
		alloca_memory(matrix, row, col);
		
		for (int k = 0; k < row; k++) {
		
			for (int j = 0; j < col; j++)
			{
					in >> matrix[k][j];
				
			}
			
			}
		
		if(col>row)
		{
			msg="it is linearly dependent ";
		}
		
		else if (is_reducedEche_form(matrix, row, col)) // your desired function to which you passes 2d array(matrix)
			{
			
				if(functi(matrix, row, col))
				{
				msg="it is linearly dependent ";	
				}
				
			}
			
		else
		{
			reduce(matrix,row,col,msg);
		
		 }
		
			
			out <<"\n\nRows = "<<row<<" , COl =  "<<col <<"\n";
			out<<msg<<"\n\n"<<endl;
		
		

		free_memory(matrix, row); // to free the memory allocated
		
		

	}



}
