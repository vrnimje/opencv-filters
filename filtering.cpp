#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
  // Reading the source image
  std::string file_path;
  if (argc == 2) {
    file_path = argv[1];
  } else {
    std::cout << "Usage: \n ./filtering [image file path] \n";
    return 1;
  }

  cv::Mat src = cv::imread(file_path);

  // Checking if path exixts
  if (src.empty()) {
    std::cout << "Could not read the image" << std::endl;
    return 1;
  }

  cv::Size dims = cv::Size(3, 3);

  // Defining the destination image matrix and the kernel (filter)
  cv::Mat dst, kernel;

  // Option no.
  int opt;
  std::cout << "Filters:- " << std::endl
            << "1. Box filter" << std::endl
            << "2. Gaussian filter" << std::endl
            << "3. Sobel Edge-Y filter" << std::endl
            << "4. Sobel Edge-X filter" << std::endl
            << "5. Sharpen filter" << std::endl
            << "6. High Pass filter" << std::endl
            << "7. Emboss filter" << std::endl
            << "Enter option no.: ";

  std::cin >> opt;

  switch (opt) {
  case 1: // Box filter
    cv::boxFilter(src, dst, -1, dims);
    break;
  case 2: // Gaussian filter
    cv::GaussianBlur(src, dst, dims, 0);
    break;
  case 3: // Sobel Y filter
    cv::Sobel(src, dst, -1, 0, 1, 3);
    break;
  case 4: // Sobel X filter
    cv::Sobel(src, dst, -1, 1, 0, 3);
    break;
  case 5: // Sharpen filter
    kernel = (cv::Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

    // Applying convolution using 'kernel' on the 'src' image
    cv::filter2D(src, dst, -1, kernel);
    break;
  case 6: // High Pass filter
    kernel = (cv::Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);

    // Applying convolution using 'kernel' on the 'src' image
    cv::filter2D(src, dst, -1, kernel);
    break;
  case 7: // Emboss filter
    kernel = (cv::Mat_<int>(3, 3) << -2, -1, 0, -1, 1, 1, 0, 1, 2);

    // Applying convolution using 'kernel' on the 'src' image
    cv::filter2D(src, dst, -1, kernel);
    break;
  default:
    std::cout << "Incorrect option!" << std::endl;
    return 0;
    break;
  }

  // Displaying the source image
  cv::imshow("Input image (press enter to continue)", src);
  // Waiting for any keyboard press to continue
  cv::waitKey(0);

  // Displaying the output image
  cv::imshow("Output Image", dst);
  cv::imwrite("../assets/test-" + std::to_string(opt) + ".png", dst);
  // Waiting for any keyboard press to continue
  cv::waitKey(0);
  return 0;
}