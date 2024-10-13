#include <torch/torch.h>
#include <iostream>

int main()
{
    torch::Tensor tensor = torch::rand({2, 3}, torch::device(torch::kCUDA));
    std::cout << tensor << std::endl
              << tensor.dtype() << std::endl;
}