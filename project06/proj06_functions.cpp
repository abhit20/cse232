#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::to_string;
#include<vector>
using std::vector;
#include<sstream>
using std::ostringstream; using std::ostream;
#include <algorithm>

vector < vector<long> > boards(vector<long> v, int rows, int cols){
	const vector<long>::size_type col_size = cols;
	const size_t row_size = rows;
	
	vector<long> row(col_size,0.0);
	vector< vector<long> > board(row_size, row);
	int k=0;
	for(int i =0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(k < v.size()){
				board[i][j] = v[k];
				k++;
			}
		}
	}
	return board;
}

ostream& print_vector(const vector<long>& w, ostream& pss){
	for(int i=0; i<w.size(); i++){
		pss<< to_string(w[i]);
		if(i!=w.size()-1)
			pss<<",";
	}
	return pss;
}

long four_corner_sum(const vector<long>& v, int row,int col){
	if(row <2 || col<2)
		return 0;
	long frow = v[0];
	long fcol = v[col-1];
	long lrow = v[(row*col)-col];
	long lcol = v[v.size()-1];
	long sum = frow+fcol+lrow+lcol;
	return sum;
}

vector<long> rotate_rows_up(const vector<long>& v, int row, int col){
	vector<long> resultempty;
	if (row<2) return resultempty;
	vector<long> result = v;
	for(int i =0; i < col; i++){
		result.push_back(v[i]);
		result.erase(result.begin());
	}
	return result;
}

vector<long> column_order(const vector<long>& v, int row, int col){
	vector<long> result;
	if(row < 2 || col <2)
		return result;
	auto board = boards(v, row, col);
	for(int c=0; c<col;c++) {
		for(int r=0; r<row; r++){
			result.push_back(board[r][c]);
		}
	}
	return result;
}

vector<long> matrix_ccw_rotate(const vector<long>& v, int row, int col){
	vector<long> result;
	if(row < 2 || col <2) return v;
	auto board = boards(v, row, col);
	for(int c =col-1;c>=0; c--){
		for(int r = 0;r<row;r++)
			result.push_back(board[r][c]);
	}
	return result;
}

long max_column_diff(const vector<long>& v, int row, int col){
	if(row<2 || col<2) return 0;
	
	vector<long> sums;
	auto board = boards(v, row, col);
	for(int c =0;c<col; c++){
		int sum =0;
		for(int r = 0;r<row;r++)
			sum+=board[r][c];
		sums.push_back(sum);
	}
	auto min = *std::min_element(sums.begin(), sums.end());
	auto max = *std::max_element(sums.begin(), sums.end());
	
	return (max-min);
}

long trapped_vals(const vector<long>& v, int row, int col){
	auto board = boards(v, row, col);
	int count =0;
	for(int r =0; r<row; r++){
		for(int c =0;c<col;c++){
			if(r==0 && c==0){
				int val = board[r][c];
				int t_val = board[row-1][c];
				int b_val = board[r+1][c];
				int r_val = board[r][c+1];
				int l_val = board[r][col-1];
				if((val <t_val) &&(val <b_val)&&(val <r_val)&&(val <l_val))
					count++;
			}
			else if (r==0 && c==(col-1)){
				int val = board[r][c];
				int t_val = board[row-1][c];
				int b_val = board[r+1][c];
				int r_val = board[r][0];
				int l_val = board[r][c-1];
				if((val <t_val) &&(val <b_val)&&(val <r_val)&&(val <l_val))
					count++;
			}
			else if (r==0 && c!=(col-1) && c!=0){
				int val = board[r][c];
				int t_val = board[row-1][c];
				int b_val = board[r+1][c];
				int r_val = board[r][c+1];
				int l_val = board[r][c-1];
				if((val <t_val) &&(val <b_val)&&(val <r_val)&&(val <l_val))
					count++;
			}
			else if (r==(row-1) && col==0) {
				int val = board[r][c];
				int t_val = board[r-1][c];
				int b_val = board[0][c];
				int r_val = board[r][c+1];
				int l_val = board[r][col-1];
				if((val<t_val) &&(val<b_val)&&(val<r_val)&&(val<l_val))
					count++;
			}
			
			else if(r==(row-1) && col ==(col-1)){
				int val = board[r][c];
				int t_val = board[r-1][c];
				int b_val = board[0][c];
				int r_val = board[r][0];
				int l_val = board[r][c-1];
				if((val<t_val) &&(val<b_val)&&(val<r_val)&&(val<l_val))
					count++;
			}
			else if(r==(row-1) && col !=0 && col !=(col-1)){
				int val = board[r][c];
				int t_val = board[r-1][c];
				int b_val = board[0][c];
				int r_val = board[r][c+1];
				int l_val = board[r][c-1];
				if((val <t_val) &&(val <b_val)&&(val <r_val)&&(val <l_val))
					count++;
			}
			else if(c == 0 && (r!=0 && r!=(row-1))){
				int val = board[r][c];
				int t_val = board[r-1][c];
				int b_val = board[r+1][c];
				int r_val = board[r][c+1];
				int l_val = board[r][col-1];
				if((val <t_val) &&(val <b_val)&&(val <r_val)&&(val <l_val))
					count++;
			}
			else if(c == (col-1) && r!=0 && r!=(row-1)){
				int val = board[r][c];
				int t_val = board[r-1][c];
				int b_val = board[r+1][c];
				int r_val = board[r][0];
				int l_val = board[r][c-1];
				if((val <t_val) &&(val <b_val)&&(val <r_val)&&(val <l_val))
					count++;
			} else {
				int val = board[r][c];
				int t_val = board[r-1][c];
				int b_val = board[r+1][c];
				int r_val = board[r][c+1];
				int l_val = board[r][c-1];
				if((val <t_val) &&(val <b_val)&&(val <r_val)&&(val <l_val))
					count++;
			}
		}
	}
	return count;
}

