#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <streambuf>
#include <cstdio>
#include <cerrno>
#include <fstream>
#include <iostream>

std::string get_file_contents_c(const char *filename)
{
  std::FILE *fp = std::fopen(filename, "rb");
  if (fp)
  {
    std::string contents;
    std::fseek(fp, 0, SEEK_END);
    contents.resize(std::ftell(fp));
    std::rewind(fp);
    std::fread(&contents[0], 1, contents.size(), fp);
    std::fclose(fp);
    return(contents);
  }
  throw(errno);
}

std::string get_file_contents_cpp(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

std::string get_file_contents_iter(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
  }
  throw(errno);
}

std::string get_file_contents_assign(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.reserve(in.tellg());
    in.seekg(0, std::ios::beg);
    contents.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    return(contents);
  }
  throw(errno);
}

std::string get_file_contents_copy(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.reserve(in.tellg());
    in.seekg(0, std::ios::beg);
    std::copy((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>(), std::back_inserter(contents));
    in.close();
    return(contents);
  }
  throw(errno);
}

std::string get_file_contents_rdbuf(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return(contents.str());
  }
  throw(errno);
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Please supply a routine to run" << std::endl;
        return 1;
    }

    std::string str;
    switch (atoi(argv[2])) {
        case 1:
            str = get_file_contents_c(argv[1]);
            str += " ";
            break;
        case 2:
            str = get_file_contents_cpp(argv[1]);
            str += " ";
            break;
        case 3:
            str = get_file_contents_iter(argv[1]);
            str += " ";
            break;
        case 4:
            str = get_file_contents_assign(argv[1]);
            str += " ";
            break;
        case 5:
            str = get_file_contents_copy(argv[1]);
            str += " ";
            break;
        case 6:
            str = get_file_contents_rdbuf(argv[1]);
            str += " ";
            break;
        default:
            break;
    }
    return 0;
}
