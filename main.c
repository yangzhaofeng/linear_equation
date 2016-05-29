int main(){
	
	int row,column;		
	double **matrix;
	
	
	get_matrix_size(&row,&column);

	matrix=malloc_matrix(row,column);
	get_data(matrix, row,column);
	
	print_matrix(matrix, row,column);

	handle_matrix(matrix,row, column);	   //处理矩阵化为行最简式，调用了第一部和第二部处理函数
	print_matrix(matrix, row,column);

	return 0;
}
