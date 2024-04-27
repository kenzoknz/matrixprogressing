#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
//Khai bao nguyen mau cac ham
void ReadfromKeyboard(float a[][MAX], int n); // Doc ma tran tu ban phim
void Valid(char *filename, int *n); // Kiem tra file co dung dinh dang khong
void ReadfromFile(char *filename, float matrix[][MAX], int *n); // Doc ma tran tu file
void MultiplyAndSum(float A[][MAX], float B[][MAX], float C[][MAX], float D[][MAX], int n); //Ham tinh tich va tong 2 ma tran
void Output(float matrix[][MAX], int n); //Xuat ma tran
void chuyenVi(float a[][MAX], float b[][MAX], int n); //Ma tran chuyen vi
void writeMatrixToFile(char *filename, float A[][MAX], float B[][MAX], float TransposeA[][MAX], int n); //Luu ket qua vao file
void Menu(); //Menu lua chon

int main(){
	Menu();
	return 0;
}
//Driver program function
void ReadfromKeyboard(float a[][MAX], int n, char s){
    printf("Nhap cac phan tu cua ma tran %c:\n",s);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c[%d][%d]: ",s, i+1, j+1);
            scanf("%f", &a[i][j]);
        }
    }
}
void Valid(char *filename, int *n) {
    FILE *file = fopen(filename, "r");
    char ch, pre = '1'; // ch la ki tu, pre la index cua ki tu truoc do
    int count = 0; //dem so phan tu ma tran
    if (file == NULL) {
        printf("Khong the mo file %s.\n", filename);
        exit(1);
    }
    fscanf(file, "%d", n);

    while ((ch = fgetc(file)) != EOF) // lay tung ki tu cua file cho den het file
    {
        if(isalpha(ch)) 
        {
            printf("Ma tran vua nhap co phan tu khong phu hop!!!");
            exit(1);
        }
        if (ch == ' ' || ch == '\n') //Neu ki tu la khoang trang hoac xuong dong, xet tiep dieu kien duoi
        {
            if (pre == '1') pre = ' '; //Ki tu truoc do la so thi set thanh khoang trang
        }
        if (ch != ' ' && ch != '\n') //Neu ki tu khhong phai khoang trang hoac xuong dong, xet tiep dieu kien duoi 
        {
            if (pre == ' ') //Neu index cua ki tu truoc do la khoang trang thi tang bien dem va set index thanh so
            {
                count++;
                pre = '1';
            }
        }
    }
    if (count != (*n)*(*n)) //Neu bien dem khong bang kich co thi bao loi (tru dong dau la nhap kich co ma tran)
    {
        printf("Ma tran sai luong du lieu!!");
        exit(0);
    } 
    fclose(file);
}
void ReadfromFile(char *filename, float matrix[][MAX], int *n){
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
        printf("Loi mo file %s \n", filename);
        exit(1);
    }
    fscanf(file, "%d", n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%f", &matrix[i][j]);
        }
    }

    fclose(file);
}
void MultiplyAndSum(float A[][MAX], float B[][MAX], float C[][MAX], float D[][MAX], int n) {

    //tich 2 matran
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    //tong 2 matran
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            D[i][j] = A[i][j] + B[i][j];
        }
    }
}
void Output(float matrix[][MAX], int n){
	printf("\n");
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			printf("%4.2f \t", matrix[i][j]);
		}
		printf("\n");
	}
}
void chuyenVi(float a[][MAX], float b[][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = a[j][i];
        }
    }
}
void swapColumns(float matrix[][MAX], float matrix2[][MAX], int p, int q, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix2[i][j] = matrix[i][j]; //Luu mang phu truoc khi hoan doi de in ket qua
    for (int i = 0; i < n; i++) {
        float temp = matrix[i][p];
        matrix[i][p] = matrix[i][q];
        matrix[i][q] = temp;
    }
}
void writeMatrixToFile(char *filename, float A[][MAX], float B[][MAX], float C[][MAX], float TransposeA[][MAX], float TransposeB[][MAX], int n) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Loi mo file %s \n", filename);
        exit(1);
    }
	
	fprintf(file, "Ma tran tong: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%4.2f \t", A[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nMa tran tich: \n");
	 for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%4.2f \t", B[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nMa tran tich sau khi doi cot: \n");
	 for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%4.2f \t", C[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nMa tran chuyen vi cua A: \n");
	 for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%4.2f \t", TransposeA[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nMa tran chuyen vi cua B: \n");
	 for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%4.2f \t", TransposeB[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
