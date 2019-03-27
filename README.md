# Random Number Sequence Discriminator

## Overview
This work deals with discriminating patterns created using random numbers generated from different functions. For example, the figures show a 2D histogram created using random numbers from a Gaussian distribution (left) and a 2D histogram created using Gaussian and Landau distributions where the random numbers generated from the former is the x-coordinate and the latter is the y-coordinate (right).

<img src="https://github.com/stjohnso98/Random-Number-Sequence-Discriminator/blob/master/docs/c1.png" width="425" /> <img src= "https://github.com/stjohnso98/Random-Number-Sequence-Discriminator/blob/master/docs/c3.png" width="425" />

Although the difference between both figures is clear when there is 5 million entries in the figure, it is not clearly distinguishable when there is say, only 150, entries i.e 150 pairs of random numbers. For example, the below figures are 2D histogram created using random numbers from a Gaussian distribution (left) and a 2D histogram created using Gaussian and Landau distributions where the random numbers generated from the former is the x-coordinate and the latter is the y-coordinate (right) with only 150 entries (150 pairs of random numbers) in both cases.

<img src="https://github.com/stjohnso98/Random-Number-Sequence-Discriminator/blob/master/docs/gauss.png" width="425" /> <img src="https://github.com/stjohnso98/Random-Number-Sequence-Discriminator/blob/master/docs/land.png" width="425" />

This becomes a pattern recognition problem in which these can be used to train neural networks.

## Instructions
The images for this work were created using ROOT. ROOT is an object oriented program and library developed by CERN. All images are 2D histograms filled with pairs of random numbers i.e (x,y,z) is (a random number, a random number, normalized number of such pairs). Signal images were images where both x and y were random numbers from a Gaussian distribution with mean = 0 and std.dev=3. Background images were images wheere x is a random number from the same Gaussian distribution and y is from Landau distribution with mean=0, std. dev=3.

C++ code for creating signal and background images are given in sigtree.C and bgtree.C respectively. These scripts also have the code to create a TTree which is a structure to store large quantities of same class objects in ROOT. The branches of these tree hold values of normalized pixel intensities. This trees will then become input to a neural network implemented using TMVA. ![TMVAClassification.C](https://github.com/stjohnso98/Random-Number-Sequence-Discriminator/blob/master/TMVAClassification.C) shows the code for the same. 

Python code for tensorflow implementing convolutional neural network along with training and testing is given in the script ![Gauss_Land.py](https://github.com/stjohnso98/Random-Number-Sequence-Discriminator/blob/master/Gauss_Land.py). This script reads and decodes image file and trains and tests the CNN on them.
