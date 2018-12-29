#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <memory>
#include <iostream>
#include "util.hpp"

template<>
void annihilate<Pix>(Pix *ptr)
{ pixDestroy(&ptr); }

int main()
{
    std::unique_ptr<tesseract::TessBaseAPI> api{new tesseract::TessBaseAPI()};

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(nullptr, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    std::unique_ptr<Pix, Annihilator<Pix>> image{pixRead("phototest.tif")};
    api->SetImage(image.get());

    // Get OCR result
    std::unique_ptr<char[]> outText{api->GetUTF8Text()};
    printf("OCR output:\n%s", outText.get());

    return 0;
}