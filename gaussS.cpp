#include <iostream>
#include <fstream>

void input_Demention(unsigned int& M)
{
	std::cout << "\nEnter the quantity of unknown variables\n" << std::endl;
	std::cout << "Variables = ";
	std::cin >> M;
}

struct File_Reader
{
	std::ifstream fread;
	const char* file_Name;
	File_Reader(const char* _name)
	{
		file_Name = _name;
		fread.open(file_Name, std::ios::in);
		if(!fread.is_open())
		{
			std::cout << "Error" ;
		}
		else
		{
			std::cout << "you're lucky\n";
		}
	}
	bool read_digit(int& digit)
       	{
		return (fread >> digit ? true : false);
	}
	~File_Reader()
       	{
		fread.close();
	}
};

struct Matrix 
{
	float* array_A;
	float* array_B;
	unsigned int size;
	Matrix(const unsigned int M_size)
       	{
		size = M_size;
		array_A = new float [size * size];
		array_B = new float [size];
	}
	int get_Size()
       	{
		return size;
	}
	float& operator() (const unsigned int i, const unsigned j) 
	{
		return array_A[i * get_Size() + j];
	}
	float& operator() (const unsigned int i) 
	{
		return array_B[i];
	}
	~Matrix()
       	{
		delete [] array_A;
		delete [] array_B;
	}
};

void gauss_Seidel_Method(Matrix& a, Matrix& b, Matrix& x, unsigned int& loop, File_Reader& fa, File_Reader& fb)
{
	int digit = 0;
	float temp;
	for(int i = 0; i < a.get_Size(); ++i)
       	{
		for(int j = 0; j < a.get_Size(); ++j)
	       	{
			fa.read_digit(digit);
			a(i, j) = digit;
			std::cout << a(i, j) << "\t";
		}
		fb.read_digit(digit);
		b(i) = digit;
		x(i) = 0;
		temp = 0;
		std::cout << "|  " << b(i) << "\n";
	}
	std::cout << "\n";
	while(loop > 0)
       	{
		for(int i = 0; i < a.get_Size(); ++i)
	       	{
			temp = (b(i) / a(i, i));
			for(int j = 0; j < a.get_Size(); ++j)
		       	{
				if(j != i) 
				{	
					temp = temp - ((a(i, j) / a(i, i)) * x(j));
				}
				x(i) = temp;
			}
			std::cout << " X[" << i + 1 << "] = " << x(i) << "\t";
		}
		std::cout << "\n";
		--loop;
	}
}

int main()
{
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed);
	unsigned int M = 0;
	input_Demention(M);
	File_Reader fa("a.txt"), fb("b.txt");
	Matrix A(M), B(M), X(M), Y(M);
	unsigned int loop;
	std::cout << "\nEnter the iteration ";
	std::cin >> loop;
	gauss_Seidel_Method(A, B, X, loop, fa, fb);
	return 0;
}
