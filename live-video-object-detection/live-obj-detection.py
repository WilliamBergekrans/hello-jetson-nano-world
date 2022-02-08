#!/usr/bin/python3

import jetson.inference
import jetson.utils

# Load object detection model 
net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)

# Connect to the camera for streaming. 
# Creates and instance of the videoSource object. 
camera = jetson.utils.videoSource("csi://0")

# Create video output interface 
display = jetson.utils.videoOutput("display://0")

# Output to file
while display.IsStreaming():
    img = camera.Capture()
    # Detect automatically overlays the detections on the image. 
    detections = net.Detect(img)

    # Render the results 
    display.Render(img)
    # Display FPS information
    display.SetStatus("Object Detection | Network {:.0f} FPS".format(net.GetNetworkFPS()))

