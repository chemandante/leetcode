#include <cassert>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class NumMatrix
{
private:
	vector<vector<int>> m_matrix;
	NumMatrix* m_pSubMatrix;	// Submatrix containing 2x2 sums of cells of the original matrix

public:
	NumMatrix(vector<vector<int>>& matrix)
	{
		vector<vector<int>> submatrix;
		vector<int> row;
		int i, j, cRow, cCol;

		m_matrix = matrix;
		cRow = matrix.size();
		cCol = matrix[0].size();

		// Building submatrix containing sums in 2x2 subblocks of original matrix
		// Size of submatrix will be floor(M/2) x floor(N/2)
		for (i = 0; i < (cRow & -2); i += 2)
		{
			row.clear();

			for (j = 0; j < (cCol & -2); j += 2)
			{
				row.push_back(matrix[i][j] + matrix[i][j + 1] + matrix[i + 1][j] + matrix[i + 1][j + 1]);
			}

			submatrix.push_back(row);
		}

		if (!submatrix.empty()) m_pSubMatrix = new NumMatrix(submatrix);
		else m_pSubMatrix = NULL;
	}

	int sumRegion(int row1, int col1, int row2, int col2)
	{
		int nSum = 0, r1, r2;
		bool bRow1 = row1 & 1;		// Add first row
		bool bRow2 = !(row2 & 1);	// Add last row

		if (row2 < row1 || col2 < col1) return 0;

		r1 = (row1 + 1) & -2;	// r1 is row1 ceiled to 2' multiple (next even number greater than row1)
		r2 = ((row2 + 1) & -2) - 1; // r2 is nearest odd number less then row2

		// If corresponding coord is odd, the cell is not counted in submatrix:
		// If beginning row is odd, we need count sum of first row from col1 to col2
		if (bRow1) for (int i = col1; i <= col2; ++i) nSum += m_matrix[row1][i];
		// If ending row is even, we need count sum of last row from col1 to col2
		if (bRow2) for (int i = col1; i <= col2; ++i) nSum += m_matrix[row2][i];
		// If beginning col is odd, we need count sum of first column, but take in mind:
		// we could already add matrix[row1][col1] and/or matrix[row2][col1]
		if (col1 & 1) for (int i = r1; i <= r2; ++i) nSum += m_matrix[i][col1];
		// Same for even col2
		if (!(col2 & 1)) for (int i = r1; i <= r2; ++i) nSum += m_matrix[i][col2];

		if (m_pSubMatrix)
		{
			nSum += m_pSubMatrix->sumRegion((row1 + 1) >> 1, (col1 + 1) >> 1, (row2 - 1) >> 1, (col2 - 1) >> 1);
		}

		return nSum;
	}

	int sumRegionSimple(int row1, int col1, int row2, int col2)
	{
		int nSum = 0;

		for (int i = row1; i <= row2; ++i)
		{
			for (int j = col1; j <= col2; ++j)
			{
				nSum += m_matrix[i][j];
			}
		}

		return nSum;
	}
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */



vector<vector<int>> readMatrix(ifstream& inFile)
{
	vector<vector<int>> mat;
	vector<int> row;
	int cInRow = -1;
	string str;

	getline(inFile, str);

	while (str != "")
	{
		stringstream ss(str);
		string elem;

		row.clear();

		while (getline(ss, elem, ','))
		{
			const char* psz = elem.c_str();
			if (!isdigit(psz[0])) psz++;
			row.push_back(atoi(psz));
		}

		if (cInRow < 0) cInRow = row.size();
		else if (cInRow != row.size())
		{
			printf("Assertion error: %d lines read before error\n", mat.size());
			abort();
		}

		mat.push_back(row);

		getline(inFile, str);
	}

	return mat;
}

//#define TEST_RESULT

int main()
{
	vector<vector<int>> data = { {3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5} };
	NumMatrix x1 = NumMatrix(data);

	printf("%d, %d\n", x1.sumRegion(2, 1, 4, 3), x1.sumRegionSimple(2, 1, 4, 3));
	printf("%d, %d\n", x1.sumRegion(1, 1, 2, 2), x1.sumRegionSimple(1, 1, 2, 2));
	printf("%d, %d\n", x1.sumRegion(1, 2, 2, 4), x1.sumRegionSimple(1, 2, 2, 4));
	printf("%d, %d\n", x1.sumRegion(0, 0, 4, 4), x1.sumRegionSimple(0, 0, 4, 4));

	vector<vector<int>> mat;
	ifstream	inFile;
	string		str;
	int			nCnt = 0;

	inFile.open("304\\test20.txt");
	//if (!pFile) return -1;

	mat = readMatrix(inFile);

	NumMatrix x = NumMatrix(mat);

	getline(inFile, str);

	while (str != "")
	{
		int r1, c1, r2, c2, n, ns;

		n = sscanf_s(str.c_str(), "[%d,%d,%d,%d],", &r1, &c1, &r2, &c2);
		if (n != 4)
		{
			printf("Stoped. Total %d sumRegions processed", nCnt);
			break;
		}

		n = x.sumRegion(r1, c1, r2, c2);
#ifdef TEST_RESULT
		ns = x.sumRegionSimple(r1, c1, r2, c2);
		if (n != ns)
		{
			printf("Different results for (%d, %d, %d, %d): %d != %d\n", r1, c1, r2, c2, n, ns);
		}
#endif

		nCnt++;
		getline(inFile, str);

		//if (nCnt > 10) break;
	}

	inFile.close();

	return 0;
}
