#ifndef MATRIX_H_
#define MATRIX_H_

#define BUFSIZE    4096

int equation_type(char type);    //返回方程类型 （齐次或非齐次）

void print_matrix(double **matrix,int row,int column);

void get_matrix_size(int *row,int *column);
double **malloc_matrix(int row,int column);    //申请内存

void get_data(double **matrix,int row,int column);

void handle_matrix(double **matrix,int row,int column);

#endif
