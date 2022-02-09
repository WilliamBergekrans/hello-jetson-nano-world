#!/usr/bin/python3

import jetson.inference
import jetson.utils

# Load object detection model 
net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)

# Connect to the camera for streaming. 
# Creates and instance of the videoSource object. 
input = jetson.utils.videoSource("csi://0")

# Create video output interface 
output = jetson.utils.videoOutput("display://0")

# Output to file
while output.IsStreaming():
    img = input.Capture()
    # Detect automatically overlays the detections on the input. 
    detections = net.Detect(img)
    # Render the results 
    output.Render(img)
    # Display FPS information
    output.SetStatus("Object Detection | Network {:.0f} FPS".format(net.GetNetworkFPS()))

