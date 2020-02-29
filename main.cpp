#include <chrono>  // for high_resolution_clock
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

void write_data(const std::string& path, std::vector<uchar> buf) {
    FILE* file = fopen(path.data(), "wb");
   // uchar* result = reinterpret_cast<uchar*> (&buf[0]);
    fwrite(&buf[0], sizeof(uchar), (int)buf.size(), file);
}

void read_data(char* path, std::vector<char> & vec) {
    std::ifstream file(path);

    if(file.eof() || file.fail() ) {
        std::cout << path << ": file not found\n" << std::endl;
        return;
    }

    file.seekg(0, std::ios_base::end);
    std::streampos fileSize = file.tellg();
    vec.resize(fileSize);
    file.seekg(0, std::ios_base::beg);
    file.read(&vec[0], fileSize);
    file.close();
}

template <typename T>

void free_vec(std::vector<T> vec) {
    vec.clear();
    vec.shrink_to_fit();
}

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cout <<"usage: DisplayImage.out <Image_Path>\n" << std::endl;
        return -1;
    }
    // read image to buffer
    std::vector<char> vec;
    read_data(argv[1], vec);

    if (vec.empty()) {
        return -1;
    }

    auto start = Time::now();
    // Load matriz
    Mat image;
    image = imdecode(vec, IMREAD_UNCHANGED);

    if ( !image.data ) {
        std::cout <<"No image data \n"  << std::endl;
        return -1;
    }

    // write
    std::vector<uchar> vec_out;
    std::vector<int> compression_params;
    compression_params.push_back(IMWRITE_JPEG_QUALITY);
    compression_params.push_back(90);

    if(!imencode(".jpg", image, vec_out, compression_params)) {
        std::cout <<"No encode image \n"  << std::endl;
        return -1;
    }

    auto finish = Time::now();
    fsec elapsed = finish - start;
    std::cout << "Elapsed time: " << std::chrono::duration_cast<ms>(elapsed).count() << " ms\n";

    write_data("/home/renato/Pictures/c++_kobe.jpg", vec_out);

    // namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", image);
    //waitKey(0);

    // free memory
    free_vec(vec);
    free_vec(compression_params);
    free_vec(vec_out);

    image.release();

    return 0;
}
