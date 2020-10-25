//
// Created by oshikuru on 25. 10. 2020..
//

#include <mds-encoder/mds.h>
#include <chrono>
#include <string>
#include <filesystem>
#include <iostream>

constexpr int BarWidth = 70;
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    fs::path input_dir = fs::path("/mds-data/input/") / argv[1];
    if (!fs::is_directory(input_dir))
    {
        printf("Invalid video path!");
        return EXIT_FAILURE;
    }

    auto num_of_files = std::distance(fs::directory_iterator{input_dir},
                                      fs::directory_iterator{});

    auto output_dir = fs::path("/mds-data/output/") /
                      argv[1] /
                      "encoded";
    for (const auto& entry : std::filesystem::directory_iterator(output_dir))
        std::filesystem::remove_all(entry.path());
    fs::copy(input_dir / "1.bmp", output_dir);

    float progress = 0.0;
    printf("Loading %s...\n", argv[1]);
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<std::vector<uint8_t>, mds::rgb_image>> inputs(num_of_files);
    std::vector<std::vector<mds::motion_vector>> outputs(num_of_files);

    for (int i = 0; i < num_of_files; ++i)
    {
        auto img_path = input_dir / (std::to_string(i + 1) + ".bmp");
        inputs[i] = mds::load_bitmap_image(img_path.c_str());

        progress = float(i) / float(num_of_files - 1);

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
    printf("Successfully loaded %s after: %lds and %ldms\n", argv[1], duration / 1000, duration % 1000);

    progress = 0.0;
    printf("Encoding %s...\n", argv[1]);

    auto encoding_start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_of_files - 1; ++i)
    {
        outputs[i] = mds::encoder::mds_full8x8(inputs[i].second, inputs[i + 1].second);

        progress = float(i) / float(num_of_files - 1);

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

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - encoding_start).count();

    std::cout << std::endl;
    printf("Successfully encoded %s after: %lds and %ldms\n", argv[1], duration / 1000, duration % 1000);

    for (int i = 0; i < num_of_files - 1; ++i)
    {
        auto output_file_path = output_dir / (std::to_string(i + 2) + ".mds");
        mds::save(output_file_path.c_str(), outputs[i]);
    }

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    printf("Total time required: %lds and %ldms\n\n", duration / 1000, duration % 1000);

    return EXIT_SUCCESS;
}