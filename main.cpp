#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <memory>
#include <iostream>
#include <functional>

template<typename T>
using deleted_unique_ptr = std::unique_ptr<T, std::function<void(T *)>>;

int main()
{
    std::unique_ptr<tesseract::TessBaseAPI> api{new tesseract::TessBaseAPI()};

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(nullptr, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    deleted_unique_ptr<Pix> image{pixRead("phototest.tif"), [](Pix *pix) { pixDestroy(&pix); }};
    api->SetImage(image.get());

    // Get OCR result
    std::unique_ptr<char[]> outText{api->GetUTF8Text()};
    printf("OCR output:\n%s", outText.get());

    return 0;
}