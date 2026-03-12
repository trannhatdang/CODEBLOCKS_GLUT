#include <iostream>

void MultRow(float** mat, int n, int i, int multiplier)
{
	if(!mat[i])
	{
		std::cout << "Invalid Matrix entered into DivRow!" << std::endl;
		return;
	}

	for(int j = 0; j < n; ++j)
	{
		mat[i][j] *= multiplier;
	}
}

void AddRow(float** mat, int n, int operand, int operated)
{
	if(!mat[operand] || !mat[operated])
	{
		std::cout << "Invalid Matrix entered into AddRow!" << std::endl;
		return;
	}

	for(int j = 0; j < n; ++j)
	{
		mat[operated][j] += mat[operand][j];
	}
}

float* FindSolution(float** mat, int m, int n, float* c, int c_size)
{
	float* sol = new float[c_size];

	float** mat_cpy = new float*[m];
	float* c_cpy = new float[c_size];

	for(int i = 0; i < m; ++i)
	{
		mat_cpy[i] = new float[n];
		for(int j = 0; j < n; ++j)
		{
			mat_cpy[i][j] = mat[i][j];
		}
	}

	// for(int i = 0; i < m; ++i)
	// {
	// 	for(int j = 0; j < n; ++j)
	// 	{
	// 		std::cout << mat_cpy[i][j] << ' ';
	// 	}
	//
	// 	std::cout << std::endl;
	// }

	for(int i = 0; i < c_size; ++i)
	{
		c_cpy[i] = c[i];
	}

	for(int i = 0; i < m; ++i)
	{
		for(int j = i; j < n; ++j)
		{
			MultRow(mat_cpy, n, j, 1 / mat_cpy[i][j]);
		}

		for(int j = i + 1; j < n; ++j)
		{
			AddRow(mat_cpy, n, 0, j);
		}
	}

	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			std::cout << mat_cpy[i][j] << ' ';
		}

		std::cout << std::endl;

		delete[] mat_cpy[i];
	}

	delete[] c_cpy;

	return sol;
}

int main()
{
	float** a = new float*[4];

	for(int i = 0; i < 4; ++i)
	{
		a[i] = new float[4];
		for(int j = 0; j < 4; ++j)
		{
			a[i][j] = i;
		}
	}

	float b[4] = {5, 5, 5, 5};

	float* sol = FindSolution(a, 4, 4, b, 4);
	delete[] sol;

}
