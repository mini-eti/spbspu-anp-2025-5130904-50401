  #include<iostream>
  #include <fstream>


  namespace mansurov
  {
    size_t min(size_t a, size_t b);
    void transformMatrix(int * mtx, size_t m, size_t n);
    size_t fillMtrx(std::istream& input, int* mtx, size_t rows, size_t cols);
  } 


  int main(int argc, char** argv)
  {
    if (argc < 4)
    {
      std::cerr << "Not enough arguments\n";
      return 1;
    } else if (argc > 4) {
      std::cerr << "Too mush argument\n";
      return 1;
    } else if (!isdigit(*argv[1])) {
      std::cerr << "First parameter not number\n";
      return 1;
    } else if (!((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0')) {
      std::cerr << "First parameter is out of range\n";
      return 1;
    }
    std::ifstream input(argv[2]);
    std::ofstream output(argv[3]);
    size_t rows = 0, cols = 0;
    input >> rows >> cols;
    if (!input)
    {
      std::cerr << "BAD input\n";
      return 2;
    }

    if (rows == 0 || cols == 0)
    {
      output << rows << " " << cols;
      return 0;
    }
    int tempMatrix1[rows * cols] = {};
    int* tempMatrix2 = nullptr;
    if (argv[1][0] == '2')
    {
      try
      {
        tempMatrix2 = new int [rows * cols];
      }
      catch(const std::bad_alloc& e)
      {
        std::cerr << e.what() << '\n';
        return 2;
      }
    }
    int* matrix = argv[1][0] == '1' ? tempMatrix1 : tempMatrix2;
    size_t isInputOk = mansurov :: fillMtrx(input, matrix, rows, cols);
    if(isInputOk == 1){
      std::cerr << "input error";
      delete[] tempMatrix2;
      return 2;
    }
    else if (isInputOk == 2)
    {
      std::cerr << "Too much arguments\n";
      delete [] tempMatrix2;
      return 2;
    } 
  }


  size_t mansurov :: min(size_t a, size_t b){
    return (a<=b) ? a: b;
  }

  size_t  mansurov :: fillMtrx(std::istream& input, int* mtx, size_t rows, size_t cols){
    for(size_t i = 0; i < (rows * cols); ++i)
    {
      input >> mtx[i];
      if(!input){
        return 1;
      }
    }
    int last_try = 0;
    input >> last_try;
    if (input || !input.eof())
    {
      return 2;
    }
    return 0;
  }

  void mansurov :: transformMatrix(int * mtx, size_t n, size_t m)
  {
    for (size_t i = 0; i < m * n; i++) {
        size_t row = i / n;
        size_t col = i % n;
        size_t distTop = row;
        size_t distBottom = n - 1 - row;
        size_t distLeft = col;
        size_t distRight = m - 1 - col;
        size_t layer = mansurov :: min(mansurov :: min(distTop, distBottom), mansurov :: min(distLeft, distRight));
        mtx[i] += (layer + 1);
    }
  }

  
