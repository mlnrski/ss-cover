#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <memory>
#include <iostream>

class pix_wrapper {
public:
    explicit pix_wrapper(Pix *pix);

    virtual ~pix_wrapper();

    operator Pix *();

    Pix *operator->();

    // Prohibit copying and assignment.
    pix_wrapper(const pix_wrapper &) = delete;

    pix_wrapper &operator=(const pix_wrapper &) = delete;

private:

    Pix *pix;
};

int main()
{
    std::unique_ptr<tesseract::TessBaseAPI> api{new tesseract::TessBaseAPI()};

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(nullptr, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    pix_wrapper image{pixRead("phototest.tif")};
    api->SetImage(image);

    // Get OCR result
    std::unique_ptr<char[]> outText{api->GetUTF8Text()};
    printf("OCR output:\n%s", outText.get());

    return 0;
}

pix_wrapper::pix_wrapper(Pix *pix) : pix(pix)
{
}

pix_wrapper::~pix_wrapper()
{
    pixDestroy(&pix);
}

pix_wrapper::operator Pix *()
{
    return pix;
}

Pix *pix_wrapper::operator->()
{
    return pix;
}