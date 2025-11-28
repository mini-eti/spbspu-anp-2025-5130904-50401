#include <iostream>
#include <fstream>

namespace mansurov
{
  size_t min(size_t a, size_t b);
  void transformMatrix(int* mtx, size_t m, size_t n);
  size_t fillMatrix(std::istream& input, int* matrix, size_t rows, size_t cols);
  int minSum(const int* matrix, size_t rows, size_t cols);
  void outputToFile(std::ofstream& output, const int* matrix, size_t rows, size_t cols, int minSum);
}

int main(int argc, char** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  else if (argc > 4)
  {
    std::cerr << "Too much arguments\n";
    return 1;
  }
  else if (!isdigit(*argv[1]))
  {
    std::cerr << "First parameter not number\n";
    return 1;
  }
  else if (!((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0'))
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  size_t rows = 0;
  size_t cols = 0;
  input >> rows >> cols;

  if (!input)
  {
    std::cerr << "BAD input\n";
    return 2;
  }

  if (rows == 0 || cols == 0)
  {
    output << rows << " " << cols << " 0";
    return 0;
  }

  int tempMatrix1[10000] = {};
  int* tempMatrix2 = nullptr;

  if (argv[1][0] == '2')
  {
    try
    {
      tempMatrix2 = new int[rows * cols];
    }
    catch (const std::bad_alloc& e)
    {
      std::cerr << e.what() << '\n';
      return 2;
    }
  }

  int* matrix = argv[1][0] == '1' ? tempMatrix1 : tempMatrix2;
  size_t isInputOk = mansurov::fillMatrix(input, matrix, rows, cols);

  if (isInputOk == 1)
  {
    std::cerr << "Input error";
    delete[] tempMatrix2;
    return 2;
  }
  else if (isInputOk == 2)
  {
    std::cerr << "Too much arguments\n";
    delete[] tempMatrix2;
    return 2;
  }

  int minSum = mansurov::minSum(matrix, rows, cols);
  mansurov::transformMatrix(matrix, rows, cols);
  mansurov::outputToFile(output, matrix, rows, cols, minSum);

  if (argv[1][0] == '2')
  {
    delete[] matrix;
  }

  return 0;
}

size_t mansurov::min(size_t a, size_t b)
{
  return (a <= b) ? a : b;
}

void mansurov::outputToFile(std::ofstream& output, const int* matrix, size_t rows, size_t cols, int minSum)
{
  for (size_t i = 0; i < rows * cols; ++i)
  {
    output << matrix[i];
    if (i < rows * cols - 1)
    {
      output << " ";
    }
  }
  output << " " << minSum << "\n";
}

size_t mansurov::fillMatrix(std::istream& input, int* matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < (rows * cols); ++i)
  {
    input >> matrix[i];
    if (!input)
    {
      return 1;
    }
  }
  
  int lastTry = 0;
  input >> lastTry;
  if (input || !input.eof())
  {
    return 2;
  }
  return 0;
}

void mansurov::transformMatrix(int* matrix, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0)
  {
    return;
  }
  
  for (size_t i = 0; i < rows * cols; i++)
  {
    size_t row = i / cols;
    size_t col = i % cols;
    size_t distTop = row;
    size_t distBottom = rows - 1 - row;
    size_t distLeft = col;
    size_t distRight = cols - 1 - col;
    size_t layer = mansurov::min(mansurov::min(distTop, distBottom), mansurov::min(distLeft, distRight));
    matrix[i] += (layer + 1);
  }
}

int mansurov::minSum(const int* matrix, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0)
  {
    return 0;
  }
  
  int minSum = matrix[0];
  
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      int tempSum = matrix[i * cols + j];
      
      if (i > 0 && j < cols - 1)
      {
        tempSum += matrix[(i - 1) * cols + j + 1];
      }
      if (j > 0 && i < rows - 1)
      {
        tempSum += matrix[(i + 1) * cols + j - 1];
      }
      
      if (tempSum < minSum)
      {
        minSum = tempSum;
      }
    }
  }
  
  return minSum;
}