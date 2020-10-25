//
// Created by oshikuru on 25. 10. 2020..
//

#include <mds-decoder/decoder.h>
#include <chrono>
#include <string>
#include <filesystem>
#include <iostream>

constexpr int BarWidth = 70;
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    fs::path input_dir = fs::path("/mds-data/output") / argv[1] / "encoded";
    if (!fs::is_directory(input_dir))
    {
        printf("Invalid video path!");
        return EXIT_FAILURE;
    }

    auto num_of_files = std::distance(fs::directory_iterator{input_dir},
                                      fs::directory_iterator{});

    auto output_dir = fs::path("/mds-data/output/") /
                      argv[1] /
                      "decoded";
    for (const auto& entry : std::filesystem::directory_iterator(output_dir))
        std::filesystem::remove_all(entry.path());
    fs::copy(input_dir / "1.bmp", output_dir);

    float progress = 0.0;
    printf("Decoding %s...\n", argv[1]);
    auto start = std::chrono::high_resolution_clock::now();

    auto [header, referent_image] = mds::load_bitmap_image((input_dir / "1.bmp").c_str());

    for (int i = 2; i < num_of_files; ++i)
    {
        auto motion_path = input_dir / (std::to_string(i) + ".mds");
        auto output_file_path = output_dir / (std::to_string(i) + ".bmp");

        auto motions = mds::load(motion_path.c_str());
        referent_image = mds::decoder::decode_motion_vector8x8(referent_image, motions);
        mds::write_to_bitmap_image(referent_image, header.data(), output_file_path.c_str());

        progress = float(i - 1) / float(num_of_files - 2); // for demonstration only

        std::cout << "[";
        int pos = BarWidth * progress;
        for (int i = 0; i < BarWidth; ++i)
        {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::endl;
    printf("Total time required: %lds and %ldms\n\n", duration / 1000, duration % 1000);

    return EXIT_SUCCESS;
}