void Menu(){
	float A[MAX][MAX], B[MAX][MAX], Product[MAX][MAX], 
	Sum[MAX][MAX], temp[MAX][MAX], TransposeA[MAX][MAX], TransposeB[MAX][MAX];
    int m,n,choice,ok=0,ok1=0;
    int count;

    char file1[100], file2[100], file3[100];
    MENU: do {
    system("cls");
    printf("Moi ban chon 1 trong cac lua chon sau day:\n");
        printf("\t1. Doc ma tran vuong A, B tu ban phim\n");
        printf("\t2. Doc ma tran A, B tu file\n");
        printf("\t3. Xuat ma tran A va B ra man hinh\n");
        printf("\t4. Tinh tong va tich 2 ma tran A, B\n");
        printf("\t5. Tim ma tran chuyen vi cua ma tran A, B\n");
        printf("\t6. Hoan doi cot cua ma tran tich.\n");
        printf("\t7. Luu ket qua vao file\n");
        printf("\t8. Ket thuc\n");        
        
	  printf("Chon chuc nang: "); scanf("%d", &choice);
	  switch (choice) {
            case 1:
            	system("cls");
                printf("Nhap bac cua ma tran vuong A: ");
                scanf("%d", &m);
                printf("Nhap bac cua ma tran vuong B: ");
                scanf("%d", &n);
                ReadfromKeyboard(A,m,'A');
                ReadfromKeyboard(B,n,'B');
                ok=1;
                printf("Da nhap thanh cong, bam phim bat ki de quay lai menu.");
                getch();
                break; 
            case 2:
            	system("cls");
            	printf("Nhap ten file cho ma tran A: ");
   				scanf("%s", file1);
    			printf("Nhap ten file cho ma tran B: ");
    			scanf("%s", file2);
    			Valid(file1,&m);
				Valid(file2,&n);
    			ReadfromFile(file1, A, &m);
    			ReadfromFile(file2, B, &n);
    			printf("Da doc thanh cong, bam phim bat ki de quay lai menu.");
    			ok = 1;
    			getch();
    			break;
    		
    		case 3: 
    			if (ok==0) {
					printf("Chua nhap du lieu ma tran, Khong the xuat.\n");
					getch();
					break;
				}
				system("cls");
    			printf("Ma tran A:\n");
    			Output(A,m);
    			printf("Ma tran B: \n");
    			Output(B,n);
    			printf("\nBam phim bat ki de quay lai menu.");
    			getch();
    			break;
    		case 4:
    			if (ok==0) {
					printf("Chua nhap du lieu ma tran, Khong the tinh.\n");
					getch();
					break;
				}
				system("cls");
    			int a,b;
    			a = sizeof(A)/sizeof(A[0]);
    			b = sizeof(B)/sizeof(B[0]);
    			if ((a==0)||(b==0)){
						printf("Chua co du lieu cua 1 trong 2 ma tran, khong the thuc hien phep tinh.");
						getch();
						break;
					}
    			if (m!=n) {
					printf("2 ma tran khong cung kich co! Khong the thuc hien phep tinh");
					printf("Bam phim bat ki de quay lai menu.");
					getch();
					break;
					}
				 system("cls");
    			 MultiplyAndSum(A,B,Product,Sum,n);
    			 printf("\nMa tran tong la: ");
    			 Output(Sum,n);
    			 printf("\nMa tran tich la: ");
    			 Output(Product,n);
    			 ok1=1;
    			 printf("Bam phim bat ki de quay lai menu.");
    			 getch();
    			 break;
    		case 5:
    			if (ok==0) {
					printf("Chua co du lieu ma tran.\n");
					getch();
					break;
				}
				
    			system("cls");
    			printf("Ma tran A:\n");
    			Output(A,m);
    			printf("Ma tran B: \n");
    			Output(B,n);
    			printf("Ma tran chuyen vi cua ma tran A:\n");
                chuyenVi(A, TransposeA, m);
                Output(TransposeA,m);
                printf("Ma tran chuyen vi cua ma tran B:\n");
                chuyenVi(B, TransposeB, m);
                Output(TransposeB,n);
                getch();
                break;
            case 6: 
            if (ok==0) {
					printf("Chua nhap du lieu ma tran, Khong the thuc hien.\n");
					getch();
					break;
				}
			if (ok1==0) {
					printf("Chua tinh tich cua ma tran, Khong the tinh.\n");
					getch();
					break;
				}
            	system("cls");
            	printf("Ma tran tich truoc khi hoan doi:\n");
            	Output(Product,n);
            	    int p,q;
            	    count = 0;
   				 do{
   				 	
        			printf("nhap vao 2 cot doi vi tri cho nhau (0<p<=%d; 0<q<=%d): ",n,n);
        			scanf("%d %d", &p, &q);
        			if (p > n || q > n || p <= 0 || q <= 0) 
        				{
						printf("Sai kich thuoc, ");
						count++;
						if (count<3) printf("ban con %d nhap lai.\n",3-count);
						if (count == 3) {
							printf("Ban da nhap sai 3 lan, chuong trinh se quay lai menu.\n");
							getch();
							goto MENU;
						}
					
				}
    			} while (p > n || q > n || p <= 0 || q <= 0);
    			swapColumns(Product, temp, p-1, q-1, n);
    			printf("\nMa tran tich sau khi doi cot la: ");
   				Output(Product,n);
   				getch();
   				break;
            case 7: 
            if (ok==0) {
					printf("Chua nhap du lieu ma tran, Khong the luu file.\n");
					getch();
					break;
				}
             printf("Nhap ten file de luu ket qua: ");
    		 scanf("%s", file3);
    		writeMatrixToFile(file3, Sum, temp, Product, TransposeA, TransposeB, n);
    		printf("Da luu ket qua vao file. Bam phim bat ki de quay lai menu.");
    		getch();
    		break;
    		case 8: printf("Ket thuc chuong trinh, See you later."); break;
            default: 
            count++;
						if (count<3) printf("Lua chon khong hop le, bam phim bat ki de nhap lai!\n");
						if (count == 3) {
							printf("Ban da nhap sai 3 lan, chuong trinh se tu dong thoat.\n");
							exit(1);
						}
			getch();
        }
    } while (choice!=8);
}
