#include"matrix.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

static int is_zero(double a){
	if( fabs(a) < 1E-6)
		return 1;
else
		return 0;
}

static void handle_1(double **matrix,int row,int column);//初步处理，化为行阶梯式
static void handle_2(double **matrix,int row,int column);//进一步处理，化为行最简式


void print_matrix(double **matrix,int row,int column){
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			printf("%3.5f ",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}


void get_matrix_size(int *row,int *column){
	printf("输入矩阵大小(行 列 如 2 4):");
	scanf("%d %d",row,column);
	getchar();					//清除缓冲区中的'\n'
}

double **malloc_matrix(int row,int column){
	double **matrix=(double **)malloc(sizeof(double *)*row);
	if(matrix == NULL){
		printf("malloc error\n");
		exit(1);
	}

	int i;
	for(i=0;i<row;i++){
		matrix[i] = (double *)malloc(sizeof(double)*column);
		if(matrix[i] == NULL){
			printf("malloc error\n");
			exit(1);
		}
	}
	return matrix;
}

void get_data(double **matrix,int row,int column){
	int i,j;
	char buf[BUFSIZE];
	char *ptr=buf;
	printf("输入数据,空格分开，以行为单位输入,不存在的未知数(如不存在x2),相应系数写0\n");
	for(i=0;i<row;i++){
		fgets(buf,BUFSIZE,stdin);
		ptr=buf;
		for(j=0;j<column;j++){
			sscanf(ptr,"%lf",&matrix[i][j]);
			
				while(*ptr != ' ' && *ptr != '\n'){
					ptr++;
				}
				while(*ptr == ' '){
					ptr++;
				}
			
		}
	}
}



static void handle_1(double **matrix,int row,int column){
	int i=0,j,k,l;
	
	int max;
	double *temp;
	double beishu;
	int pianyi=0;
	while(i<row && i<column ){																	
		max = i;																	//列选主元
		for(j=i+1;j<row &&(i+pianyi<column);j++){								   //	
			max = (fabs(matrix[j][i+pianyi])>=fabs(matrix[max][i+pianyi]))?j:max;
		}																				
		if(is_zero(matrix[max][i+pianyi])){							//如果是零，说明这一列都是零，
			pianyi++;												//则下一个处理的是这一行的下一个元素
			i--;													//所以偏移量加1 i--与后面的i++使i 不变
		}else{
			if(max != i){											//最大元素不是当前行，则调换两行
				temp = *(matrix+max);
				*(matrix+max) = *(matrix+i);
				*(matrix+i) = temp;
				printf("调换 %d行和%d行\n",i,max);
				print_matrix(matrix, row,column);
			}
			for(k=i+1;k<row;k++){
				if(is_zero(matrix[k][j])){									//将非零首元所在列中在其下面的元素都要化为0
					;														//如果是零就直接处理下一行
				}else{																	
					beishu = matrix[k][i+pianyi]/matrix[i][i+pianyi];		//不是零，求出倍数并处理
					for(l=0;l<column;l++){
						matrix[k][l] -= (matrix[i][l]*beishu);
					}
					printf("处理完%d行\n",k);
					print_matrix(matrix, row,column);
				}
			}
	
		}	
			
		i++;
	}
	print_matrix(matrix, row,column);


}
static void handle_2(double **matrix,int row,int column){		//将行阶梯矩阵化为最简形式
	int i,j,m,n;
	double beishu;
	double store;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			if(!is_zero(matrix[i][j])){		//找到非零首元
				store = matrix[i][j];	
				for(m=j;m<column;m++){						//将非零首元化为1
					matrix[i][m] = matrix[i][m]/store;		//后面的元素，都除以之前的首元
					
				} 
				printf("将第%d行首选化为1\n",i);
				print_matrix(matrix,row,column);
				for(m=i-1;m>=0;m--){						//将非零首元所在列的其他元素都化为0
					if(!is_zero(matrix[m][j])){
						beishu = matrix[m][j];
						for(n=j;n<column;n++){
							matrix[m][n] -= matrix[i][n]*beishu;
						}	
					}
					printf("处理第%d行\n",m);
					print_matrix(matrix,row,column);
				}
				break;									//跳出该行，处理下一行
			}
		}
	}
}
void handle_matrix(double **matrix,int row,int column){
	handle_1(matrix,row,column);
	handle_2(matrix,row,column);
}
