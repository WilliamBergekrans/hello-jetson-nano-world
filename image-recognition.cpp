#include <jetson-inference/imageNet.h>
#include <jetson-utils/loadImage.h>

// Main 
int main( int argc, char** argv ) 
{
    // make sure that the image is included when calling the program 
    if (argc < 2) 
    {
        printf("Expected image filename as argument\n");
        return 0; 
    }

    // Get the image filename from the command line arguments
    const char* imgFilename = argv[1];

    // Tries to open the file using the provided filename
    uchar3* imgPtr = NULL; // Pointer to the image
    int imgWidth = 0; // Width in pixels
    int imgHeight = 0; // Height in pixels

    // Either stores image in the imgPtr (image pointer) or gives error msg.
    if (!loadImage(imgFilename, &imgPtr, &imgWidth, &imgHeight))
    {
        printf("Failed to load image '%s' \n", imgFilename);
        return 0;
    }

    // Load the imageNet network for image recognition
    imageNet* net = imageNet::Create(imageNet::GOOGLENET);

    // Check that the network is loaded properly 
    if( !net ) 
    {
        printf("Failed to load the image recognition network\n");
        return 0;
    }

    // Variable for storing confidence in a classification 
    float confidence = 0.0; 

    // Classify the image and return 
    const int classIndex = net -> Classify(imgPtr, imgWidth, imgHeight, &confidence);

    // Check that the classification is valid 
    if (classIndex >= 0)
    {
        // Get the class description
        const char* classDescrition = net -> GetClassDesc(classIndex);

        // Print the classification results
        printf("Image is recognized as '%s' (class #%i) with %f%% confidence\n", 
                classDescrition, classIndex, confidence * 100.0f);
    } 
    else 
    {
        printf("Failed to classify the image\n");
    }

    // Need to return the objects and free CUDA resources 
    delete net; 

    return 0;
}